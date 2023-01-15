#include "FBullAndCowGame.h" // este acelasi lucru cu ceea ce am scris in fisierul .h
#include <map>
#define TMap std::map

using int32 = int;

FBullAndCowGame::FBullAndCowGame() { Reset(); }//activam metoda Reset de fiecare data cand incepem un joc nou
//pentru a avea numarul de incercari disponibile si numarul incercarii curente
//constructor implicit

int32 FBullAndCowGame::GetCurrentTry() const { return MyCurrentTry; }
// scriind const la sfarsit ne poate reaminti
	//atunci cand facem debug ca functia este nemodificabila
int32 FBullAndCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
//prin aceasta metoda ne va arata la inceputul jocului
//cate litere va avea cuvantul care trebuie sa il ghicim, cuvant scris mai jos in 
//functia "void FBullAndCowGame::Reset()"
bool FBullAndCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullAndCowGame::GetMaxTries() const {
	TMap <int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,7}, {6,10}, {7,15}, {8,20}, {9,25}, {10,30} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	//folosind aceasta metoda adaptam numarul de incercari in functie de numarul de litere al cuvantului
	//{3 este numarul de litere, 5 este numarul de incercari}
}


void FBullAndCowGame::Reset() {
	const FString HIDDEN_WORD = "captiv";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	//de fiecare data cand se incepe un nou joc vom avea aceste valori
	return;
}

EGuessStatus FBullAndCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {//daca cuvantul nu este isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {//daca cuvantul nu este cu litere mici
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {//daca lungimea cuvantului este gresita
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

//primim o varianta valida, incrementeaza incercarile si returneaza count 
FBullAndCowCount FBullAndCowGame::SubmitValidGuess(FString Guess) {
	//incrementam numarul de incercari
	++MyCurrentTry;
	//setam o variabila pentru returnare
	FBullAndCowCount BullAndCowCount;
	int32 WorldLentgh = MyHiddenWord.length();
	//facem o structura repetitiva pentru a trece printr-e toate literele incercarii
	for (int32 MHWChar = 0; MHWChar < WorldLentgh; ++MHWChar) {// MHWChar = MyHiddenWord Character
		//comparam literele incercarii cu cuvantul ascuns
		for (int32 GChar = 0; GChar < WorldLentgh; ++GChar) {// GChar = Guess Character
			//daca literele ghicite se potrivesc
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//incrementam bulls daca literele sunt in locul potrivit
				if (MHWChar == GChar) {
					++BullAndCowCount.Bulls;
					//incrementam cows daca nu sunt in locul potrivit
				}
				else {
					++BullAndCowCount.Cows;
				}
			}
		}
	}
	if (BullAndCowCount.Bulls == WorldLentgh) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullAndCowCount;
}

bool FBullAndCowGame::IsIsogram(FString World) const {
	//daca cuvantul contine 1 litera sau 0 litere se poate considera isogram
	if (World.length() <= 1) { return true; }
	TMap <char, bool> LetterSeen;//setam tabla de joc 
	//(tabla de joc sunt spatiile unde trebuie sa gasim literele corespunzatoare cuvantului)
	for (auto Letter : World) {//pentru toate literele cuvantului
		Letter = tolower(Letter); //pentru cazurile mixte(litera mare si litera mica)
		//Facem o structura repetitiva pentru a trece prn toate literele cuvantului
		if (LetterSeen[Letter]) {//daca o litera este deja pe tabla de joc 
			return false;//nu avem in cuvant isogram
		}
		else {
			LetterSeen[Letter] = true;//adaugam litera pe tabla de joc
		}
	}
	return true;//pentru cazurile cand se introduce /0
}

bool FBullAndCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {//daca nu este litera mica
			return false;
		}
	}
	return true;
}