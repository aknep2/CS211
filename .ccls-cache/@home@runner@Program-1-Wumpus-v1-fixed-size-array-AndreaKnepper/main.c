/*-------------------------------------------------------------------------------
        Program 1: Wumpus, version 1 (fixed size array)
        Description: Game that allows player to move around a map, avoiding pits
and Wumpus. The object of this iteration of the game is to guess where Wumpus is
before you die! Course: CS 141, Fall 2022. Thursday 10 am Lab System: Windows
11, Using Replit Author: Andrea Knepper
---------------------------------------------------------------------------------
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // for srand
//--------------------------------------------------------------------------------
void displayCave() {
  printf("\n       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}

//--------------------------------------------------------------------------------
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' to guess which room Wumpus is in, to win or lose the "
         "game!\n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()

//--------------------------------------------------------------------------------

void randomSetup(int array[6]) {
  srand(1);
  // srand(time(0)) for actual randomization
  for (int i = 0; i < 2; i++) {
    array[i] = 0;
  }
  for (int i = 2; i < 6; i++) {
    array[i] = rand() % 20 + 1;
  }
}

int checkValid(int var[6]) {
  int valid = 0;
  for (int i = 0; i < 6; i++)
    if (var[i] > 0 && var[i] < 20) {
      valid++;
    }
  return valid;
}

int main(void) {

  int gameObjects[6]; // 0 - bat, 1 - bat, 2 - pit1, 3 - pit2, 4 - wumpus, 5 -
                      // player
  randomSetup(gameObjects);

  int guess;
  int validRoom = 0;
  int stench = 0;
  int draft = 0;
  char playerMove;
  int desiredRoom; // must check that player's move is valid before moving there
  int moveCount = 1; // counts number of player moves
  int check[6];

  int map[21][3] = {{0, 0, 0},    {2, 5, 8},    {1, 3, 10},  {2, 12, 4},
                    {3, 5, 15},   {1, 4, 6},    {5, 7, 15},  {6, 8, 17},
                    {1, 7, 9},    {8, 10, 18},  {2, 11, 9},  {10, 12, 19},
                    {3, 13, 11},  {12, 14, 20}, {4, 15, 13}, {6, 16, 14},
                    {15, 17, 20}, {7, 18, 16},  {9, 19, 17}, {11, 20, 18},
                    {13, 16, 19}};
  // run until the player enters 'x' or 'X'
  while (playerMove != 'x' && playerMove != 'X') {
    // display instructions
    if (playerMove == 'd' || playerMove == 'D') {
      displayCave();
      displayInstructions();
    }
    // cheat, player can view game piece locations
    if (playerMove == 'c' || playerMove == 'C') {
      printf("Cheating! Game elements are in the following rooms: \n"
             "Player Wumpus Pit1 Pit2  \n"
             "%4d %7d %5d %5d \n\n",
             gameObjects[5], gameObjects[4], gameObjects[2], gameObjects[3]);
    }
    // print cave layout
    if (playerMove == 'p' || playerMove == 'P') {
      displayCave();
    }
    // allow player to move to adjacent rooms
    if (playerMove == 'm' || playerMove == 'M') {
      validRoom = 0; // can't use a bool w/ the loop or it will override, use
                     // incrementation of a variable instead
      scanf(" %d", &desiredRoom);
      for (int i = 0; i < 3; i++) { // checks if the desired room is adjacent to
                                    // player's current room
        if (map[gameObjects[5]][i] == desiredRoom) {
          validRoom++;
        }
      }
      if (validRoom > 0) {            // if room is adjacent...
        gameObjects[5] = desiredRoom; // move player to their desired room
        moveCount++;                  // increment the move counter
      } else { // if player room is not adjacent, have them input a valid move
        printf("Invalid move.  Please retry. \n");
      }
    }
    // guess which room wumpus is in
    if (playerMove == 'g' || playerMove == 'G') {
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf("%d", &guess);
      if (guess == gameObjects[4]) { // if guess is correct --> wins
        printf("You won!\n");
      }
      if (guess !=
          gameObjects[4]) { // if guess is incorrect --> loses and exits program
        printf("You lost.\n");
      }
      printf("\nExiting Program ...\n");
      return 0;
    }
    // change location of game pieces
    if (playerMove == 'r' || playerMove == 'R') {
      printf("Enter the room locations (1..20) for player, wumpus, pit1, and "
             "pit2: \n"
             "\n");
      for (int i = 2; i < 6; i++) {
        scanf(" %d", &check[i]);
      }
      if (checkValid(check) == 6) { // check entered values are between 1 & 2
        gameObjects[2] = check[4];
        gameObjects[3] = check[5];
        gameObjects[4] = check[3];
        gameObjects[5] = check[2];
      }
      if (checkValid(check) != 6) {
        printf("Invalid move.  Please retry.\n");
      }
    }

    // if wumpus room is even, player dies
    if (gameObjects[5] == gameObjects[4] && gameObjects[4] % 2 == 0) {
      printf(
          "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
      printf("\nExiting Program ...\n");
      return 0;
    }
    // if wumpus room is odd, wumpus moves to lowest value room
    if (gameObjects[5] == gameObjects[4] && gameObjects[4] % 2 == 1) {
      if (map[gameObjects[5]][0] != gameObjects[2] &&
          map[gameObjects[5]][0] !=
              gameObjects[3]) { // no pit, wumpus moves into the lowest adjacent
                                // room
        gameObjects[4] =
            map[gameObjects[5]][0]; // map is layed out so lowest adjacent room
                                    // is always position [0]
        printf("You hear a slithering sound, as the Wumpus slips away. \n"
               "Whew, that was close! \n");
        // if wumpus can't move into the lowest room because there is a pit
        // there, wumpus kills the player
      } else {
        printf(
            "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
            "It is over.\n");
        printf("\nExiting Program ...\n");
        return 0;
      }
    }
    // if player enters room with a pit, dies
    if (gameObjects[5] == gameObjects[2] || gameObjects[5] == gameObjects[3]) {
      printf("Aaaaaaaaahhhhhh....   \n");
      printf("    You fall into a pit and die. \n");
      printf("\nExiting Program ...\n");
      return 0;
    }
    // message with player's location
    printf("You are in room %d. ", gameObjects[5]);
    stench = 0;
    draft = 0;
    for (int i = 0; i < 3; i++) {
      if (map[gameObjects[5]][i] == gameObjects[4]) {
        stench++;
      }
      if (map[gameObjects[5]][i] == gameObjects[2] ||
          map[gameObjects[5]][i] == gameObjects[3]) {
        draft++;
      }
    }
    if (stench > 0) {
      printf("You smell a stench. "); // wumpus in adjacent room
    }
    if (draft > 0) {
      printf("You feel a draft. "); // pit is in adjacent room
    }

    printf("\n\n%d. Enter your move (or 'D' for directions): ", moveCount);
    scanf(" %c",
          &playerMove); // scan for next move to run through while loop again
  }
  // when while loop breaks, that means that the player has entered 'x' or 'X',
  // so the program ends
  printf("\nExiting Program ...\n");
  return 0;
}