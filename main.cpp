/*acesta este executabilul consolei care foloseste  clasa BullCow
acesta actioneaza ca vizualizare intr-un mod MCV si este responsabil pentru toata interactiunea utilizatorului
pentru logica jocului a se vedea clasa FBullAndCowGame
*/

#include <iostream>
#include <string> // pentru a corecta si a functiona biblioteca string fara namespace 
//"Edit - Find and Replace - Quck Replace" apoi scriem "FText"
// pentru a corecta mai rapid "ctrl + h"
#include "FBullAndCowGame.h" // biblioteca creata de noi pentru a putea introduce variabile

//pentru a face sintaxa mai prietenoasa cu Unreal
using FText = std::string;
using int32 = int;

// corpurile functiilor le-am mutat sub main pentru o mai buna viziune a codului
//functii prototip in afara clasei
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullAndCowGame  BCGame; // este clasa creata de noi cu variabila declarata // cream instant un nou joc
//am declarat global pentru a avea acces mereu la noul joc.

int main() {// punctul de intrare in aplicatie
	bool bPlayAgain = false; // "variabila" bool-eala
	do {

		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	return 0;// iesirea din aplicatie
}

// introducerea jocului
void PrintIntro() {
	//prin metoda facuta "GetMyHiddenWordLength" putem schimba constanta si sa eliminam
	//"constexpr int32 WORD_LENGTH = 5;//expresie constanta" 
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//se joaca un singur joc pana la sfarsit
void PlayGame() {// am creat aceasta functie prin selectarea corpului, click dreapata si selectand 
	//"Quick Action << Extract Function"
	//structura repetitiva pentru numarul de incercari de a ghici
	BCGame.Reset();//vrem sa resetam mereu vechiul joc pentru a incepe altul
	//metoda Reset face exact ce face si constructorul, 
	//reseteaza valorile pentru a incepe un nou joc 

	int32 MaxTries = BCGame.GetMaxTries();//am creat aceasta variabila pentru a simplifica functia si a elimina
	//"constexpr int NUMBER_OF_TURNS = 5;// numarul e incercari"
	//TODO schimbarea din for in while cand am validat incercarile
//bucla repetitiva care cere incercari de raspuns 
//pana cand jocul NU(!) este castigat si cand mai sunt incercari de validat
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); //TODO o bucla repetitiva pentru a vedea daca raspunsul este corect
		// intoarcerea raspunsului de la jucator
		//validarea raspunsului jucatorului in joc si primim contoarele
		FBullAndCowCount BullAndCowCount = BCGame.SubmitValidGuess(Guess);
		//afisarea numaului de bulls si cows
		std::cout << "Bull = " << BullAndCowCount.Bulls;
		std::cout << "  Cow = " << BullAndCowCount.Cows << "\n\n";//am folosit \n pentru a reduce codul
	}
	//TODO adauga un sumar al jocului, dupa ce jocul este terminat
	PrintGameSummary();
	return;
}
//structura repetitiva continua pana cand jucatorul scrie un raspuns valid

FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//primeste raspunsul de la jucator
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);// citim cu std::getline pentru a putea citi tot sirul de caractere ignorand spatiile. Daca citeam doar cu cin citeam doar primul cuvant
		// atunci cand nu mai avem namespace vom citi "cin" tot cu "std::"
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Scrie un cuvant din " << BCGame.GetHiddenWordLength() << " litere.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Scrie un cuvant fara a se repeta literele.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Scrie toate literele cuvantului cu litera mica.\n\n";
			break;
		default://asuma valabilitatea raspunsului
			break;

		}

	} while (Status != EGuessStatus::OK);//structura repetitiva continua pana vom avea raspuns fara erori
	return Guess;
}

bool AskToPlayAgain() { //functia bool returneaza true sau false
	std::cout << "Do you want to play again with the same hidden word?(y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "FELICITARI!!! - Ai castigat\n";
	}
	else {
		std::cout << "Mult noroc data viitoare\n";
	}
}
