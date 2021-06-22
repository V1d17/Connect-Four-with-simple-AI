// Connect Four with AI
#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<time.h>

#include<unistd.h>

//Structure for grid
struct Grid {
  char data;
  struct Move * next;
};

//Structure for linked list to record moves
struct Move {
  int data;
  struct Move * next;
};

/*************************************************************************************************
*                                 Functions for AI moves                                         *
*************************************************************************************************/

/*
Helper function for checkAbtWinAI() and horCheckAI(). Checks for three consecutive occurences of either 'X' or 'O' in column.
@returns 1 -> if three consecutive occurences and 4th index '.'
         0 -> if otherwise
*/
int checkThreeAIVert(struct Grid * gridPtr, int x, int y, int z, int w, char sym) {
  return ((gridPtr + y) -> data == (gridPtr + z) -> data && (gridPtr + z) -> data == (gridPtr + w) -> data && (gridPtr + (x % 42)) -> data == '.' && (gridPtr + z) -> data != '.');
}

/*
Helper function for checkAbtWinAI() and horCheckRightAI(). Checks for three consecutive occurences of either 'X' or 'O' in row.
This method checks if 4th right element is '.'.
@returns 1 -> if three consecutive occurences and 4th index '.'
         0 -> if otherwise
*/
int checkThreeAIHorRight(struct Grid * gridPtr, int x, int y, int z, int w, char sym) {
  return ((gridPtr + x) -> data == (gridPtr + y) -> data && (gridPtr + y) -> data == (gridPtr + z) -> data && (gridPtr + (w % 42)) -> data == '.' && (gridPtr + z) -> data != '.');
}

/*
Helper function for checkAbtWinAI() and horCheckLeftAI(). Checks for three consecutive occurences of either 'X' or 'O' in row.
This method checks if 4th left element is '.'.
@returns 1 -> if three consecutive occurences and 4th index '.'
         0 -> if otherwise
*/
int checkThreeAIHorLeft(struct Grid * gridPtr, int x, int y, int z, int w, char sym) {
  return ((gridPtr + y) -> data == (gridPtr + z) -> data && (gridPtr + z) -> data == (gridPtr + w) -> data && (gridPtr + (x % 42)) -> data == '.' && (gridPtr + z) -> data != '.');
}

/*
Helper function for checkAbtWinAI() and diaCheckAI(). Checks for three consecutive occurences of either 'X' or 'O' in diagonal.
@returns 1 -> if three consecutive occurences and 4th index '.'
         0 -> if otherwise
*/
int checkThreeAIDia(struct Grid * gridPtr, int x, int y, int z, int w, char sym) {
  return ((gridPtr + y) -> data == (gridPtr + z) -> data && (gridPtr + z) -> data == (gridPtr + w) -> data && (gridPtr + (x % 42)) -> data == '.' && (gridPtr + z) -> data != '.');
}

/*
Helper function for checkAbtWinAI(). Loops through all possible indexes in grid. 
Calls checkThreeAIHor() with next 3 indices. 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int horCheckRightAI(struct Grid * gridPtr, char sym) {
  int index;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 7 - 2; col++) {
      index = 7 * row + col;
      if (checkThreeAIHorRight(gridPtr, index, index + 1, index + 2, index + 3, sym)) {
        return index + 3;
      }
    }
  }
  return -1;
}

/*
Helper function for checkAbtWinAI(). Loops through all possible indexes in grid. 
Calls checkThreeAIHor() with next 3 indices. 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int horCheckLeftAI(struct Grid * gridPtr, char sym) {
  int index;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 7 - 2; col++) {
      index = 7 * row + col;
      if (checkThreeAIHorLeft(gridPtr, index, index + 1, index + 2, index + 3, sym)) {
        return index;
      }
    }
  }
  return -1;
}

/*
Helper function for checkAbtWinAi(). Loops through all possible indexes in grid. 
Calls checkThreeAIVer() with next 3 indices. 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int verCheckAI(struct Grid * gridPtr, char sym) {
  int index;

  for (int row = 0; row < 6 - 2; row++) {
    for (int col = 0; col < 7; col++) {
      index = 7 * row + col;
      if (checkThreeAIVert(gridPtr, index, index + 7, index + 7 * 2, index + 7 * 3, sym)) {
        return (index);
      }
    }
  }
  return -1;
}

/*
Helper function for checkAbtWinAi(). Loops through all possible indexes in grid. 
Calls checkThreeAIDia() with next 3 indices. 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int leftdiaCheckAI(struct Grid * gridPtr, char sym) {
  int index, counter = 0;
  const int leftDia = 8;

  for (int row = 0; row < 6 - 3; row++) {
    for (int col = 0; col < 7; col++) {
      index = 7 * row + col;
      if (counter <= 2 && checkThreeAIDia(gridPtr, index, index + leftDia, index + leftDia * 2, index + leftDia * 3, sym) ) {
        return index;
      }
      counter = counter + 1;
    }
    counter = 0;
  }
  return -1;
}

/*
Helper function for checkAbtWinAi(). Loops through all possible indexes in grid. 
Calls checkThreeAIDia() with next 3 indices. 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int rightdiaCheckAI(struct Grid * gridPtr, char sym) {
  int index, counter = 0;
  const int rightDia = 6;

  for (int row = 0; row < 6 - 3; row++) {
    for (int col = 0; col < 7; col++) {
      index = 7 * row + col;
      if (counter >= 2 && checkThreeAIDia(gridPtr, index, index + rightDia, index + rightDia * 2, index + rightDia * 3, sym) ) {
        return index;
      }
      counter = counter + 1;
    }
    counter = 0;
  }
  return -1;
}

/*
This function checks for three in a row of either 'X' or 'O' in a row or a column and
returns the index of the 4th element if the element at that index is '.' (empty).
This function checks for the possibility of computer win or human win and acts accordingly.
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@returns: index of 4th element -> if value of the 4th index is '.'
          -1 -> if otherwise
*/
int checkAbtWinAI(struct Grid * gridPtr, char sym) {

  if (verCheckAI(gridPtr, sym) != -1) {               //vertical check
    return verCheckAI(gridPtr, sym);                  
  } else if (horCheckRightAI(gridPtr, sym) != -1) {   //right horizontal check
    return horCheckRightAI(gridPtr, sym);             
  } else if (rightdiaCheckAI(gridPtr,sym) != -1){     //right diagonal check
    return rightdiaCheckAI(gridPtr,sym);
  } else if (leftdiaCheckAI(gridPtr,sym) != -1){      //left diagonal check
    return leftdiaCheckAI(gridPtr,sym);
  } else if (horCheckLeftAI(gridPtr,sym)){            //left horizontal check
    return horCheckLeftAI(gridPtr,sym);
  }
  
  return -1;
}

/**************************************************************************************************
*                                Functions to check for win                                       *
**************************************************************************************************/

/*
Helper method for horCheck(), verCheck() and diaCheck(). Checks if four consecutive of either 'X' or 'O' exist.
@returns: 1 -> if there are 4 consecutive 'X' or 'O'
          0 -> if otherwise
*/
int checkFour(struct Grid * gridPtr, int w, int x, int y, int z) {
  return ((gridPtr + w) -> data == (gridPtr + x) -> data && (gridPtr + x) -> data == (gridPtr + y) -> data && (gridPtr + y) -> data == (gridPtr + z) -> data && (gridPtr + w) -> data != '.');
}

/*
Helper method for checkWin(). Loops through all possible indexes in grid.
Calls checkFour() with next 3 indices in a row.
@params: gridPtr -> It stores moves as 'X' and 'O'
@returns: 1 -> if there are 4 consecutive 'X' or 'O' in a horizontal and
          0 -> if otherwise
*/
int horCheck(struct Grid * gridPtr) {
  int index;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 7 - 3; col++) {
      index = 7 * row + col;
      if (checkFour(gridPtr, index, index + 1, index + 2, index + 3)) {
        return 1;
      }
    }
  }
  return 0;
}

/*
Helper method for checkWin(). Loops through all possible indexes in grid.
Calls checkFour() with next 3 indices in a column.
@params: gridPtr -> It stores moves as 'X' and 'O'
@returns: 1 -> if there are 4 consecutive 'X' or 'O' in a horizontal and
          0 -> if otherwise
*/
int verCheck(struct Grid * gridPtr) {
  int index;

  for (int row = 0; row < 6 - 3; row++) {
    for (int col = 0; col < 7; col++) {
      index = 7 * row + col;
      if (checkFour(gridPtr, index, index + 7, index + 7 * 2, index + 7 * 3)) {
        return 1;
      }
    }
  }
  return 0;
}

/*
Helper method for checkWin(). Loops through all possible indexes in grid.
Calls checkFour() with next 3 indices in a diagonal.
@params: gridPtr -> It stores moves as 'X' and 'O'
@returns: 1 -> if there are 4 consecutive 'X' or 'O' in a horizontal and
          0 -> if otherwise
*/
int diaCheck(struct Grid * gridPtr) {
  int index, counter = 0;
  const int rightDia = 6,
    leftDia = 8;

  for (int row = 0; row < 6 - 3; row++) {
    for (int col = 0; col < 7; col++) {
      index = 7 * row + col;
      if (counter <= 3 && checkFour(gridPtr, index, index + leftDia, index + leftDia * 2, index + leftDia * 3) || counter >= 3 && checkFour(gridPtr, index, index + rightDia, index + rightDia * 2, index + rightDia * 3)) {
        return 1;
      }
      counter = counter + 1;
    }
    counter = 0;
  }
  return 0;
}

/*
This function checks for win after each turn.
@params: gridPtr -> It stores moves as 'X' and 'O'
@returns: 1 -> if there are 4 consecutive 'X' or 'O' in a diagonal, vertical or horizontal  and
          0 -> if otherwise
*/
int checkWin(struct Grid * gridPtr) {
  return (verCheck(gridPtr) || horCheck(gridPtr) || diaCheck(gridPtr));
}

/*************************************************************************************************
*                                  Miscellaneous Functions                                       *
*************************************************************************************************/

/*
Function for printing the board
@params: gridPtr -> It stores moves as 'X' and 'O'
*/
void printBoard(struct Grid * gridPtr) {
  int row, col;

  printf("\n****CURRENT STATE****\n");
  printf(" 1  2  3  4  5  6  7\n");
  for (row = 0; row < 6; row++) {
    for (col = 0; col < 7; col++) {
      printf(" %c ", (gridPtr + (7 * row + col)) -> data);
    }
    puts(" ");
    puts("---------------------");
  }
  puts("\n");
}

/*
Fixes the position selected by user/computer into the board.
Records the moves.
Calls the  printboard function after each turn.
@params: col -> The column number 
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@params: move -> It records coloumn numbers of the moves as linked list
@params: i -> The ith number of move in the game
*/
void completeTurn(int col, struct Grid * gridPtr, char sym, struct Move * move, int i) {
  for (int row = 5; row >= 0; row--) {
    if ((gridPtr + (7 * row + col)) -> data == '.') {
      (gridPtr + (7 * row + col)) -> data = sym;
      (move + i) -> data = col;
      printBoard(gridPtr);
      return;
    }
  }

}

/*
Checks if a coloumn is Full
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: col -> The column number 
*/

int isColoumnFull(struct Grid * gridPtr, int col) {
  for (int i = 0; i < 6; i++) {
    if ((gridPtr + (i * 7 + (col - 1))) -> data == '.') {
      return 0;
    }
  }
  return 1;
}

/*
Function for user's Turn
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@params: move -> It records coloumn numbers of the moves as linked list
@params: i -> The ith number of move in the game
*/
void userTurn(struct Grid * gridPtr, char sym, struct Move * move, int i) {
  int input;
  puts("It is your chance.");
  point:
    printf("Select a letter from 1-7:");
  scanf("%i", & input);
  if (isColoumnFull(gridPtr, input)) {
    printf("\n\nColoumn is full! Enter a different Column!\n\n");
    goto point;
  }
  switch (input) {
  case 1:
    completeTurn(0, gridPtr, sym, move, i);
    break;
  case 2:
    completeTurn(1, gridPtr, sym, move, i);
    break;
  case 3:
    completeTurn(2, gridPtr, sym, move, i);
    break;
  case 4:
    completeTurn(3, gridPtr, sym, move, i);
    break;
  case 5:
    completeTurn(4, gridPtr, sym, move, i);
    break;
  case 6:
    completeTurn(5, gridPtr, sym, move, i);
    break;
  case 7:
    completeTurn(6, gridPtr, sym, move, i);
    break;
  default:
    printf("\nWrong choice entered!\n");
    goto point;
    break;
  }
}

/*
Analyses the board and completes computer's move
@params: gridPtr -> It stores moves as 'X' and 'O'
@params: sym -> symbol for the computer in this game i.e. 'X' or 'O'
@params: move -> It records coloumn numbers of the moves as linked list
@params: i -> The ith number of move in the game
*/
void computerTurn(struct Grid * gridPtr, char sym, struct Move * move, int i) {
  int col;
  int tempSym;
  srand(time(NULL));

  printf("The computer is thinking of a move...");
  sleep(2);

  col = checkAbtWinAI(gridPtr, sym) % 7;
  if (col == -1) {
    col = (rand() % 7) + 1;
    while (isColoumnFull(gridPtr, col)) {
      col = (rand() % 7) + 1;
    }
  }

  completeTurn(col, gridPtr, sym, move, i);
}

/*
Sets the board to initial stage
@params: gridPtr -> It stores moves as 'X' and 'O'
*/
void setBoard(struct Grid *gridPtr, struct Move *move) {
  for (int i = 0; i < 42; i++) {
    (gridPtr + i) -> data = '.';
  }
  for (int j = 0; j < 42; j++) {
    (move + j) -> data = 8;
  }
}

/*
Prints moves at the end of the game as a linked list
@param: move -> It records coloumn numbers of the moves as linked list
*/
void printMoves(struct Move *move){  
    printf("The list of moves is ");
    for (int z = 0; z < 42; z++) {
      if ((move + z) -> data == 8) {
        break;
      }
      printf("->%i", ((move + z) -> data) % 7 + 1);
    }
    printf("\n\n");
}

/*************************************************************************************************
*                                      Main                                                      *
*************************************************************************************************/

void main() {

  struct Grid * gridPtr; //pointer for the start of the grid
  struct Move * move; //pointer for the start of linked list to record moves
  char answer[3]; // stores input from user
  int gameStat; //variable to store win status
  int k, j;
  int noOfMoves = 0; //Keeps track of number of moves played

  gridPtr = (struct Grid * ) calloc(42, sizeof(struct Grid));
  move = (struct Move * ) calloc(42, sizeof(struct Move));
  printf("\t\t\t CONNECT FOUR GAME\n\n");
  printf("Do you wanna start the game:");
  scanf("%s", answer);
  if (strcmp("yes", answer) != 0) {
    printf("Have a nice day!");
    exit(0);
  }

  while (strcmp("yes", answer) == 0) {
    setBoard(gridPtr, move);
    noOfMoves = 0;
    printf("Do you wanna go first:");
    scanf("%s", answer);
    printBoard(gridPtr);
    if (strcmp("yes", answer) == 0) {
      for (j = 0; j < 42; j++) {    // if user goes first

        userTurn(gridPtr, 'X', move, noOfMoves);
        noOfMoves = noOfMoves + 1;
        gameStat = checkWin(gridPtr);
        if (gameStat == 1) {
          printf("\t\t\tUser won the game!! Congratulations!!\n\n ");
          break;
        }

        computerTurn(gridPtr, 'O', move, noOfMoves);
        noOfMoves = noOfMoves + 1;
        gameStat = checkWin(gridPtr);
        if (gameStat == 1) {
          printf("\t\t\tComputer won the game!! Better luck next time.\n\n");
          break;
        }
      }
    } 
    else {
      for (k = 0; k < 42; k++) {   // if computer goes first

        computerTurn(gridPtr, 'X', move, noOfMoves);
        noOfMoves = noOfMoves + 1;
        gameStat = checkWin(gridPtr);
        if (gameStat == 1) {
          printf("\t\t\tComputer won the game!! Better luck next time.\n\n");
          break;
        }

        userTurn(gridPtr, 'O', move, noOfMoves);
        noOfMoves = noOfMoves + 1;
        gameStat = checkWin(gridPtr);
        if (gameStat == 1) {
          printf("\t\t\tUser won the game!! Congratulations!!\n\n ");
          break;
        }
      }
    }
    if (k == 42 || j == 42) {      
        printf("\t\tThe game is tied!\n");
    }
    printMoves(move); 
    printf("Do you wanna play once more?");
    scanf("%s", answer);
    system("clear");
  }

  return;

}