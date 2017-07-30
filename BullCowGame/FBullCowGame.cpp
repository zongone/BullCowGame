#pragma once

#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

const int32 DEFAULT_NUMBER_OF_LETTERS = 6;

FBullCowGame::FBullCowGame() { Reset(DEFAULT_NUMBER_OF_LETTERS); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(int32 NumberofLetters)
{
	TMap<int32, FString> Words{ { 3,"kot" },{ 4,"piwo" },{ 5,"robak" },{ 6,"kamera" }, }; // this MUST be an isogram
	MyHiddenWord = Words[NumberofLetters];
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lovercase;
	} 
	else if (Guess.length()!=GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} 
	else {
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();

	// loop through all letters in the hidden word	
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the hidden guess
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (Guess[i] == MyHiddenWord[j]) {
				// if they're in the same place
				if (i == j) {
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // incriment cows
				}			
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { 
		bGameIsWon = true;
	}
	else { 
		bGameIsWon = false; 
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true;}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else
		{
			LetterSeen[Letter] = true;
		}
	
		//iterate through the word and put every letter to the map with the value of true
		// returm false if any letter is multipicated
		// otherwise add the letter to the map
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}
