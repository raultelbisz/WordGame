/*
prog6Undortelbi2.cpp
AcrossWord with Undo is a 4x4 grid of letters that originally contains four four-letter words.
The original configuration is then changed by two row and one column rotation, where the
letters wrap around the ends.  The user then has to solve the puzzle to get back the
original four words. The extra credit has the computer solve the puzzle by itself, but is
not implemented here. The Undo option has been added where a player can undo a move by
entering 'u'.

Author: Raul Telbisz
Program: #6, AcrossWord with Undo
TA: Moumita Samanta, Mon 11
4/19/2017

Running the program looks like the following:

		Author: Raul Telbisz
		Program: #6, AcrossWords with Undo
		TA: Moumita Samanta, Mon 11
		April 19, 2017

		Welcome to AcrossWord puzzle, where you rotate rows or columns
		to restore the board back to containing four words. Each move is
		a row or column letter followed by the rotation distance 1,2 or 3.

		When prompted to provide input you may enter:
		Enter 'r' to reset the board to user-defined values.
		Enter 'u' to undo a move.
		Enter 'o' for original board to be shown.
		Enter 'x' to exit the program.

		There are 500 4-letter words.

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| e k t o
		1. Enter the row or column to be rotated, and a number 1..3: d1

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| o e k t
		List: 2->1

		2. Enter the row or column to be rotated, and a number 1..3: u
		You chose u to undo most recent move.
		* Undoing move *

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| e k t o
		List: 1
		1. Enter the row or column to be rotated, and a number 1..3: u
		You chose u to undo most recent move.
		* Undoing move *
		Can't undo past the beginning of the game.  Please try again

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| e k t o
		List: 1
		1. Enter the row or column to be rotated, and a number 1..3: d1

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| o e k t
		List: 2->1

		2. Enter the row or column to be rotated, and a number 1..3: d1

		E F G H
		-------
		A| b u e h
		B| k n o w
		C| i v s l
		D| t o e k
		List: 3->2->1

		3. Enter the row or column to be rotated, and a number 1..3: g2

		E F G H
		-------
		A| b u s h
		B| k n e w
		C| i v e l
		D| t o o k
		List: 4->3->2->1

		4. Enter the row or column to be rotated, and a number 1..3: c1

		E F G H
		-------
		A| b u s h
		B| k n e w
		C| l i v e
		D| t o o k
		List: 5->4->3->2->1

		You did it!  Well done.
		Press any key to continue . . .

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for the exit() command
#include <iostream>
#include <math.h>   // for random()
#include <time.h>   // for srand( time(0) )
using namespace std;

// Global constants
const char SMALL_DICTIONARY_NAME[] = "smallDictionary.txt";
const int WORD_LENGTH = 4; // Minimum dictionary word size to be stored
const int BOARD_SIZE = WORD_LENGTH * WORD_LENGTH;  



//--------------------------------------------------------------------------------
// Linked list which has the following:
// Node structure to hold the current move number,
// current board at the time of Node creation
// and a pointer to the next Node.
struct Node {
	int moveNumber;
	char board[BOARD_SIZE];
	Node *pNext;
}; // end of struct Node


//--------------------------------------------------------------------------------
// Creates/Saves all values into a node, values saved are:
// the current characters spanning the board and move Number
void saveNode(Node *&pHead, char board[BOARD_SIZE], int moveNumber) {

	Node *pTemp = new Node; // Creating a pointer to a new node

	// Populating the board of the current Node with the current board
	for (int i = 0; i < BOARD_SIZE; i++) {
		pTemp->board[i] = board[i];
	}

	pTemp->moveNumber = moveNumber; // Setting the move number of the node
	pTemp->pNext = pHead; // Setting the next pointer of the node back to the "head" node
	pHead = pTemp; // Making the head of the node point back to the temporary node
} // end of saveNode()


//--------------------------------------------------------------------------------
// Display the List of move numbers that have been made
void displayList(Node *pHead)
{
	printf("List: ");
	while (pHead != NULL) {
		cout << pHead->moveNumber;
		if (pHead->pNext != NULL)  cout << "->";
		pHead = pHead->pNext;
	}
	cout << endl;
} // end of displayList()


//--------------------------------------------------------------------------------
// Undo a Node, which in turn undoes a move.
// The board is reupdated with the board saved in the previous node
// and the last node created gets deleted to save new values
// The move number also gets deducted
void undoNode(Node *&pHead, char board[BOARD_SIZE], int &moveNumber) {

	// If the pointer is empty then we can't go back to a "non-existant" board
	// This is a safeguard against that
	if (pHead->pNext == NULL) {
		printf("Can't undo past the beginning of the game.  Please try again\n");
		return;
	}

	
	Node *pTemp = pHead;  // Pointer points back to the sentinel head
	pHead = pHead->pNext; // "Resetting" the pointer
	delete(pTemp);        // Deleting the old node pointer 

	// Updating the board
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = pHead->board[i];
	}
	moveNumber = pHead->moveNumber; // Changing the moveNumber as needed
} // end of undoNode()


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
	printf("\n");
	printf("Author: Raul Telbisz          \n");
	printf("Program: #6, AcrossWords with Undo  \n");
	printf("TA: Moumita Samanta, Mon 11 \n");
	printf("April 19, 2017               \n");
	printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
	printf("Welcome to AcrossWord puzzle, where you rotate rows or columns       \n");
	printf("to restore the board back to containing four words. Each move is     \n");
	printf("a row or column letter followed by the rotation distance 1,2 or 3.\n");
	printf("  \n");
	printf("When prompted to provide input you may enter:              \n");
	printf("     Enter 'r' to reset the board to user-defined values.  \n");
	printf("     Enter 'u' to undo a move.                             \n");
	printf("     Enter 'o' for original board to be shown.             \n");
	printf("     Enter 'x' to exit the program.                        \n");
	printf("  \n");
}//end displayInstructions()


 //---------------------------------------------------------------------------
 // Read in dictionary.
 //    First read through the dictionary once to count how many four-letter
 //    words there are.  Then dynamically allocate space for those words,
 //    and re-read the dictionary, this time storing those words.
 //    Note that the '&' is needed so that the new array address is
 //    passed back as a reference parameter.
void readInDictionary(
	char** &dictionary,           // dictionary words
	int &numberOfWords)      // number of words stored
{
	FILE *pInputFile;     // Pointer to input file
	char theWord[81];    // Used to read in each dictionary word
	int wordLength;       // Set to be the length of each input word
	int dictionarySize;	  // User input sets this, which in turn determines which dictionary to open
	char dictionaryName[81];  // Will be set to the dictionary name corresponding to the dictionary size


	strcpy(dictionaryName, SMALL_DICTIONARY_NAME);

	// Read all dictionary words and count how many four-letter words there are
	pInputFile = fopen(dictionaryName, "r");   // Returns null if not found.  Mode is "r" for read
    // Verify that file open worked
	if (pInputFile == NULL) {
		printf("File open failed.  Ensure file is in the right location.\n");
		printf("Exiting program...\n");
		exit(-1);
	}

	// Keep repeating while input from the file yields a word
	while (fscanf(pInputFile, "%s", theWord) != EOF) {
		wordLength = (int)strlen(theWord);
		if (wordLength == WORD_LENGTH) {
			numberOfWords++;
		}
	}
	fclose(pInputFile);

	// Allocate space for the dictionary of only four-letter words
	dictionary = (char **)malloc(sizeof(char *) * numberOfWords);
	// For each array entry, allocate space for the word (C-string) to be stored there
	for (int i = 0; i < numberOfWords; i++) {
		// Extra character for the NULL
		dictionary[i] = (char *)malloc(sizeof(char) * (WORD_LENGTH + 1));
	}

	// Now reread the input file, this time storing the four-letter words into dictionary
	pInputFile = fopen(dictionaryName, "r");   // Returns null if not found.  Mode is "r" for read
	numberOfWords = 0; // reset, then use as index to count up
	 // Keep repeating while input from the file yields a word
	while (fscanf(pInputFile, "%s", theWord) != EOF) {
		wordLength = (int)strlen(theWord);
		if (wordLength == WORD_LENGTH) {
			strcpy(dictionary[numberOfWords++], theWord);
		}
	}
	fclose(pInputFile);

	printf("There are %d %d-letter words. \n", numberOfWords, WORD_LENGTH);
}//end readInDictionary()


 //--------------------------------------------------------------------------------
 // Select four random words from the dictionary of 4-letter words and
 // place them on the board.
void placeFourRandomWordsOnBoard(
	char **dictionary,            // Array of all dictionary words
	int numberOfWords,            // How many words there are in above dictionary
	char board[BOARD_SIZE])   // The board where words will be placed
{
	srand(0);

	// Place words horizontally.  If random number dictates vertical, we will rotate board
	// 90 degrees clockwise.
	for (int i = 0; i<WORD_LENGTH; i++) {
		// Find starting location for word to be placed
		int startingIndex = i * WORD_LENGTH;

		// Find the word to be placed
		int wordIndex = rand() % numberOfWords;

		// Copy the four word letters onto the board
		for (int j = 0; j<WORD_LENGTH; j++) {
			board[startingIndex + j] = dictionary[wordIndex][j];
		}
	}

}//end placeFourRandomWordsOnBoard()


 //--------------------------------------------------------------------------------
 // Display the board, taking the 16 board characters and displaying them
 // in a 4x4 grid.
void displayBoard(char board[])
{
	printf("\n");

	printf("     E F G H\n");
	printf("     -------\n");
	for (int row = 0; row<WORD_LENGTH; row++) {
		printf("  %c| ", 'A' + row);
		for (int col = 0; col<WORD_LENGTH; col++) {
			// calculate actual board position
			int index = row * WORD_LENGTH + col;
			//  display that board character
			printf("%c ", board[index]);
		}
		printf("\n");
	}
	fflush(stdout);  // flush the output buffer
}//end displayBoard()


 //--------------------------------------------------------------------------------------
 // Rotate the characters right "distance" number of times.  Changes to the characters
 // are reflected back to the caller.
void rotate(char &c1, char &c2, char &c3, char &c4, int distance)
{
	char c;
	// Do a single rotation the determined number of times
	for (int i = 0; i<distance; i++) {
		c = c1;   // store the first character so it is not overwritten and available at the end
		// do the single rotation
		c1 = c4; c4 = c3; c3 = c2; c2 = c;
	}
}


//--------------------------------------------------------------------------------------
// Prompt for a row (A..D) or column (E..H) and how many single rotations to make.
// Extract those board letters, and make the rotation.
// Board index positions for the rotations are:
//
//      E  F  G  H
//     ------------
//   A| 0  1  2  3
//   B| 4  5  6  7
//   C| 8  9 10 11
//   D|12 13 14 15
//
void getCharactersAndMakeRotation(char board[BOARD_SIZE], char rowOrColumnToRotate, int rotateDistance)
{
	// printf("Rotating row/col %c by %d\n", rowOrColumnToRotate, rotateDistance);   // For debugging

	// Pull out the four board characters to be used in the rotation, and send them to actually do the rotation
	switch (toupper(rowOrColumnToRotate)) {
	case 'A': rotate(board[0], board[1], board[2], board[3], rotateDistance); break;
	case 'B': rotate(board[4], board[5], board[6], board[7], rotateDistance); break;
	case 'C': rotate(board[8], board[9], board[10], board[11], rotateDistance); break;
	case 'D': rotate(board[12], board[13], board[14], board[15], rotateDistance); break;
	case 'E': rotate(board[0], board[4], board[8], board[12], rotateDistance); break;
	case 'F': rotate(board[1], board[5], board[9], board[13], rotateDistance); break;
	case 'G': rotate(board[2], board[6], board[10], board[14], rotateDistance); break;
	case 'H': rotate(board[3], board[7], board[11], board[15], rotateDistance); break;
	default: // Sanity check, should never get called
		printf("Invalid row/col value of %c.  Exiting program...\n", rowOrColumnToRotate);
		exit(-1);
	}
}//end getCharactersAndMakeRotation()


//--------------------------------------------------------------------------------------
// Make two row rotations and one column rotation, randomly choosing in which of the
// three moves the column rotation is done.
void makeBoardRotations(char board[BOARD_SIZE])
{
	srand(0);   // Seed the random number generator with time(0) rather than just 0,
				// if you want different results each time

	// Generate the two row letters ('A'..'D') to be used
	char rowsToUse[2];
	rowsToUse[0] = rand() % 4 + 'A';   // Add 0..3 to 'A', giving 'A'..'D'
	// Make sure the second one is a different row
	do {
		rowsToUse[1] = rand() % 4 + 'A';   // Add 0..3 to 'A', giving 'A'..'D'
	} while (rowsToUse[1] == rowsToUse[0]);

	// Create the array where those three values will be placed, with the column letter ('E'..'H')
	// being placed at random into one of the three positions
	char rowOrColumnToUse[3] = { ' ',' ',' ' };
	rowOrColumnToUse[rand() % 3] = rand() % 4 + 'E';   // Add 0..3 to 'E', giving 'E'..'H'

	// Put the two row letters into the remaining empty spots
	int rowIndex = 0;
	for (int i = 0; i<3; i++) {
		if (rowOrColumnToUse[i] == ' ') {
			// Put the next row letter into this empty spot
			rowOrColumnToUse[i] = rowsToUse[rowIndex++];
		}
	}

	// Now make the three rotations
	for (int i = 0; i<3; i++) {
		int rotateDistance = (rand() % 3 + 1);  // We will rotate 1..3 times
		getCharactersAndMakeRotation(board, rowOrColumnToUse[i], rotateDistance);
		// displayBoard( board);    // For debugging
	}
} // end makeBoardRotations()


  //--------------------------------------------------------------------------------------
  // Use binary search to look up the search word in the dictionary array, returning index
  // if found, -1 otherwise
int binarySearch(const char searchWord[WORD_LENGTH + 1], // word to be looked up
	char *dictionary[],                   // the dictionary of words
	int numberOfWords)                    // number of dictionary words
{
	int low, mid, high;     // array indices for binary search
	int searchResult = -1;  // Stores index of word if search succeeded, else -1

	// Binary search for word
	low = 0;
	high = numberOfWords - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		// searchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found
		searchResult = strcmp(searchWord, dictionary[mid]);
		if (searchResult == 0) {
			// Word IS in dictionary, so return the index where the word was found
			return mid;
		}
		else if (searchResult < 0) {
			high = mid - 1; // word should be located prior to mid location
		}
		else {
			low = mid + 1; // word should be located after mid location
		}
	}

	// Word was not found
	return -1;
}//end binarySearch()


 //--------------------------------------------------------------------------------------
 // Check the four row four-letter words.  If all four are in the dictionary, then we're done.
bool done(char board[BOARD_SIZE], char **dictionary, int numberOfWords)
{
	bool allWordsAreFound = true;
	for (int i = 0; i<WORD_LENGTH; i++) {
		// Make a word out of the 4 letters
		char theWord[5];
		theWord[0] = board[i*WORD_LENGTH + 0];
		theWord[1] = board[i*WORD_LENGTH + 1];
		theWord[2] = board[i*WORD_LENGTH + 2];
		theWord[3] = board[i*WORD_LENGTH + 3];
		theWord[4] = '\0';    // Null terminate each word

		// See if it is in the dictionary.  If not, indicate all words are not found and return false
		if (binarySearch(theWord, dictionary, numberOfWords) == -1) {
			// word was not found.
			allWordsAreFound = false;    // We're not done yet, since all words are not found
			break;
		}
	}//end for( int i..

	return allWordsAreFound;   // True when we're not done yet, false otherwise
}// end done()


 //--------------------------------------------------------------------------------------
 // Prompt the user for 16 board values and reset the board
void resetBoard(char board[BOARD_SIZE])
{
	char userInput[81];
	userInput[0] = '\0';   // Set the first character to NULL, so strlen will work

	// Validate user input as being the same size as the board
	while (strlen(userInput) != BOARD_SIZE) {
		printf("Enter %d char values to reset the board: ", BOARD_SIZE);
		scanf("%s", userInput);

		// validate length of user input
		if (strlen(userInput) != 16) {
			printf("Sorry, needed to provide exactly 16 characters of user input to reset the board.  Please retry.\n");
		}
	}//end while

	 // User input length is correct. Copy over from user input into the board.
	for (int i = 0; i<BOARD_SIZE; i++) {
		board[i] = userInput[i];
	}
}//end resetBoard()


 //--------------------------------------------------------------------------------------
 // main function
int main() {
	// Declare the board
	char board[BOARD_SIZE];	   // The boad of letters, that starts with 4 words on it
	char backupBoard[BOARD_SIZE]; // Used to make a copy of the board, to display when "cheat" selected
	char **dictionary;     		 // Will store dynamically-allocated dictionary of words
	int numberOfWords = 0; 	 	 // How many words of correct length are in the dictionary
	int moveNumber = 1;    	 	 // Display move numbers as play progresses
	char rowOrColumn = ' ';  	 // Will be 'A'..'H'
	char rotateDistance = ' ';   // Should be '1'..'3', since '4' and above starts to repeat
	Node *pHead = NULL;
	


	 // Display identifying information and instructions
	displayIdentifyingInformation();
	displayInstructions();

	// Seed the random number generator
	srand(0);   // Use time(0) rather than 0 if you want to get a different board each time

	// Read each word in the large dictionary and count how many 4-letter words are there.
	readInDictionary(dictionary, numberOfWords);

	// Choose four words at random, and set them on the board.
	placeFourRandomWordsOnBoard(dictionary, numberOfWords, board);
	// Make a copy of the original board
	for (int i = 0; i<BOARD_SIZE; i++) {
		backupBoard[i] = board[i];
	}

	// Make two rotations of a row and one rotation of a column
	makeBoardRotations(board);
	// Save a new Node with the current board
	saveNode(pHead, board, moveNumber);

	// display the board
	displayBoard(board);

	// Present the puzzle to the user to try and interactively solve
	while (!done(board, dictionary, numberOfWords)) {
		printf("%d. Enter the row or column to be rotated, and a number 1..3: ", moveNumber);
		scanf(" %c", &rowOrColumn);
		// Check for 'r' to reset, 'u' to undo, 'o' to cheat, or 'x' to exit
		if (rowOrColumn == 'x') {
			printf("You chose x to Exit...\n");
			break;
		}
		else if (rowOrColumn == 'u') {
			printf("You chose u to undo most recent move.\n");
			printf("* Undoing move *\n");
			// Reverts to the previous node with the previous board
			undoNode(pHead, board, moveNumber);
			// Displays the new "older" board
			displayBoard(board);
			// Display the lis of moves
			displayList(pHead);
			continue; // continue back up to retru user input
		}
		else if (rowOrColumn == 'r') {
			printf("You chose 'r' to reset the board. \n");
			resetBoard(board);
			displayBoard(board);
			continue;	// continue back up to retry user input
		}
		else if (rowOrColumn == 'o') {
			// 'o' for 'originalboard' was chosen.  Display the backup board
			printf("You chose 'o' for the original board to be shown.  Here are the underlying words: \n");
			displayBoard(backupBoard);
			printf("\n");
			displayBoard(board);
			continue;   // continue back up to retry user input
		}

		// Neither 'x','r','u', or 'o' were chosen, so go on to read the rotate distance
		scanf(" %c", &rotateDistance);

		// Make the rotation
		getCharactersAndMakeRotation(board, toupper(rowOrColumn), rotateDistance - '0');

		// Display the board
		displayBoard(board);
		
		
		moveNumber++; // Update the move number
		saveNode(pHead, board, moveNumber); // save a new Node with updated board and moveNumber
		displayList(pHead); // Display the list of moves done

		printf("\n");
	}

	// Display congratulatory message if solution was found
	if (done(board, dictionary, numberOfWords)) {
		printf("You did it!  Well done. \n");
	}

	system("pause");
	printf("\nEnd of program.  Exiting... \n");
	return 0;
}// end main()

