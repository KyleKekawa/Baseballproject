#include<iostream>
#include<string>
#include<cstdlib> //to use srand()
#include<ctime> //to use time, returns the number of seconds elapsed since 1/1/70
#include<iomanip>

using namespace std;

const int numOfPlayers = 12;
const int numOfPositions = 12;
const int numOfInning = 5; 
const int numOfInfieldPosition = 6;
const int numOfOutfieldPosition = 6;

void getName(string listOfNames[numOfPlayers]);
void getBatting(int batting[numOfPlayers], string listOfNames[numOfPlayers]); 
void selectionSort(int batting[numOfPlayers], string listOfNames[numOfPlayers]);
bool findNumInArray(int temp[numOfPositions], int randNum);
void resetArray(int[numOfPositions]);
void lineUp(int lineUpArray[numOfInning][numOfPositions]);
void transposing(int lineUpArray[numOfInning][numOfPositions], 
										int transposedLineUpArray[numOfPlayers][numOfInning]);
void convertingIntToStr(int transposedLineUpArray[numOfPlayers][numOfInning],
	string convertedLineUpArray[numOfPlayers][numOfInning],
	string positions[numOfPositions]);
void displayArray(string listOfNames[numOfPlayers], string convertedLineUpArry[numOfPlayers][numOfInning]);

int main() {

	string positions[numOfPositions] = { "C", "P", "1B", "2B", "SS", "3B", "LF", "LCF", "RCF", "RF", "OUT1", "OUT2" };
									//    0    1    2     3     4     5   | 6     7       8     9      10      11
									//    INFIELD                         |              OUTFIELD

	string listOfNames[numOfPlayers];
	int batting[numOfPlayers];
	int lineUpArray[numOfInning][numOfPositions];
	int transposedLineUpArray[numOfPlayers][numOfInning];
	string convertedLineUpArray[numOfPlayers][numOfInning];
	char x = 'y';

	srand(time(0));

	getName(listOfNames);
	getBatting(batting, listOfNames);
	selectionSort(batting, listOfNames);

	while (x == 'y' || x == 'Y')
	{
		lineUp(lineUpArray);
		transposing(lineUpArray, transposedLineUpArray);
		convertingIntToStr(transposedLineUpArray, convertedLineUpArray, positions);
		displayArray(listOfNames, convertedLineUpArray);
		cout << "\n" << "Try Again? ";
		cin >> x;
	}
	
	system("pause");
	return 0;
}

void getName(string listOfNames[numOfPlayers]) {
	string userInput;
	cout << "Enter " << numOfPlayers << " player names: " << endl;
	for (int i = 0; i < numOfPlayers; i++)
	{
		cout << "What is player " << i + 1 << " 's name: ";
		cin >> userInput;
		listOfNames[i] = userInput;
	}
}

void getBatting(int batting[numOfPlayers], string listOfNames[numOfPlayers]) {
	int userInput;
	cout << "\n\n\n";
	cout << "Enter the averages for each player: " << endl;
	cout << "-------------------------------------" << endl;

	for (size_t i = 0; i < numOfPlayers; i++)
	{
		cout << "What is " << listOfNames[i] << " 's average: ";
		cin >> userInput;
		batting[i] = userInput;

	}
}

void selectionSort(int batting[numOfPlayers], string listOfNames[numOfPlayers]) {
	string tempName = "";
	int tempNum;
	int maxIndex;

	for (int i = 0; i < numOfPlayers - 1; i++)
	{
		for (int j = i + 1; j < numOfPlayers; j++)
		{
			if (batting[i] < batting[j]) {
				tempName = listOfNames[i];
				tempNum = batting[i];

				batting[i] = batting[j];
				batting[j] = tempNum;

				listOfNames[i] = listOfNames[j];
				listOfNames[j] = tempName;
			}

		}
	}
}
bool findNumInArray(int temp[numOfPositions], int randNum) {
	bool isFound = false;
	for (int i = 0; i < numOfPositions; i++) {
		if (temp[i] == randNum) {
			isFound = true;
			break;

		}
		else
		{
			isFound = false;
		}
	}
	return isFound;
}
void resetArray(int temp[numOfPositions]) {
	for (int i = 0; i < numOfPositions; i++)
	{
		temp[i] = -1;
	}
}


void lineUp(int lineUpArray[numOfInning][numOfPositions]) {
	int randNum;
	int temp[numOfPositions]; //for memorizing generated random numbers
	int row;

	for (int i = 0; i < numOfInning; i++)
	{
		row = i;
		for (int j = 0; j < numOfPositions; j++)
			//inning 1
		{
			if (row == 0) {
				randNum = rand() % numOfPositions;
				if (findNumInArray(temp, randNum) == false) { //determine if the randNum is in the temp array
					temp[j] = randNum;
					lineUpArray[i][j] = randNum;
				}
				else // the condition failed. redo the loop 
				{
					j -= 1;
				}
			}
			//*********************************************************************************************************************
			// Inning 2 
			else if (row == 1) {
				if (lineUpArray[0][j] < 6) {

					randNum = rand() % numOfOutfieldPosition + numOfOutfieldPosition; // from 6-11

					if (findNumInArray(temp, randNum) == false) {
						temp[j] = randNum;
						lineUpArray[i][j] = randNum;
					}
					else
					{
						j -= 1;								// The condition failed. redo the loop again
					}
				}
				else
				{																//the player played outfield in Inning 1
																				// Then the player should play infield in Inning 2
					randNum = rand() % numOfInfieldPosition; //from 0-5


					if (findNumInArray(temp, randNum) == false) {
						temp[j] = randNum;
						lineUpArray[i][j] = randNum;
					}
					else
					{
						j -= 1;				// the condition failed. redo the loop again.
					}
				}
			}
			else if (row == 2) {
				randNum = rand() % numOfPositions;
				if (findNumInArray(temp, randNum) == false) { // determine if the randNum is in the temp array 
					if (randNum != lineUpArray[i - 1][j] && randNum != lineUpArray[i - 2][j]) {
						//determine if the player had played the position before 

						temp[j] = randNum;
						lineUpArray[i][j] = randNum;

						if (randNum == 0) { //the player plays catcher in this inning
							//check if he played catcher before
							//if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 0 || lineUpArray[i - 2][j] == 0) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}
						else if (randNum == 10) { // the player played out1 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 11 || lineUpArray[i - 2][j] == 11) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

						else if (randNum == 11) { // the player played out2 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 10 || lineUpArray[i - 2][j] == 10) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

					}
					else {
						temp[j] = -1;
						lineUpArray[i][j] = -1;
						j = -1;

					}
				}
				else {
					j -= 1;
				}
			}
			//***************************************************************************************************************
			// inning 4 
			else if (row == 3) {
				randNum = rand() % numOfPositions;
				if (findNumInArray(temp, randNum) == false) { // determine if the randNum is in the temp array 
					if (randNum != lineUpArray[i - 1][j] && randNum != lineUpArray[i - 2][j] && randNum != lineUpArray[i - 3][j]) {
						//determine if the player had played the position before 

						temp[j] = randNum;
						lineUpArray[i][j] = randNum;

						if (randNum == 0) { //the player plays catcher in this inning
							//check if he played catcher before
							//if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 0 || lineUpArray[i - 2][j] == 0 || lineUpArray[i - 3][j] == 0) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}
						else if (randNum == 10) { // the player played out1 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 11 || lineUpArray[i - 2][j] == 11 || lineUpArray[i - 3][j] == 11) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

						else if (randNum == 11) { // the player played out2 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 10 || lineUpArray[i - 2][j] == 10 || lineUpArray[i - 3][j] == 10) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

					}
					else {
						temp[j] = -1;
						lineUpArray[i][j] = -1;
						j = -1;

					}
				}
				else {
					j -= 1;
				}
			}
			//***************************************************************************************************************
			// inning 5 
			else if (row == 4) {
				randNum = rand() % numOfPositions;
				if (findNumInArray(temp, randNum) == false) { // determine if the randNum is in the temp array 
					if (randNum != lineUpArray[i - 1][j] && randNum != lineUpArray[i - 2][j] && randNum != lineUpArray[i - 3][j] && randNum != lineUpArray[i - 4][j]) {
						//determine if the player had played the position before 

						temp[j] = randNum;
						lineUpArray[i][j] = randNum;

						if (randNum == 0) { //the player plays catcher in this inning
							//check if he played catcher before
							//if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 0 || lineUpArray[i - 2][j] == 0 || lineUpArray[i - 3][j] == 0 || lineUpArray[i - 4][j] == 0) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}
						else if (randNum == 10) { // the player played out1 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 11 || lineUpArray[i - 2][j] == 11 || lineUpArray[i - 3][j] == 11 || lineUpArray[i - 4][j] == 11) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

						else if (randNum == 11) { // the player played out2 in this inning 
							// check if he played out before 
							// if so, re-generate new randNums for the whole row.
							if (lineUpArray[i - 1][j] == 10 || lineUpArray[i - 2][j] == 10 || lineUpArray[i - 3][j] == 10 || lineUpArray[i - 4][j] == 10) {
								temp[j] = -1;
								lineUpArray[i][j] = -1;
								j = -1;
							}
						}

					}
					else {
						temp[j] = -1;
						lineUpArray[i][j] = -1;
						j = -1;

					}
				}
				else {
					j -= 1;
				}


			}
		} resetArray(temp); //set every element in array to -1
	}
}

void transposing(int lineUpArray[numOfInning][numOfPositions],
	int transposedLineUpArray[numOfPlayers][numOfInning]) {
	for (int i = 0; i < numOfInning; i++) {
		for (int j = 0; j < numOfPositions; j++) {
			transposedLineUpArray[j][i] = lineUpArray[i][j];
		}
	}
}

	void convertingIntToStr (int transposedLineUpArray[numOfPlayers][numOfInning],
		string convertedLineUpArray[numOfPlayers][numOfInning],
		string positions[numOfPositions]) {
		for (int i = 0; i < numOfPositions; i++){
			for (int j = 0; j < numOfInning; j++){
				convertedLineUpArray[i][j] = positions[transposedLineUpArray[i][j]];

			}
		}
	}

	void displayArray(string listOfNames[numOfPlayers], string convertedLineUpArry[numOfPlayers][numOfInning]) {
		cout << "\n\n\n";
		cout << "Game lineup and field positions: " << endl;
		cout << "--------------------------------" << endl;
		cout << "Name" << setw(20) << "Inning 1" << setw(16) << "Inning 2" << setw(16) << "Inning 3" << setw(16) << "Inning 4" << setw(16) << "Inning 5" << endl;

		for (int i = 0; i < numOfPlayers; i++){
			cout << setw(8) << left << listOfNames[i];
			for (int j = 0; j < numOfInning; j++){
				cout << setw(16) << right << convertedLineUpArry[i][j];
			}
			cout << "\n";
		}
	}
