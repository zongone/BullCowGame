#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
int32 GetValidNumber();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;
int32 NumberOfLetters;
constexpr int MIN_NUMBER = 3;
constexpr int MAX_NUMBER = 6;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain()==true);

	return 0;
}

void PrintIntro()
{
	//introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Enter number of letters ["<< MIN_NUMBER << "-" << MAX_NUMBER << "]: ";
	NumberOfLetters = GetValidNumber();
	std::cout << "Can you guess the " << NumberOfLetters << " letter isogram I'm thinking of?\n\n";
	return;
}

int32 GetValidNumber()
{
	int32 NumberOfLetters = 0;
	while (!(std::cin >> NumberOfLetters))
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		std::cout << "Not a number!\n";
		std::cout << "Enter number of letters [3-6]: ";
	}
	while ((NumberOfLetters < MIN_NUMBER) || (NumberOfLetters > MAX_NUMBER))
	{
		std::cout << "Invalid value!\n";
		std::cout << "Enter number of letters [3-6]: ";
		std::cin >> NumberOfLetters;
	}
	std::cin.ignore(INT_MAX, '\n');
	return NumberOfLetters;
}

void PlayGame()
{
	BCGame.Reset(NumberOfLetters);

	while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries() ) {
		{
			FText Guess = GetValidGuess();
			//submit valid guess to the game
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
		}
	}  
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response;
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You won!\n";
	}
	else
	{
		std::cout << "Bad luck :(\n";
	}
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		// get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lovercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);	
	return Guess;
}
