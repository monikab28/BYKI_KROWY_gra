#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// punkt wejœcia dla gry
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // wyœcie z gry
}

void PrintIntro()
{
	std::cout << "| Witaj w grze BYKI I KROWY! Jest to ciekawa gra oparta na zgadywaniu wyrazow. |\n";
	std::cout << std::endl;
	std::cout << "|             .=     ,        =.           " << std::endl;
	std::cout << "|     _  _   /'/    )\,/,/(_   \ \         " << std::endl;
	std::cout << "|      `//-.|  (  ,\\)\//\)\/_  ) |        " << std::endl;
	std::cout << "|      //___\   `\\\/\\/\/\\///'  /        " << std::endl;
	std::cout << "|   ,-''`- _ ` - -  _       _ \ ' ~-,_     " << std::endl;
	std::cout << "|   \       `-.  '_`.      .'_` \ ,-'~`/   " << std::endl;
	std::cout << "|    `.__.-'`/   (-\        /-) |-.__,'    " << std::endl;
	std::cout << "|      ||   |     \O)  /^\ (O/  |          " << std::endl;
	std::cout << "|      `\\  |         /   `\    /          " << std::endl;
	std::cout << "|        \\  \       /      `\ /           " << std::endl;
	std::cout << "|         `\\ `-.  /' .---.--.\            " << std::endl;
	std::cout << "|           `\\/`~(, '()      ('           " << std::endl;
	std::cout << "|            /(O) \\   _,.-.,_)            " << std::endl;
	std::cout << "|           //  \\ `\'`      /             " << std::endl;
	std::cout << "|         / |  ||   `' ' '  '              " << std::endl;  
	std::cout << "|        /'  |__||                         " << std::endl;
	std::cout << "|              `o                          " << std::endl;
	std::cout << "|                                          " << std::endl;
	std::cout << "| Czy dasz rade odgadnac wyraz o ktorym mysle? Jest zlozony z " << BCGame.GetHiddenWordLength();
	std::cout << " liter. |\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is not won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Byki = " << BullCowCount.Bulls;
		std::cout << ". Krowy = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Proba " << CurrentTry << " z " << BCGame.GetMaxTries();
		std::cout << ". Podaj slowo: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Wpisz slowo skladajace sie z " << BCGame.GetHiddenWordLength() << " liter.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Wpisz slowo bez powtarzajacych sie liter.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Wyraz musi sie skladac tylko z malych liter.\n\n";
			break;
		default:
			// assume the guess is valid
			break; }
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Czy chcesz zagrac jeszcze raz z tym samym, ukrytym wyrazem? (tak/nie) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'tak') || (Response[0] == 't');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "|            /~~~~~\        /~~~~~\                    " << std::endl;
		std::cout << "|           |    (~'        ~~~)   |                   " << std::endl;
		std::cout << "|            \    \__________/    /                    " << std::endl;
		std::cout << "|            / ~::::::::         ~\                    " << std::endl;
		std::cout << "| /~~~~~~~-_|  ::::::::            |_-~~~~~~~\         " << std::endl;
		std::cout << "|\ ======= /|   ::A::;      A     :|\ ====== /         " << std::endl;
		std::cout << "| ~-_____-~ |  _----------------_::| ~-____-~          " << std::endl;
		std::cout << "|           |/~                  ~\|                   " << std::endl;
		std::cout << "|           /                      \                   " << std::endl;
		std::cout << "|          (        ()    ()        )                  " << std::endl;
		std::cout << "|           `\                   ./'                   " << std::endl;
		std::cout << "|             ~-_______________-~                      " << std::endl;
		std::cout << "|                   /~~~~\                             " << std::endl;
		std::cout << "|                  |      |                            " << std::endl;
		std::cout << "|                  |      |                            " << std::endl;
		std::cout << "|                 (________)                           " << std::endl;
		std::cout << "|                     ()                               " << std::endl;
		std::cout << "|                                                      " << std::endl;
		std::cout << "|              BRAWO - WYGRYWASZ!                      " << std::endl;
		std::cout << "|                                                    \n";
	}
	else
	{
		std::cout << "                                        " << std::endl;
		std::cout << "     db               db                " << std::endl;
		std::cout << "    d88                d88              " << std::endl;
		std::cout << "   888                  888             " << std::endl;
		std::cout << "  d88                   88b             " << std::endl;
		std::cout << "  888                  88P              " << std::endl;
		std::cout << "  Y888b  /`````````\  8888              " << std::endl;
		std::cout << ",----Y888           Y88P`````\          " << std::endl;
		std::cout << "|         ,'`\_/``\  |,,    |           " << std::endl;
		std::cout << " \,,,,-|  | o | o /  |  ```'            " << std::endl;
		std::cout << "       |   """ """   |                  " << std::endl;
		std::cout << "      |               |                 " << std::endl;
		std::cout << "     |                 |                " << std::endl;
		std::cout << "     |  ,,,,-----,,,,  |                " << std::endl;
		std::cout << "     |``   @    @    ``|                " << std::endl;
		std::cout << "      \,,    ___    ,,/                 " << std::endl;
		std::cout << "         \__|   |__/                    " << std::endl;
		std::cout << "            | | |                       " << std::endl;
		std::cout << "            \_|_/                       " << std::endl;
		std::cout << "                                        " << std::endl;
		std::cout << "        NIE UDALO SIE...                " << std::endl;
		std::cout << "  Powodzenia przy kolejnej probie!      " << std::endl;
		std::cout << "                                      \n";
	}
}
