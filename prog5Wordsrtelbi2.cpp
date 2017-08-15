// AcrossWordsrtelbi2.cpp
//
// Author: Raul Telbisz
// Program: #5, AcrossWords
// TA: Moumita Samanta
// April 14, 2017
//
// AcrossWords is a game where you rotate rows or columns
// to restore the board back to containing four words. Each
// move is a row or column letter followed by the rotation distance
// 1,2,3. User may also select 'u' to unveil which words are hidden
// on the board.
//
/*

A runthrough of the program might look like:


		Author: Raul Telbisz
		Program 5: AcrossWords
		TA: Moumita Samanta, Mo 11-12
		April 10, 2017

		Welcome to AcrossWord puzzle, where you rotate rows or columns
		to restore the board back to containing four words. Each move is
		a row or column letter followed by the rotation distance 1, 2 or 3.
		When prompted to provide input you may enter:
		Enter 'r' to reset the board to user - defined values.
		Enter 'u' to unveil the underlying words.
		Enter 'x' to exit the program.

		Which dictionary size do you want? (1 = small, 2 = medium, 3 = large):

		1
		There are 500 four letter words

		E F G H
		-------
		A| n r d o
		B| l y a r
		C| o e w s
		D| m u c k

		1. Enter the row or column to be rotated, and a number 1..3:
		r

		You chose 'r' to reset the board.
		Enter 16 char values to reset the board:
		eushtnewblivokko

		E F G H
		-------
		A| e u s h
		B| t n e w
		C| b l i v
		D| o k k o

		1. Enter the row or column to be rotated, and a number 1..3:
		d2
		Rotating row/col D by 2
		E F G H
		-------
		A| e u s h
		B| t n e w
		C| b l i v
		D| k o o k

		2. Enter the row or column to be rotated, and a number 1..3:
		e2
		Rotating row/col E by 2
		E F G H
		-------
		A| b u s h
		B| k n e w
		C| e l i v
		D| t o o k

		3. Enter the row or column to be rotated, and a number 1..3:
		c3
		Rotating row/col C by 3
		E F G H
		-------
		A| b u s h
		B| k n e w
		C| l i v e
		D| t o o k

		Congratulations! You solved it!
		Press any key to continue . . .




*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//-----------------------------------------------------------------------------
// Display program information
void displayInformation() 
{
	printf("Author: Raul Telbisz\n");
	printf("Program 5: AcrossWords\n");
	printf("TA: Moumita Samanta, Mo 11-12\n");
	printf("April 10, 2017\n");
	printf("\n");
} // end of displayInformation()


//-----------------------------------------------------------------------------
// Display program instructions
void displayInstructions()
{
	printf("Welcome to AcrossWord puzzle, where you rotate rows or columns\n");
	printf("to restore the board back to containing four words. Each move is \n");
	printf("a row or column letter followed by the rotation distance 1, 2 or 3.\n");
	printf("When prompted to provide input you may enter:\n");
	printf("	Enter 'r' to reset the board to user - defined values.\n");
	printf("	Enter 'u' to unveil the underlying words.\n");
	printf("	Enter 'x' to exit the program.\n");
	printf("\n");
	printf("Which dictionary size do you want? (1 = small, 2 = medium, 3 = large): \n");
	printf("\n");
} // end of displayInstructions()


//-----------------------------------------------------------------------------
// Read in a dictionary, of which 3 sizes exist:
//	dictionaryNumber:	1 - small ; 2 - medium ; 3 - large
//
// This function simply "reads" in the words, storing happens in a later function
int readInDictionary(int dictionaryNumber)      // specifies which dictionary to use
{
	char tempWord[81];     // string which  temporarily holds each and every word as it is scanned in
	int numberOfWords = 0; // counts the total number of words in dictionary
	int wordLength = 0;    // placeholder for length of each word 
						   // (we are only looking to store 4-letter words)
	FILE *fDictionary;     // File type for our dictionary
	
	if (dictionaryNumber == 1) {	// small dictionary
		fDictionary = fopen("smallDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) { // We are only checking for 4-letter words
				numberOfWords++;
			}
		}
		printf("There are %d four letter words\n", numberOfWords);
		fclose(fDictionary);
	}
	else if (dictionaryNumber == 2) { // medium dictionary
		fDictionary = fopen("mediumDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) {
				numberOfWords++;
			}
		}
		printf("There are %d four letter words\n", numberOfWords);
		fclose(fDictionary);
	}
	else if (dictionaryNumber == 3) { // large dictionary
		fDictionary = fopen("largeDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) {
				numberOfWords++;
			}
		}
		printf("There are %d four letter words\n", numberOfWords);
		fclose(fDictionary);
	}
	return numberOfWords;
}// end of readinDictionary


//-----------------------------------------------------------------------------
// This opens the dictionary file again each number corresponding to a size:
// dicitonaryNumber     1 - small; 2 - medium; 3 - large
// The function then stores these words into a local array of pointers **dictionary
// Once the words are stored locally, we can perform necessayr operations
void storeWords(int dictionaryNumber, char **dictionary) 
{
	char tempWord[81];   // Temporary holds every word scanned in
	int wordLength = 0;  // Needed to store only 4 letter words 
	FILE *fDictionary;   // Pointer to dictionary stored on user's drive
	int i = 0;           // Placeholder for dictionary location

	if (dictionaryNumber == 1) {
		fDictionary = fopen("smallDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) {
				strcpy(dictionary[i], tempWord); // copying each 4 letter word into our dictionary
				i++; // incrementing to the next word in the dictionary
			}
		}
		fclose(fDictionary);
	}
	else if (dictionaryNumber == 2) {
		fDictionary = fopen("mediumDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) {
				strcpy(dictionary[i], tempWord);
				i++;
			}
		}
		fclose(fDictionary);
	}
	else if (dictionaryNumber == 3) {
		fDictionary = fopen("largeDictionary.txt", "r");
		while (fscanf(fDictionary, "%s", tempWord) != EOF) {
			wordLength = strlen(tempWord);
			if (wordLength == 4) {
				strcpy(dictionary[i], tempWord);
				i++;
			}
		}
		fclose(fDictionary);
	}
}// end of storeWords()


//-----------------------------------------------------------------------------
// Creates a local copy of the original board the user started the game with
// This is to be used later with the 'unveil' option in which the user
// Can choose to unveil the words on the original board.
// Function used in conjunction with displayOriginalBoard() method
void createOriginalBoard(char board[17], char originalBoard[17]) 
{
	for (int i = 0; i < 17; i++) {
		originalBoard[i] = board[i];
	}
} // end of CreateOriginalBoard()


//-----------------------------------------------------------------------------
// If the user selects the 'u' to unveil option, this method
// Displays all the contents of the original words that the user
// Started the game with, all in sensical order
void displayOriginalBoard(char originalBoard[17]) 
{
	printf("\n");
	printf("   E F G H \n");
	printf("   ------- \n");
	printf("A| %c %c %c %c     \n", 
		originalBoard[0], originalBoard[1], originalBoard[2], originalBoard[3]);
	printf("B| %c %c %c %c     \n", 
		originalBoard[4], originalBoard[5], originalBoard[6], originalBoard[7]);
	printf("C| %c %c %c %c     \n", 
		originalBoard[8], originalBoard[9], originalBoard[10], originalBoard[11]);
	printf("D| %c %c %c %c     \n", 
		originalBoard[12], originalBoard[13], originalBoard[14], originalBoard[15]);
	printf("\n");
} // end of displayOriginalBoard()


//-----------------------------------------------------------------------------
// Creates a board for which the user can play with, also scrambles the words 
// on the board. To present a challenge to the user, in having to solve it.
// Argument **dictionary is our local dictionary which has all stored words
// Board[17] will be the board that we create
// numberOfWords is the number of Words that exist in the specified dictionary
// originalBoard[17] is passed through so we may create a copy of the board for
// use with the 'u' unveil option
void createBoard(
	char **dictionary, char board[17], 
	int numberOfWords, char originalBoard[17]) 
{
	srand((int)time(0)); // seeding our random number generator with the time
	int randomIndex;     // random number we will use to select words for the board
	
	randomIndex = ((rand() % numberOfWords) + 1); // gives us a random value
	strcpy(board, dictionary[randomIndex]);       // we copy this random value
												  // to our board

	// Scrambling the letters of the board
	for (int i = 0; i < 3; i++) {
		randomIndex = ((rand() % numberOfWords) + 1);
		strcat(board, dictionary[randomIndex]);
	}
	
	// Creating an original copy of the board for use with the unveil option
	createOriginalBoard(board, originalBoard);
} // end of createBoard()


//-----------------------------------------------------------------------------
// Shifts the positions of the letters on board based on an input of 
// A,B,C,D which coincide with rows or
// E,F,G,H which coincide with columns.
// The shift amount determines by how many "places" to shift letters over
// This function also "wraps" the letters "around" the board
void shiftLetters(char board[17], 
	int firstSpot,   // first location to be shifted
	int secondSpot,  // second location to be shifted
	int thirdSpot,   // third location to be shifted
	int fourthSpot,  // fourth location to be shifted
	int shiftAmount) // number to be shifted by
{
	char temporaryVariable0; // holds location of the first location on the board
	char temporaryVariable1; // holds location of the second location on the board
	char temporaryVariable2; // holds location of the third location on the board
	char temporaryVariable3; // holds location of the fourth location on the board

    // Saving all original chars in temporary variables
	temporaryVariable0 = board[firstSpot];
	temporaryVariable1 = board[secondSpot];
	temporaryVariable2 = board[thirdSpot];
	temporaryVariable3 = board[fourthSpot];
	
	if (shiftAmount == 1) {      // shifts locations by 1 spot
		board[firstSpot] = temporaryVariable3;
		board[secondSpot] = temporaryVariable0;
		board[thirdSpot] = temporaryVariable1;
		board[fourthSpot] = temporaryVariable2;
	}
	else if (shiftAmount == 2) { // shifts locations by 2 spots
		board[firstSpot] = temporaryVariable2;
		board[secondSpot] = temporaryVariable3;
		board[thirdSpot] = temporaryVariable0;
		board[fourthSpot] = temporaryVariable1;
	}
	else if (shiftAmount == 3) { // shifts locations by 3 spots
		board[firstSpot] = temporaryVariable1;
		board[secondSpot] = temporaryVariable2;
		board[thirdSpot] = temporaryVariable3;
		board[fourthSpot] = temporaryVariable0;
	}
} // end of shiftLetters()


//-----------------------------------------------------------------------------
// Moves all characters in a "row" on the board over by a number as specified
// by shiftNum. This function only shifts rows in a horizontal direction.
// columnOrRow will only call this function if it is an A,B,C, or D
// which corresponds to a row call, to be shifted.
void makeMoveRow(char columnOrRow, int shiftNum, char board[17]) 
{
	// columnOrRow dictates which row is to be shifted
	// shiftNum dictates by how much we are shifting
	// shiftLetters performs the shifting of all characters in the row
	// the arguments shiftLetters() indicate which locations on the board[] will shift
	// For example: Row A corresponds to locations 0, 1,  2, 3
	//              Row B corresponds to locations 4, 5,  6, 7
	//              Row C corresponds to locations 8, 9, 10, 11
	//              Row C corresponds to locations 12, 13, 14, 15
	if (columnOrRow == 'A') {
		if (shiftNum == 1) {
			shiftLetters(board, 0, 1, 2, 3, 1);		 
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 0, 1, 2, 3, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 0, 1, 2, 3, 3);
		}
	}
	else if (columnOrRow == 'B') {
		if (shiftNum == 1) {
			shiftLetters(board, 4, 5, 6, 7, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 4, 5, 6, 7, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 4, 5, 6, 7, 3);
		}
	}
	else if (columnOrRow == 'C') {
		if (shiftNum == 1) {
			shiftLetters(board, 8, 9, 10, 11, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 8, 9, 10, 11, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 8, 9, 10, 11, 3);
		}
	}
	else if (columnOrRow == 'D') {
		if (shiftNum == 1) {
			shiftLetters(board, 12, 13, 14, 15, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 12, 13, 14, 15, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 12, 13, 14, 15, 3);
		}
	}
} // end of makeMoveRow()


//-----------------------------------------------------------------------------
// Moves all characters in a column based on the input of columnOrRow
// Values of which can only be E,F,G,H and shiftNum 1 .. 3
// The characters on the board are all shifted vertically, up to down
// while wrapping the letters around the board.
void makeMoveColumn(char columnOrRow, int shiftNum, char board[17]) 
{
	// columnOrRow dictates which column is to be shifted
	// shiftNum dictates by how much we are shifting
	// shiftLetters performs the shifting of all characters in the row
	// the arguments shiftLetters() indicate which locations on the board[] will shift
	// For example: Col E corresponds to locations 0, 4,  8, 12
	//              Col F corresponds to locations 1, 5,  9, 13
	//              Col G corresponds to locations 2, 6, 10, 14
	//              Col H corresponds to locations 3, 7, 11, 15
	if (columnOrRow == 'E') {
		if (shiftNum == 1) {
			shiftLetters(board, 0, 4, 8, 12, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 0, 4, 8, 12, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 0, 4, 8, 12, 3);
		}
	}
	else if (columnOrRow == 'F') {
		if (shiftNum == 1) {
			shiftLetters(board, 1, 5, 9, 13, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 1, 5, 9, 13, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 1, 5, 9, 13, 3);
		}
	}
	else if (columnOrRow == 'G') {
		if (shiftNum == 1) {
			shiftLetters(board, 2, 6, 10, 14, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 2, 6, 10, 14, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 2, 6, 10, 14, 3);
		}
	}
	else if (columnOrRow == 'H') {
		if (shiftNum == 1) {
			shiftLetters(board, 3, 7, 11, 15, 1);
		}
		else if (shiftNum == 2) {
			shiftLetters(board, 3, 7, 11, 15, 2);
		}
		else if (shiftNum == 3) {
			shiftLetters(board, 3, 7, 11, 15, 3);
		}
	}
} // end of makeMoveColumn()


//-----------------------------------------------------------------------------
// Display the board in its current state
void displayBoard(char board[17]) {
	printf("\n");
	printf("   E F G H \n");
	printf("   ------- \n");
	printf("A| %c %c %c %c     \n", 
		board[0], board[1], board[2], board[3]);
	printf("B| %c %c %c %c     \n", 
		board[4], board[5], board[6], board[7]);
	printf("C| %c %c %c %c     \n", 
		board[8], board[9], board[10], board[11]);
	printf("D| %c %c %c %c     \n", 
		board[12], board[13], board[14], board[15]);
	printf("\n");
} // end of displayBoard()


//-----------------------------------------------------------------------------
// Takes an input of letters and returns a random one out of the 4 given
char randomLetter(char first, char second, char third, char fourth) 
{
	char letterChosen;     // The letter that will be returned
	char arrayLetters[5];  // Storing all the letters in an array
	int randomInt;         // Used to select one of the 4 randomly

	randomInt = (rand() % 4); // Gives us a number 1 through 4

	// Assignment of letters to array locations
	arrayLetters[0] = first;
	arrayLetters[1] = second;
	arrayLetters[2] = third;
	arrayLetters[3] = fourth;
	arrayLetters[4] = '\0';

	// Assignment of our randomletter by the randomInt
	letterChosen = arrayLetters[randomInt];

	//returning the random Letter
	return letterChosen;

} // end of randomLetter()


//-----------------------------------------------------------------------------
// Performs an automated and randomized rotation of a single row by a single number
void doRowRotation(char board[17], char columnOrRow, int shiftingNumber) 
{
	// First we select a random row to be rotated, and then a random value
	// by which to rotate
	columnOrRow = randomLetter('A', 'B', 'C', 'D');
	shiftingNumber = (rand() % 3) + 1;

	// perform the shifting of the row
	if (columnOrRow == 'A' || columnOrRow == 'B' || columnOrRow == 'C' || columnOrRow == 'D') {
		makeMoveRow(columnOrRow, shiftingNumber, board);
	}
} // end of doRowRotation()


//-----------------------------------------------------------------------------
// Performs an automated and randomized rotation of a single column by a number
void doColumnRotation(char board[17], char columnOrRow, int shiftingNumber) 
{
	// First we select a random column to be rotated
	// and then a random value by which to rotate
	columnOrRow = randomLetter('E', 'F', 'G', 'H');
	shiftingNumber = (rand() % 3) + 1;;

	// perform the shifting of the column
	if (columnOrRow == 'E' || columnOrRow == 'F' || columnOrRow == 'G' || columnOrRow == 'H') {
		makeMoveColumn(columnOrRow, shiftingNumber, board);
	}
} // end of doColumnRotation()


//-----------------------------------------------------------------------------
// Randomizes the order of rotations of one column and two rows
// Three possible iterations of rotation exist:
// Column, Row, Row ; Row, Column, Row; Row, Row, Column;
void randomizeRotations(
	char board[17],         // The playing board
	char &columnOrRow,      // Passed as an argument for later use
	int &shiftingNumber,    // Specifies by what amount to rotate by
	int orderNumber)        // Specifies which order to rotate by
{
	if (orderNumber == 1) {
		doColumnRotation(board, columnOrRow, shiftingNumber);
		doRowRotation(board, columnOrRow, shiftingNumber);
		doRowRotation(board, columnOrRow, shiftingNumber);
	}
	else if (orderNumber == 2) {
		doRowRotation(board, columnOrRow, shiftingNumber);
		doColumnRotation(board, columnOrRow, shiftingNumber);
		doRowRotation(board, columnOrRow, shiftingNumber);
	}
	else if (orderNumber == 3) {
		doRowRotation(board, columnOrRow, shiftingNumber);
		doRowRotation(board, columnOrRow, shiftingNumber);
		doColumnRotation(board, columnOrRow, shiftingNumber);
	}
} // end of randomizeRotations()


//-----------------------------------------------------------------------------
// Loops through a dictionary searching for matching words, as words are found
// the wordCounter is increased
void loopThroughDictionary(
	char wordToSearch[4],  // word we will look to match
	char **dictionary,     // dictionary we will try to search
	int &wordCounter,      // counter for words found
	int numberOfWords)     // number of total words in dictionary
{
	char *pstr = NULL; // pointer to be used for words in the dictionary
	int i = 0;

	// if our pstr pointer does not return NULL, a word was found, so wordcounter++
	for (i = 0; i < numberOfWords; i++) {
		pstr = strstr(dictionary[i], wordToSearch);
		if (pstr != NULL) {
			wordCounter++;
		}
	}
} // end of loopThroughDictionary()


//-----------------------------------------------------------------------------
// Checks if all rows on the board match up with words found in the dictionary
// If all rows match, a congratulatory message is displayed and the program exits
void checkForWin(char board[17], char **dictionary, int numberOfWords) 
{
	int wordCounter = 0;    // Counts number of words found
	char wordToSearch[5];   // Word on the board we are searching for
	int boardLocation = 0;  // Current location on the board
	int boardRow = 0;
	int boardCol = 0;
	
	// Loop through every location on the board searching for matching words
	for (boardCol = 0; boardCol < 4; boardCol++) {
		for (boardLocation = 0; boardLocation < 4; boardLocation++) {
			wordToSearch[boardLocation] = board[boardRow];
			boardRow++;
		}
		
		wordToSearch[4] = '\0';
		// Looping through dictionary searching for matches
		loopThroughDictionary(wordToSearch, dictionary, wordCounter, numberOfWords);

		// Finding all words on the board match
		if (wordCounter == 4) {
			printf("Congratulations! You solved it!\n");
			system("pause");
			exit(0);
		}
	}
} // end of CheckForWin()


//-----------------------------------------------------------------------------
// Changes all characters on the board to 16 characters the user specifies
// in both identical order, format, and capitalization.
// We prompt the user for 16 characters exact, through which we will change the
// board
void resetBoard(char board[17]) {

	char resetString[17]; // The new string of chars to reset the board with

	printf("\nYou chose 'r' to reset the board.\n");
	printf("Enter 16 char values to reset the board: \n");
	scanf("%16s", resetString);

	while (strlen(resetString) != 16) {
		printf("Sorry, needed to provide exactly 16 characters of user input to reset the board.Please retry.\n");
		printf("Enter 16 char values to reset the board: \n");
		scanf("%16s", resetString);
	}

	// Changing all characters on the board to the new string of chars
	for (int i = 0; i < 16; i++){
		board[i] = resetString[i];
	}

	displayBoard(board); // Displaying the new board
} // end of resetBoard()


//-----------------------------------------------------------------------------
// Allows the user to try and unscramble the board, unveil the words on the board,
// or reset the board with a new set of characters
void playGame
    (char board[17],          // Board to play with
	char columnOrRow,         // Whether a row or column will be shifted
	char shiftingNumber,      // How much to shift by
	char moveCounter,         // Counts how many moves have been performed
	char **dictionaryWords,   // Dictionary of words
	int numberOfWords,        // Number of words in dictionary
	char originalBoard[17])   // A copy of the original board pre-scramble
{
	// We prompt the user for a move
	do {
		printf("%d. Enter the row or column to be rotated, and a number 1..3: \n", moveCounter);
		scanf(" %c", &columnOrRow);
		columnOrRow = toupper(columnOrRow);

		if (columnOrRow == 'R') { // Reset the board
			resetBoard(board);
			continue;
		}

		if (columnOrRow == 'U') { // Unveils all words on the board
			printf("\nYou chose 'u' to unveil. Here are the underlying words.\n");
			displayOriginalBoard(originalBoard);
			displayBoard(board);
			continue;
		}

		if (columnOrRow == 'X') { // Exits the game
			printf("You chose to exit. Exiting...\n");
			system("pause");
			exit(0);
		}

		scanf(" %d", &shiftingNumber); // Number by which to shift

		// Performing specified rotations
		printf("Rotating row/col %c by %d", columnOrRow, shiftingNumber);
		if (columnOrRow == 'A' || columnOrRow == 'B' || columnOrRow == 'C' || columnOrRow == 'D') {
			makeMoveRow(columnOrRow, shiftingNumber, board);
		}
		else if (columnOrRow == 'E' || columnOrRow == 'F' || columnOrRow == 'G' || columnOrRow == 'H') {
			makeMoveColumn(columnOrRow, shiftingNumber, board);
		}

		// Displaying the board and checking for a win
		displayBoard(board);
		checkForWin(board, dictionaryWords, numberOfWords);

		moveCounter++;
	} while (columnOrRow != 'X'); // Loop continues until a win or exit
} // end of playGame()


//-----------------------------------------------------------------------------
int main(){

	int dictionaryInput = 0;   // which dictionary size to use
	int numberOfWords = 0;     // number of words in the dictionary
	char **dictionaryWords;    // words stored in the dictionary
	char board[17];            // playing board
	int moveCounter = 1;       // count moves as the user goes
	char columnOrRow;          // whether a row or column rotates
	int shiftingNumber = 0;    // how much to rotate a row or column by
	int orderNumber = 0;       // randomized order number to scramble board
	char originalBoard[17];    // copy of original board pre-scrambled

	displayInformation(); 
	displayInstructions();

	// ask for a dictionary size
	scanf("%d", &dictionaryInput); 
	
	// count words in dictionary
	numberOfWords = readInDictionary(dictionaryInput);
	
	// allocate memory for words in dictionary
	dictionaryWords = (char**)malloc(numberOfWords * sizeof(char*));
	for (int i = 0; i < numberOfWords; i++) {
		dictionaryWords[i] = (char*)malloc(5 * sizeof(char));
	}
	 
	// store words in the dictionary from a .txt file
	storeWords(dictionaryInput, dictionaryWords);
	
	// create a board to play with
	createBoard(dictionaryWords, board, numberOfWords, originalBoard);

	// seed a random number generator
	srand((int)time(0));

	// choose a random order number
	orderNumber = (rand() % 3) + 1;

	// randomize rotations of the board (scramble)
	randomizeRotations(board, columnOrRow, shiftingNumber, orderNumber);
	
	displayBoard(board);
	
	// user can now play the game
	playGame(board, columnOrRow, shiftingNumber, moveCounter, dictionaryWords, numberOfWords, originalBoard);
	
	system("pause");
	return 0;

} //end of main()