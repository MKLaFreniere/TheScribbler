//Mark LaFreniere
//Creation Date: 4/26/2020
//Modification Date: 4/29/2020
// A fun word scrambler game! (With header file)
#include<algorithm>
#include<string>
#include"words.h"
using namespace std;

Word::Word()
{
	definition = "";
	questionWord = "";
	option1 = "";
	option2 = "";
	option3 = "";
}

void Word::SetDefinition(string newWord)
{
	definition = newWord;
}

string Word::GiveDefinition()
{
	return definition;
}

string Word::GiveQuestion(char easyMode)
{
	std::string scrabbledWord;

	scrabbledWord = definition;

	if (easyMode == 'y') 
	{
		scrabbledWord.at(0) = toupper(scrabbledWord.at(0));
	}

	std::random_shuffle(scrabbledWord.begin(),scrabbledWord.end());

	return scrabbledWord;
}

void Word::GenerateOptionQs()
{
	std::string scrabbledWord1;
	std::string scrabbledWord2;
	std::string scrabbledWord3;

	scrabbledWord1 = definition;
	scrabbledWord2 = definition;
	scrabbledWord3 = definition;

	std::random_shuffle(scrabbledWord1.begin(), scrabbledWord1.end());
	std::random_shuffle(scrabbledWord2.begin(), scrabbledWord2.end());
	std::random_shuffle(scrabbledWord3.begin(), scrabbledWord3.end());

	option1 = scrabbledWord1;
	option2 = scrabbledWord2;
	option3 = scrabbledWord3;
}

string Word::GiveOption1()
{
	return option1;
}

string Word::GiveOption2()
{
	return option2;
}

string Word::GiveOption3()
{
	return option3;
}