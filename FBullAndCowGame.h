// FBullAndCowGame.h
#pragma once
#include <string>
#include <map>
#include <vector>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullAndCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullAndCowGame {
public:
	FBullAndCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset();
	FBullAndCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	std::vector<FString> WordList;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
