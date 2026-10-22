#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOP = 5 };

struct stAnswer
{
	short UserAnswer = 0;
	short RightAnswer = 0;

};


struct stFinalResults
{
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	string QuestionsLevelName;
	enOpType OpType;
	string OperationTypeName;
	short NumberOfWrongAnswer = 0;
	short NumberOfRightAnswer = 0;
	stAnswer Answer;
};



int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}


short ReadHowManyQuestions()
{
	short HowManyQuestions = 0;

	cout << " How Many Questions do you want to answer ? ";
	cin >> HowManyQuestions;

	return HowManyQuestions;

}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;
	do
	{
		cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;
	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}

enOpType ReadOperationType()
{
	short OperationType = 0;
	do
	{
		cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);

	return (enOpType)OperationType;
}

int ReadUserAnswer()
{
	int UserAnswer;
	cin >> UserAnswer;

	return UserAnswer;
}

void NumbersAccordingToQuestionLevel(stFinalResults FinalResults, short Num[2])
{
	switch (FinalResults.QuestionsLevel)
	{
	case enQuestionsLevel::Easy:
	{
		Num[0] = RandomNumber(1, 10);
		Num[1] = RandomNumber(1, 10);
		break;
	}

	case enQuestionsLevel::Med:
	{
		Num[0] = RandomNumber(10, 20);
		Num[1] = RandomNumber(10, 20);
		break;
	}

	case enQuestionsLevel::Hard:
	{
		Num[0] = RandomNumber(50, 100);
		Num[1] = RandomNumber(50, 100);
		break;
	}

	default:

		Num[0] = RandomNumber(1, 100);
		Num[1] = RandomNumber(1, 100);



	}


}

enOpType MixOperationType()
{
	short i = RandomNumber(1, 4);

	switch (i)
	{
	case 1:
	{

		return enOpType::Add;
		break;
	}

	case 2:
	{
		return enOpType::Sub;
		break;
	}

	case 3:
	{
		return enOpType::Mul;
		break;
	}

	default:
		return enOpType::Div;



	}

}

int GetRightAnswer(enOpType CurrentOp, short Num[2])
{
	switch (CurrentOp)
	{
	case enOpType::Add:
	{
		return Num[0] + Num[1];
		break;
	}

	case enOpType::Sub:
	{
		return Num[0] - Num[1];
		break;
	}

	case enOpType::Mul:
	{
		return Num[0] * Num[1];
		break;
	}

	case enOpType::Div:
	{
		return Num[0] / Num[1];
		break;
	}
	default:
		return 0;
	}

}

string QuestionsLevelName(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionsLevelName[4] = { "Easy","Med", "Hard", "Mix" };
	return arrQuestionsLevelName[QuestionsLevel - 1];
}


string OperationTypeName(enOpType OperationType)
{
	string arrOperationTypeName[5] = { "+", "-", "*", "/" , "Mix" };
	return arrOperationTypeName[OperationType - 1];
}


stFinalResults FillFinalResults(stFinalResults& FinalResults, short NumberOfRightAnswer, short NumberOfWrongAnswer)
{


	FinalResults.QuestionsLevelName = QuestionsLevelName(FinalResults.QuestionsLevel);
	FinalResults.OperationTypeName = OperationTypeName(FinalResults.OpType);
	FinalResults.NumberOfRightAnswer = NumberOfRightAnswer;
	FinalResults.NumberOfWrongAnswer = NumberOfWrongAnswer;


	return FinalResults;
}

string PassOrFail(stFinalResults FinalResults)
{
	if (FinalResults.NumberOfRightAnswer > FinalResults.NumberOfWrongAnswer)
	{
		return " Final Results is Pass :-)";
	}
	else
	{
		return " Final Results is Fail :-(";
	}
}

bool CalculatRightOrWrongAnswer(stAnswer Answer)
{
	return Answer.UserAnswer == Answer.RightAnswer;
}

void PrintRigtOrWrongAnswer(stAnswer Answer)
{
	if (CalculatRightOrWrongAnswer(Answer))
	{
		cout << "\nRight Answer :-)";
		system("color 2F");
	}
	else
	{
		cout << "\nWrong Answer :-(\n";
		cout << "The right answer is:  " << Answer.RightAnswer;
		system("color 4F");
		cout << "\a";
	}

}

void ShowPassOrFailScreen(stFinalResults FinalResults)
{
	cout << "\n\n\n____________________________________\n\n";

	cout << PassOrFail(FinalResults);

	cout << "\n____________________________________\n\n";

}

void PrintQuestions(short Num[2], short QNumber, short NumberOfQuestions, enOpType CurrentOp)
{
	cout << "\n\nQuestion  [" << QNumber << "/" << NumberOfQuestions << "]\n\n";

	cout << Num[0] << endl;

	cout << Num[1] << " " << OperationTypeName(CurrentOp) << endl << endl;
	cout << "________________\n";

}

stFinalResults PlayGame(short HowManyQuestions, short Num[2])
{
	stFinalResults FinalResults;

	short NumberOfRigtAnswer = 0, NumberOfRwongAnswer = 0;

	FinalResults.NumberOfQuestions = HowManyQuestions;
	FinalResults.QuestionsLevel = ReadQuestionsLevel();
	FinalResults.OpType = ReadOperationType();




	for (int QNumber = 1;QNumber <= HowManyQuestions;QNumber++)
	{
		enOpType CurrentOp;

		if (FinalResults.OpType == enOpType::MixOP)
			CurrentOp = MixOperationType();
		else
			CurrentOp = FinalResults.OpType;

		NumbersAccordingToQuestionLevel(FinalResults, Num);
		PrintQuestions(Num, QNumber, HowManyQuestions, CurrentOp);
		FinalResults.Answer.UserAnswer = ReadUserAnswer();
		FinalResults.Answer.RightAnswer = GetRightAnswer(CurrentOp, Num);
		PrintRigtOrWrongAnswer(FinalResults.Answer);

		if (CalculatRightOrWrongAnswer(FinalResults.Answer))
			NumberOfRigtAnswer++;
		else
			NumberOfRwongAnswer++;

	}
	return FillFinalResults(FinalResults, NumberOfRigtAnswer, NumberOfRwongAnswer);
}

void ShowFinalGameResults(stFinalResults FinalResults)
{

	cout << "Number of Questions: " << FinalResults.NumberOfQuestions << endl;
	cout << "Questions Level    : " << FinalResults.QuestionsLevelName << endl;
	cout << "OpType             : " << FinalResults.OperationTypeName << endl;
	cout << "Number of Right Answers: " << FinalResults.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answers: " << FinalResults.NumberOfWrongAnswer << endl;

	cout << "____________________________________\n\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame(short Num[2])
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();

		stFinalResults FinalResults = PlayGame(ReadHowManyQuestions(), Num);

		ShowPassOrFailScreen(FinalResults);
		ShowFinalGameResults(FinalResults);

		cout << "Do you Want To Play again?  Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));

	short Num[2];

	StartGame(Num);

	return 0;
}