//Mark LaFreniere
//Creation Date: 4/26/2020
//Modification Date: 8/3/2020
// A fun set of word games!
#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include<vector>
#include<ctime>
#include<limits>
#include"words.h"
using namespace std;

void PrintMenu();
void PrintSizeMenu();
void PrintLine();
void InputFile(vector<Word>&);
bool CheckFile(std::ifstream& pFile);
string WordFinder(char, vector<Word>&, int&);
void ScrabbleGame(string, int, vector<Word>&, char);
void ScrabbleSingleplayer(vector<Word>&, char);
void ScrabbleMultiplayer(char);
void HangmanGUI(int);
void HangmanGame(string, char);
void HangmanSingleplayer(vector<Word>&, char originalMenu);
void HangmanMultiplayer(char);

int main()
{
	char menu = '0';
	vector<Word> Scrabble;   //Scrabble is the default vector for all funcitons, whether they be scrabble or not.
	
	srand(time(NULL));
	
	while (menu != '6') 
	{
		PrintMenu();
		cin >> menu;

		switch (menu) 
		{
			case '1':
				PrintLine();
				InputFile(Scrabble);
				break;

			case '2':
				PrintLine();
				ScrabbleSingleplayer(Scrabble, menu);
				break;

			case '3':
				PrintLine();
				ScrabbleMultiplayer(menu);
				break;

			case '4':
				PrintLine();
				HangmanSingleplayer(Scrabble, menu);
				break;

			case '5':
				PrintLine();
				HangmanMultiplayer(menu);
				break;

			case '6':
				PrintLine();
				cout << "  Closing The Scribbler! See you later!" << endl << endl;
				break;

			default:
				PrintLine();
				cout << "  Please input a valid option!" << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}

//Purpose: Prints the main menu
void PrintMenu()
{
	cout << "--------------THE SCRIBBLER MENU--------------" << endl << endl;
	cout << "  1. Input Single Player Words!" << endl;
	cout << "  2. Scrambled (Single Player)" << endl;
	cout << "  3. Scrambled (Multiplayer)" << endl;
	cout << "  4. Hangman (Singleplayer)" << endl;
	cout << "  5. Hangman (Multiplayer)" << endl;
	cout << "  6. Quit" << endl;
	cout << "  > ";
}

//Purpose: Prints the word size option menu
void PrintSizeMenu()
{
	cout << "  What setting will you play on?" << endl;
	cout << "  1. Small (3-5 letters)" << endl;
	cout << "  2. Medium (6-8 letters)" << endl;
	cout << "  3. Large (9-11 letters)" << endl;
	cout << "  4. Omg (12+ letters!)" << endl;
	cout << "  5. Random (Any size!)" << endl;
	cout << "  6. Back to main menu" << endl;
	cout << "  > ";
}

//Purpose: Prints a simple line
void PrintLine()
{
	cout << "----------------------------------------------" << endl << endl;
}

//Purpose: Reads an file inputted by the user and puts it into the Scrabble vector
void InputFile(vector<Word> &Scrabble)
{
	ifstream ifs;
	string inFile;
	vector<Word> tmpVec(1);
	string tmpStr;
	char quickMenu = '0';
	bool fileEmpty;

	if (Scrabble.size() > 0)
	{
		cout << "  You have already read a file." << endl;
		cout << "  Read a new one? y/n: ";
		cin >> quickMenu;

		cout << endl;

		quickMenu = tolower(quickMenu);

		if (quickMenu == 'y')
		{
			Scrabble.clear();
		}
		else
		{
			return;
		}
	}

	cout << "  Type \"Default\"" << endl;
	cout << "  Or create your own.txt file of words!" << endl;
	cout << endl << "  Input file: ";

	cin >> inFile;

	inFile.append(".txt");

	ifs.open(inFile);
	
	if (!ifs.is_open())
	{
		cerr << "  Your input file could not be read" << endl << endl;
		system("pause");
		cout << endl << endl;
		return;
	}

	fileEmpty = CheckFile(ifs);

	if (fileEmpty == true)
	{
		cout << "  Your text file is empty!" << endl << endl;

		system("pause");
		cout << endl << endl;
		return;
	}

	while (!ifs.eof())
	{
		ifs >> tmpStr;
			
		tmpVec[0].SetDefinition(tmpStr);

		Scrabble.push_back(tmpVec[0]);
	}

	cout << "  Your file has been read :)" << endl << endl;
	system("pause");
	cout << endl << endl;

	ifs.close();

	return;
}

//Purpose: Checks if an inputted file is empty
bool CheckFile(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

//Purpose: Finds a word for a given word game
string WordFinder(char limitDecider, vector<Word>& wordMatrix, int& wordIndex)
{
	int count = 0;			//ADD counter to each menu option. If exceeds 10000, then abort
	string qWord = "0";
	int lowerLimit = 0;
	int upperLimit = 0;

	switch (limitDecider) 
	{
		case '1':
			lowerLimit = 3;
			upperLimit = 5;
			break;

		case '2':
			lowerLimit = 6;
			upperLimit = 8;
			break;
			
		case '3':
			lowerLimit = 9;
			upperLimit = 11;
			break;

		case '4':
			lowerLimit = 12;
			upperLimit = INT_MAX;
			break;

		case '5':
			lowerLimit = 3;
			upperLimit = INT_MAX;
			break;

		case '6':
			return "0";

		default:
			PrintLine();
			cout << "Invalid option! D:" << endl << endl;
			system("pause");
			cout << endl << endl;
			return "0";
	}

	do {
		wordIndex = (rand() % wordMatrix.size());
		qWord = wordMatrix[wordIndex].GiveDefinition();

		count++;
		if (count == 10000)
		{
			PrintLine();
			cout << "  Could not find a word of that size!" << endl;
			cout << "  Please check your .txt" << endl << endl;

			system("pause");
			cout << endl << endl;
			return "0";
		}
	} while ((qWord.size() < lowerLimit) || (qWord.size() > upperLimit));

	return qWord;
}

//Initiates the base Scrabble game
void ScrabbleGame(string qWord, int wordIndex, vector<Word>& Scrabble, char originalMenu)
{
	string userAnswer;

	if (originalMenu == '3')	// If multiplayer was chosen, the program will skip lines
	{
		for (int i = 0; i < 200; i++)
		{
			cout << endl;
		}
	}
	
	cout << "      " << qWord << endl << endl;

	for (int i = 3; i > 0; i--)
	{
		cout << "  Answer (Chances: " << i << "): ";
		cin >> userAnswer;

		userAnswer.at(0) = tolower(userAnswer.at(0));

		if (userAnswer == Scrabble[wordIndex].GiveDefinition())
		{
			PrintLine();
			cout << "  Correct! Nice job!" << endl;

			if (i == 1)
			{
				cout << "  That was close!" << endl << endl;

				system("pause");
				cout << endl << endl;
				return;
			}

			cout << endl;
			system("pause");
			cout << endl << endl;
			return;
		}
	}

	PrintLine();
	cout << "  Better luck next time!" << endl << "  The answer was: " << Scrabble[wordIndex].GiveDefinition() << endl << endl;

	system("pause");
	cout << endl << endl;

	return;
}

//Purpose: Starts the Singleplayer mode (uses an input file)
void ScrabbleSingleplayer(vector<Word>& Scrabble, char originalMenu)
{
	if (Scrabble.size() == 0)
	{
		cout << "  You haven't inputted a file yet!" << endl << endl;
		system("pause");
		cout << endl << endl;
		return;
	}

	char ezMode;
	char quickMenu;
	int wordIndex;
	string qWord;
	
	PrintSizeMenu();
	cin >> quickMenu;

	qWord = WordFinder(quickMenu, Scrabble, wordIndex);

	if (qWord == "0")
	{
		return;
	}

	PrintLine();
	cout << "  Enable Easy Mode? (y/n): ";
	cin >> ezMode;

	PrintLine();

	qWord = Scrabble[wordIndex].GiveQuestion(ezMode);
	
	ScrabbleGame(qWord, wordIndex, Scrabble, originalMenu);

	return;
}

//Purpose: Starts Multiplayer mode
void ScrabbleMultiplayer(char originalMenu)
{
	string plr1Word;
	string plr1Question;
	vector<Word> multiScrabble(1);
	char quickMenu;
	int wordIndex = 0;

	cout << "  Hide the screen from player 2!" << endl << endl;
	system("pause");
	cout << endl;

	PrintLine();

	cout << "  Type in your word, player 1: ";
	cin >> plr1Word;
	
	multiScrabble[0].SetDefinition(plr1Word);
	multiScrabble[0].GenerateOptionQs();
	
	PrintLine();
	cout << "  Here are your choices: " << endl;
	cout << "  1. " << multiScrabble[0].GiveOption1() << endl;
	cout << "  2. " << multiScrabble[0].GiveOption2() << endl;
	cout << "  3. " << multiScrabble[0].GiveOption3() << endl;
	cout << "  > ";
	cin >> quickMenu;

	PrintLine();

	switch (quickMenu)
	{
		case '1':
			plr1Question = multiScrabble[0].GiveOption1();
			break;

		case '2':
			plr1Question = multiScrabble[0].GiveOption2();
			break;

		case '3':
			plr1Question = multiScrabble[0].GiveOption3();
			break;

		default:
			cout << "Invalid option! D:" << endl << endl;
			system("pause");
			cout << endl << endl;
			return;
	}

	ScrabbleGame(plr1Question, wordIndex, multiScrabble, originalMenu);

	return;
}

//Purpose: Displays the hangman pictures
void HangmanGUI(int errorCount)
{
	switch (errorCount)
	{
	case 0:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 1:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 2:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                      |    |" << endl;
		cout << "                           |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 3:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                      |    |" << endl;
		cout << "                       \\   |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 4:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                      |    |" << endl;
		cout << "                     / \\   |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 5:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                     /|    |" << endl;
		cout << "                     / \\   |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;

	case 6:
		cout << "                      ______" << endl;
		cout << "                      |    |" << endl;
		cout << "                      O    |" << endl;
		cout << "                     /|\\   |" << endl;
		cout << "                     / \\   |" << endl;
		cout << "                           |" << endl;
		cout << "                 __________|____" << endl;
		break;
	}

	return;
}

//Purpose: Initiates the base hangman game
void HangmanGame(string qWord, char originalMenu)
{
	char userAnswer;
	int vecCols = 2;
	int errorCount = 0;
	vector<char> mistakes;
	bool correctAnswer = false;
	bool writeBackTrigger;
	int completionCounter = 0;

	for (int i = 0; i < qWord.size(); i++)
	{
		qWord.at(i) = tolower(qWord.at(i));
	}

	PrintLine();

	if (originalMenu == '5')		// If multiplayer was chosen, the program will skip lines
	{
		for (int i = 0; i < 200; i++)
		{
			cout << endl;
		}
	}

	int vecRows = qWord.size();
	vector<vector<char>> hangmanMatrix;

	hangmanMatrix.resize(vecRows, vector<char>(vecCols, 0));

	for (int i = 0; i < vecRows; i++)
	{
		hangmanMatrix[i][0] = qWord.at(i);
	}

	for (int i = 0; i < vecRows; i++)
	{
		hangmanMatrix[i][1] = '-';
	}

	while (errorCount < 6)
	{
		HangmanGUI(errorCount);

		cout << endl << endl << "                      ";

		for (int i = 0; i < vecRows; i++)
		{
			cout << hangmanMatrix[i][1];
		}

		cout << endl << endl << "  Mistakes: ";

		if (mistakes.size() >= 1)
		{
			for (int i = 0; i < mistakes.size(); i++)
			{
				cout << mistakes[i];
			}

			cout << endl;
		}

		cout << endl;
		cout << "  > ";
		cin >> userAnswer;

		writeBackTrigger = false;

		for (int i = 0; i < vecRows; i++)
		{
			if (userAnswer == hangmanMatrix[i][0])
			{
				correctAnswer = true;
				writeBackTrigger = true;
			}

			if (correctAnswer == true)
			{
				hangmanMatrix[i][1] = hangmanMatrix[i][0];
				correctAnswer = false;
			}
		}

		if (writeBackTrigger == false)
		{
			mistakes.push_back(userAnswer);
			errorCount++;
		}

		for (int i = 0; i < vecRows; i++)
		{
			if (hangmanMatrix[i][0] == hangmanMatrix[i][1])
			{
				completionCounter++;
			}

			if (completionCounter == hangmanMatrix.size())
			{
				cout << endl;
				PrintLine();
				cout << "  Congrats! The word was indeed, " << qWord << "!" << endl << "  You did it! Great job!" << endl << endl;

				system("pause");
				cout << endl << endl;
				return;
			}
		}

		completionCounter = 0;
		PrintLine();
	}

	if (errorCount <= 6)
	{
		HangmanGUI(errorCount);
		cout << endl << "  He's a goner!" << endl << "  Better luck next time!" << endl << "  The word was: ";

		for (int i = 0; i < vecRows; i++)
		{
			cout << hangmanMatrix[i][0];
		}

		cout << endl << endl;

		system("pause");
		cout << endl << endl;
		return;
	}
}

//Purpose: Starts the singleplayer hangman game (uses an input file)
void HangmanSingleplayer(vector<Word>& Hangman, char originalMenu)
{
	if (Hangman.size() == 0)
	{
		cout << "  You haven't inputted a file yet!" << endl << endl;
		system("pause");
		cout << endl << endl;
		return;
	}

	int wordIndex;
	char quickMenu;
	string qWord;

	PrintSizeMenu();
	cin >> quickMenu;
	
	qWord = WordFinder(quickMenu, Hangman, wordIndex);

	if (qWord == "0")
	{
		return;
	}

	HangmanGame(qWord, originalMenu);

	return;
}

//Purpose: Starts the multiplayer hangman game
void HangmanMultiplayer(char originalMenu)
{
	string qWord;
	
	cout << "  Hide the screen from the other players!" << endl << endl;
	system("pause");
	cout << endl;

	PrintLine();

	cout << "  Player 1, please enter your word: ";
	cin >> qWord;
	cout << endl;
	
	HangmanGame(qWord, originalMenu);

	return;
}
