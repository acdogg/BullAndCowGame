/*Logica jocului (fara vederea codului sau a interactiunii utilizatorului)
Jocul este un simplu joc de ghicit literele cuvantului ascuns
*/

#pragma once //pentru a nu importa de doua ori
#include <string> // libraria string pentru CheckGameValidity pentru a citi string - ul

//pentru a face sintaxa mai prietenoasa cu Unreal
using FString = std::string;
using int32 = int;

struct FBullAndCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {//aceasta clasa o vom implemanta in FBullAndCowGame.cpp
	//ne ajuta sa verificam daca raspunsul jucatorului este in standardul creat de noi
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullAndCowGame {
public: // metoda publica // nu expunem nici o variabila public // este int32erfata jocului
	FBullAndCowGame(); //pentru a crea un constructor scriem numele clasei si cream o metoda

	int32 GetMaxTries() const;// previne modificarea codului scris de noi
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO face o valoare de returnare mai bogata"?"

	void Reset(); // TODO face o valoare de returnare mai bogata"?"
	//gasirea unei metode de a contoriza numarul de bulls si cows si de a incrementa numarul incercarilor
	FBullAndCowCount SubmitValidGuess(FString);//contorizeaza numarul de bulls si cows // asuma incercarile valide

private:
	//priveste constructorul pentru initializare
	int32 MyCurrentTry;
	FString  MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
