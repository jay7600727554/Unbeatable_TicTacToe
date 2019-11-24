#include<iostream>
#include<windows.h> //For using system methods
#include<conio.h>   //For using _getch()
#include<ctime>     //For setting time for random function

using namespace std;

//Shown at top of every screen
void welcome()
{
    system("CLS");
    cout << "Welcome to Tic-Tac-Toe by Jay" << endl;
    cout << "-----------------------------" << endl << endl;
}

//Instruction function. Shown only first time
void instruction()
{
    welcome();
    cout << "This is board: " << endl << endl;
    cout << "       |       |       " << endl;
    cout << "   1   |   2   |   3   " << endl;
    cout << "       |       |       " << endl;
    cout << "-----------------------" << endl;
    cout << "       |       |       " << endl;
    cout << "   4   |   5   |   6   " << endl;
    cout << "       |       |       " << endl;
    cout << "-----------------------" << endl;
    cout << "       |       |       " << endl;
    cout << "   7   |   8   |   9   " << endl;
    cout << "       |       |       " << endl << endl;
    cout << "To put your mark press key representing the position from above figure" << endl;
    system("pause");
}

//Show playing board with marks
void displayBoard(char posArr[9])
{
    cout << endl;
    cout << "       |       |       " << endl;
    cout << "   " << posArr[0] << "   |   " << posArr[1] << "   |   " << posArr[2] << "   " << endl;
    cout << "       |       |       " << endl;
    cout << "-----------------------" << endl;
    cout << "       |       |       " << endl;
    cout << "   " << posArr[3] << "   |   " << posArr[4] << "   |   " << posArr[5] << "   " << endl;
    cout << "       |       |       " << endl;
    cout << "-----------------------" << endl;
    cout << "       |       |       " << endl;
    cout << "   " << posArr[6] << "   |   " << posArr[7] << "   |   " << posArr[8] << "   " << endl;
    cout << "       |       |       " << endl << endl;
}

//Function to get Humans choice of mark
char getHumanMark()
{
    char mark;
    welcome();
    cout << "Enter your mark -> ";
    mark = _getch(); // Used getch() instead of cin so that user need not press enter after input
    cout << mark;
    return mark;
}

//function to get computers marked
char getCompMark(char hm) // hm = HUman Mark
{
    if (hm == 'X' || hm == 'x')
        return 'O';
    else
        return 'X';
}

//One time called function to display marks after selection
void displayMarks(char hm, char cm)
{
    welcome();
    cout << "Your mark is '" << hm << "' and Computer's mark is '" << cm << "'" << endl;
    system("pause");
}

//function to print score of the game
void printScore(int score[3])
{
    cout << "Score: Human = " << score[0] << ", Computer = " << score[1] << ", Draw = " << score[2] << endl;
}


//This function clears screen,
//Display welcome message,
//print current score and then display the game board

void displayGame(int score[3], char posArr[9])
{
    welcome();
    printScore(score);
    displayBoard(posArr);
}

//A function to check if anybody is a winner
//Returns mark of the winner or null
char winner(char posArr[9])
{
    for(int i = 0; i < 7; i+=3)  //Check all rows for same mark
    {
        if(posArr[i]!=0 && posArr[i+1]!=0 && posArr[i+2]!=0)
            if(posArr[i] == posArr[i+1] && posArr[i+1] == posArr[i+2])
                return posArr[i];
    }
    for(int i = 0; i < 3; i++)  //Check all columns for same mark
    {
        if(posArr[i]!=0 && posArr[i+3]!=0 && posArr[i+6]!=0)
            if(posArr[i] == posArr[i+3] && posArr[i+3] == posArr[i+6])
                return posArr[i];
    }

    //Check both diagonals
    if(posArr[0]!=0 && posArr[4]!=0 && posArr[8]!=0)
            if(posArr[0] == posArr[4] && posArr[4] == posArr[8])
                return posArr[0];
    if(posArr[2]!=0 && posArr[4]!=0 && posArr[6]!=0)
            if(posArr[2] == posArr[4] && posArr[4] == posArr[6])
                return posArr[2];

    //Check for not draw (some empty position)
    for(int i = 0; i < 9; i++)
        if(posArr[i] == '\0')
            return '\0'; //returns null if no one is winner

    return 'd'; //Draw
}

//Apply minimax algorith
//Maximise the score for computers turn
//Minimise the score for humans turn
int getScore(char posArr[9], char humanMark, char compMark, int turn, int l)
{
    char posArr2[9];
    int score, score1;

    char win = winner(posArr);
    if(win == compMark)
        return 100-l;
    else if(win == humanMark)
        return -(100-l);
    else if(win == 'd')
        return 0;

    if(turn == 0) //Human's turn
    {
        score1 = 1000;
        for (int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                posArr2[j] = posArr[j];
            if(posArr2[i] == '\0') //Find an empty space
            {
                posArr2[i] = humanMark; //Check the score if move is made on that empty space
                score = getScore(posArr2, humanMark, compMark, 1, l+1);
                if(score < score1)
                    score1 = score; //Return the minimum score
            }
        }
    }
    else  //Computers turn
    {
        score1 = -1000;
        for (int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                posArr2[j] = posArr[j];
            if(posArr2[i] == '\0')  //Find empty space
            {
                posArr2[i] = compMark;  //Check the score if move is made on that empty space
                score = getScore(posArr2, humanMark, compMark, 0, l+1);
                if(score > score1)
                    score1 = score;  //Return the maximum score
            }
        }
    }
    return score1;
}

//Compute the computers move
int compMove(char posArr[9], char humanMark, char compMark)
{
    char posArr2[9];
    int score[9];
    for(int i = 0; i < 9; i++)
    {
        score[i] = -1000;
    }
    int maxScore;
    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
            posArr2[j] = posArr[j];
        if(posArr2[i] == '\0') //Find emppty space
        {
            posArr2[i] = compMark;  //Check score for this position
            score[i] = getScore(posArr2, humanMark, compMark, 0, 0);
        }
    }

    //Return maximize score's index (its computer score)
    maxScore = 0;
    for(int i = 1; i < 9; i++)
    {
        if(score[maxScore] < score[i])
        {
            maxScore = i;
        }
    }
    return maxScore;
}

//Function that control game
//Return 'h' if human wins, 'c' if comp wins and 'd' if draw
char startGame(int score[3], char humanMark, char compMark)
{
    int turn;  //Turn 0 = human, 1 = comp
    int position; //position in between 0 to 8
    char temp;
    char posArr[9] = {'\0'}; //Array that saves mark of human and comp
    char win = '\0';    //char to save winners mark
    srand(time(0));     //Set random timer
    turn = rand() % 2;  //Randomize the turn
    for(int i = 0; i < 9; i++)
    {
        displayGame(score, posArr);
        if(turn == 0)
        {
            do
            {
                cout << "Human's turn: ";
                temp = _getch();                //Input integer position as char (because of getch())
                position = (int)temp - 48;      //Converting char to int
                position--;                     //Human's position start from 1, comps start from 0
                cout << "\r";                   //In case of invalid input we want to ask for input again on same line so use '\r'
            } while(posArr[position] != '\0' || position < 0 || position > 9);
            posArr[position] = humanMark;       //Put human mark
            turn = 1;                           //Change the turn
            displayGame(score, posArr);
            cout << "Human's turn: " << position+1 << endl;
        }
        else
        {
            position = compMove(posArr, humanMark, compMark);   //Get computers move
            posArr[position] = compMark;                        //Put computers mark
            turn = 0;                                           //Change the turn
            displayGame(score, posArr);
            cout << "Computer's turn: " << position+1 << endl;
        }
        win = winner(posArr);                   //Check if game is over
        if(win == humanMark)
            return 'h';
        else if(win == compMark)
            return 'c';
        Sleep(1000);
    }
    return 'd';
}


//Main driver program
int main()
{
    int score[3] = {0};                             //Array to keep score
    char humanMark, compMark, playAgain, winner;
    instruction();                                  //Show instructions
    humanMark = getHumanMark();                     //Get humans mark
    compMark = getCompMark(humanMark);              //Get computers mark
    displayMarks(humanMark, compMark);              //Display both marks
    do
    {
        winner = startGame(score, humanMark, compMark); //Start game
        if (winner == 'h')
        {
            score[0]++;
            cout << "You won!!!" << endl;
        }
        else if (winner == 'c')
        {
            score[1]++;
            cout << "Computer won!!!" << endl;
        }
        else
        {
            score[2]++;
            cout << "It's a draw" << endl;
        }
        cout << "Play again? Y or N? : ";
        playAgain = _getch();
    } while (playAgain != 'N' && playAgain != 'n');
}
