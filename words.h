//Mark LaFreniere
//Creation Date: 4/26/2020
//Modification Date: 4/29/2020
// A fun word scrambler game! (Header file)
#include<string>
using namespace std;
#ifndef WORDS_H
#define WORDS_H

class Word
{
private:
	string definition;
	string questionWord;
	string option1;
	string option2;
	string option3;
public:
	Word();
	void SetDefinition(string);
	string GiveDefinition();
	string GiveQuestion(char);
	void GenerateOptionQs();
	string GiveOption1();
	string GiveOption2();
	string GiveOption3();
};
#endif
