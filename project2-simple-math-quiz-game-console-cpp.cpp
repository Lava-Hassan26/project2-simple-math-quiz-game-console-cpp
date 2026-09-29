#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Med, Hard, MixLevel };
enum enOperationType { Add = 1, Sub, Mul, Div, MixOperation };

struct stQuizInfo
{
    int number1 = 0;
    int number2 = 0;
    int userAnswer = 0;
    int rightAnswer = 0;
    bool isUserAnswerCorrect = 0;
    enQuestionLevel questionLevel = enQuestionLevel::Easy;
    enOperationType operationType = enOperationType::Add;
    enOperationType actualOpType = enOperationType::Add;
};

struct stFinalResults
{
    bool isPass = 0;
    short totalQuestions = 0;
    enQuestionLevel questionLevel = enQuestionLevel::Easy;
    enOperationType operationType = enOperationType::Add;
    short rightAnswersCount = 0;
    short wrongAnswersCount = 0;
};

int GetRandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

short ReadHowManyQuestions()
{
    short questions = 0;
    
    cout << "How Many Questions Do You Want? ";
    cin >> questions;
   
    return questions;
}

enQuestionLevel ReadQuestionLevel()
{
    short questionLevel = 0;
    do
    {
        cout << "\nEnter Questions Level [1]: Easy, [2]: Mid, [3]: Hard, [4]: Mix? ";
        cin >> questionLevel;
    } while (questionLevel < 1 || questionLevel > 4);

    return (enQuestionLevel)questionLevel;
}

enOperationType ReadOperationType()
{
    short operationType = 0;
    do
    {
        cout << "\nEnter Operation Type [1]: Add, [2]: Sub, [3]: Mul, [4]: Div, [5]: Mix? ";
        cin >> operationType;
    } while (operationType < 1 || operationType > 5);

    return (enOperationType)operationType;
}

int ReadUserAnswer()
{
    int answer = 0;
    cin >> answer;
    return answer;
}

string QuestionLevelToString(enQuestionLevel questionLevel)
{
    switch (questionLevel)
    {
    case enQuestionLevel::Easy:
        return "Easy";
    case enQuestionLevel::Med:
        return "Med";
    case enQuestionLevel::Hard:
        return "Hard";
    case enQuestionLevel::MixLevel:
        return "Mix";
    default:
        return "Unknown";
    }
}

char OperationTypeToChar(enOperationType operationType)
{
    switch (operationType)
    {
    case enOperationType::Add:
        return '+';
    case enOperationType::Sub:
        return '-';
    case enOperationType::Div:
        return '/';
    case enOperationType::Mul:
        return '*';
    default:
        return '+';
    }
}

string OperationTypeToString(enOperationType operationType)
{
    switch (operationType)
    {
    case enOperationType::Add:
        return "Addition";
    case enOperationType::Sub:
        return "Subtraction";
    case enOperationType::Div:
        return "Division";
    case enOperationType::Mul:
        return "Multiplication";
    case enOperationType::MixOperation:
        return "Mix";
    }
}

int GenerateRandomNumberByLevel(enQuestionLevel questionLevel)
{
    switch (questionLevel)
    {
    case  enQuestionLevel::Easy:
        return GetRandomNumber(1, 20);

    case enQuestionLevel::Med:
        return GetRandomNumber(21, 50);

    case enQuestionLevel::Hard:
        return GetRandomNumber(51, 100);

    case enQuestionLevel::MixLevel:
        return GetRandomNumber(1, 100);
    }
}

void GenerateOperationType(stQuizInfo& quizInfo)
{
    if (quizInfo.operationType == enOperationType::MixOperation)
        quizInfo.actualOpType = (enOperationType)GetRandomNumber(1, 4);
    else
        quizInfo.actualOpType = quizInfo.operationType;
}

stQuizInfo GenerateQuestionNumbers(stQuizInfo& quizInfo)
{
    quizInfo.number1 = GenerateRandomNumberByLevel(quizInfo.questionLevel);
    quizInfo.number2 = GenerateRandomNumberByLevel(quizInfo.questionLevel);
    return quizInfo;
}

int Calculate(stQuizInfo& quizInfo)
{
    switch (quizInfo.actualOpType)
    {
    case enOperationType::Add:
        return quizInfo.number1 + quizInfo.number2;

    case enOperationType::Sub:
        return quizInfo.number1 - quizInfo.number2;

    case enOperationType::Mul:
        return quizInfo.number1 * quizInfo.number2;

    case enOperationType::Div:
        if (quizInfo.number2 != 0)
            return quizInfo.number1 / quizInfo.number2;
        else
            return 0;
    default:
        return 0;
    }
}

void PrintQuestionResult(stQuizInfo& quizInfo)
{
    if(quizInfo.isUserAnswerCorrect)
    {
        cout << "Right Answer\n";
        system("color A0");
    }
    else
    {
        cout << "Wrong Answer\n";
        cout << "The Right Answer is: " << quizInfo.rightAnswer << endl;
        system("color C0");
        cout << "\a";
    }
}

bool IsUserAnswerTrue(stQuizInfo& quizInfo)
{
    return quizInfo.rightAnswer == quizInfo.userAnswer;
}

void PrintQuestion(stQuizInfo& quizInfo)
{
    cout << quizInfo.number1 << endl;
    cout << "\t" << OperationTypeToChar(quizInfo.actualOpType) << endl;
    cout << quizInfo.number2 << endl;
    cout << "___________\n";
    quizInfo.userAnswer = ReadUserAnswer();
}

void EvaluateAndPrintQuestionResult(stQuizInfo& quizInfo)
{
    quizInfo.rightAnswer = Calculate(quizInfo);
    quizInfo.isUserAnswerCorrect = IsUserAnswerTrue(quizInfo);
    PrintQuestionResult(quizInfo);
}

stQuizInfo PrepareQuizInfo()
{
    stQuizInfo quizInfo;
    quizInfo.questionLevel = ReadQuestionLevel();
    quizInfo.operationType = ReadOperationType();
    return quizInfo;
}

void IncrementAnswersCount(stQuizInfo& quizInfo, stFinalResults& finalResults)
{
    if (quizInfo.isUserAnswerCorrect)
        finalResults.rightAnswersCount++;
    else
        finalResults.wrongAnswersCount++;
}

string IsPassToString(bool isPass)
{
    if (isPass)
    {
        system("color A0");
        return "Pass";
    }
    else
    {
        system("color C0");
        cout << "\a";
        return "Fail";
    }
}

bool IsQuizPassed(stFinalResults& finalResults)
{
    return (finalResults.rightAnswersCount >= finalResults.wrongAnswersCount);
}

stFinalResults StartQuiz(short totalQuestions)
{
    stQuizInfo quizInfo;
    stFinalResults finalResults;
    quizInfo = PrepareQuizInfo();
    for (short i = 1; i <= totalQuestions; i++)
    {
        cout << "\nQuestion[" << i << "]:\n";  
        GenerateQuestionNumbers(quizInfo);
        GenerateOperationType(quizInfo);
        PrintQuestion(quizInfo);
        EvaluateAndPrintQuestionResult(quizInfo);
        IncrementAnswersCount(quizInfo, finalResults);
    }
    finalResults.totalQuestions = totalQuestions;
    finalResults.operationType = quizInfo.operationType;
    finalResults.questionLevel = quizInfo.questionLevel;
    finalResults.isPass = IsQuizPassed(finalResults);
    
    return finalResults;
}

void PrintFinalResults(stFinalResults& finalResults)
{
    cout << "\n\n____________________________________________\n\n";
    cout << " Final Result is: " << IsPassToString(finalResults.isPass);
    cout << "\n____________________________________________\n\n";
    cout << "Number Of Questions    : " << finalResults.totalQuestions << endl;
    cout << "Question Level         : " << QuestionLevelToString(finalResults.questionLevel) << endl;
    cout << "Operation Type         : " << OperationTypeToString(finalResults.operationType) << endl;
    cout << "Number Of Right Answers: " << finalResults.rightAnswersCount << endl;
    cout << "Number Of Wrong Answers: " << finalResults.wrongAnswersCount << endl;
    cout << "____________________________________________\n";
}

void ResetScreen()
{
    system("cls");
    system("color 07");
}

void PlayGame()
{
    ResetScreen();
    short totalQuestions = ReadHowManyQuestions();
    stFinalResults finalResults = StartQuiz(totalQuestions);
    PrintFinalResults(finalResults);
}

void StartGame()
{
    char playAgain = 'Y';
    do
    {
        PlayGame();
        cout << "\nDo you want to play again [Y/N]? ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}