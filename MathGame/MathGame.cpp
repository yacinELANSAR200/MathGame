#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <string>
using namespace std;


enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp=5 };

struct stQuestion {
    short Number1 = 0;
    short Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short PlayerAnswer;
    short CorrectAnswer;
    bool AnswerResult = false;
};

struct stQuiz {
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool GameResult = false;
};

short ReadPositiveNumberInRange(string Message, short From, short To) {
    short number = 0;
    do
    {
        cout << Message;
        cin >> number;
    } while (number < 0 || number<From || number>To);
    return number;
}

enQuestionLevel ReadUserChoiceQuestionLevel(short From, short To) {
    string Message = "Enter Question Level [1]Easy [2]Medium [3]Hard [4]Mix ? ";
    return (enQuestionLevel)ReadPositiveNumberInRange(Message,From,To);
}

enOperationType ReadUserOperationType(short From, short To) {
    string Message = "Enter Operation Type [1]Add  [2]Sub  [3]Mul  [4]Div  [5]Mix ? ";
    return (enOperationType)ReadPositiveNumberInRange(Message, From, To);
}

int ReadAnswerUser() {
    int Answer =0;
    cin >> Answer;
    return Answer;
}

int RandomNumber(int From, int To) {
    int RandNum = rand() % (To + 1 - From) + From;
    return RandNum;
}

short ReadHowManyQuestions() {
    short NumberOfQuestions = 0;
    do
    {
        cout << "How Many Questions do you want to answer? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1);
    return NumberOfQuestions;
}

int SimpleCalculator(int Number1, int Numbe2, enOperationType opType) {
    switch (opType)
    {
    case Add:return Number1 + Numbe2;
        break;
    case Sub:return Number1 - Numbe2;
        break;
    case Mul:return Number1 * Numbe2;
        break;
    case Div:return Number1 / Numbe2;
        break;
    default:return Number1 + Numbe2;
        break;
    }
}

stQuestion GenerateQuestion(enOperationType opType, enQuestionLevel QuestionLevel) {
    stQuestion  Question;

    if (opType==enOperationType::MixOp)
    {
        opType = (enOperationType)RandomNumber(1, 4);
    }
    if (QuestionLevel==enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1,5);
    }
    Question.OperationType = opType;
    Question.QuestionLevel = QuestionLevel;
    switch (QuestionLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    case Medium:
        Question.Number1 = RandomNumber(20, 50);
        Question.Number2 = RandomNumber(20, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    }
    return Question;
}

void GenerateQuizzQuestions(stQuiz& Quiz) {

    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question]= GenerateQuestion(Quiz.OperationType,Quiz.QuestionLevel);
    }
}

string GetOperatorSymbol(enOperationType opType) {
    switch (opType)
    {
    case Add:return "+";
        break;
    case Sub:return "-";
        break;
    case Mul:return "*";
        break;
    case Div:return "/";
        break;
    default:return "Mix";
        break;
    }
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    switch (QuestionLevel)
    {
    case Easy:return "Easy";
        break;
    case Medium:return "Medium";
        break;
    case Hard:return "Hard";
        break;
    case Mix:return "Mix";
        break;
    default:
        break;
    }
}
void PrintQuestion(stQuiz Quiz, short Question) {
    cout << "\n";
    cout << "Question[" << Question + 1 << "/" << Quiz.NumberOfQuestions << "]\n";
    cout << Quiz.QuestionList[Question].Number1 << "\n";
    cout << Quiz.QuestionList[Question].Number2 << GetOperatorSymbol(Quiz.QuestionList[Question].OperationType) << "\n";
    cout << "_________" << endl;
}
void SetScreenColor(bool Answer) {
    switch (Answer) {
    case true:
        system("color 2F");
        break;
    case  false:
        system("color 4F");
        cout << "\a";
        break;
    }
}
void CorrectTheQuestionAnswer(stQuiz& Quiz, short Question) {
    if (Quiz.QuestionList[Question].CorrectAnswer != Quiz.QuestionList[Question].PlayerAnswer) {
        cout << "Wrong Answer :-(\n";
        cout << "The right Answer is " << Quiz.QuestionList[Question].CorrectAnswer;
        Quiz.QuestionList[Question].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;
    }
    else {
        cout << "Right Answer :-)\n";
        Quiz.QuestionList[Question].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;
    }
    SetScreenColor(Quiz.QuestionList[Question].AnswerResult);
}

string GetFinalResultsTexT(bool Pass) {
    if (Pass)
    {
        return "Pass :-)\n";
    }
    else {
        return "Fail :-(\n";
    }
}
void AskAndCorrectQuestionListAnswers(stQuiz& Quiz) {
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        PrintQuestion(Quiz,Question);
        Quiz.QuestionList[Question].PlayerAnswer = ReadAnswerUser();
        CorrectTheQuestionAnswer(Quiz, Question);
    }
    Quiz.GameResult = (Quiz.NumberOfRightAnswers > Quiz.NumberOfWrongAnswers);
}

void PrintQuizzResults(stQuiz Quiz) {
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Results is " <<
        GetFinalResultsTexT(Quiz.GameResult);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << "OpType             : " << GetOperatorSymbol(Quiz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}
void PlayGame() {
    stQuiz Quiz;
    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadUserChoiceQuestionLevel(1,4);
    Quiz.OperationType = ReadUserOperationType(1, 5);
    GenerateQuizzQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizzResults(Quiz);
}





void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = ' ';
    do
    {
        ResetScreen();
        PlayGame();
        cout << endl << "\t\t" << "Do you want to play again? Y/N? "; 
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}

