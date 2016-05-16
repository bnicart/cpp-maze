#include "iostream"
#include "stdio.h"
#include <unistd.h>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

#define SIZE 30

char maze[SIZE][SIZE];
char facing = 'F';

struct POSITION {
  int x;
  int y;
  char face;
  char base;
} currPos, endPos;

void createStartEndPoints() {
  
  srand(time(NULL));
  int sp = 0;
  int ep = 0;
  while(sp == 0 || sp == SIZE) {
    sp = rand() % SIZE;
  }
  while(ep == 0 || ep == SIZE) {
    ep = rand() % SIZE;
  }
  maze[sp][0] = '>';
  maze[ep][SIZE-1] = '_';

  endPos.x = ep;
  endPos.y = SIZE-1;
  endPos.face = '_';
  endPos.base = '_';

  currPos.x = sp;
  currPos.y = 0;
  currPos.face = '>';
  currPos.base = '>';
}

void generateMaze() {
  for( int a = 0 ; a < SIZE ; a++ ) {
    for( int b = 0 ; b < SIZE ; b++ ) {
      if( a == 0 || b == 0 || a == SIZE-1 || b == SIZE-1 ) {
        maze[a][b] = '#';
      } else {
        maze[a][b] = ' ';
      }
    }
  }
  srand(time(NULL));

  for( int a = 0 ; a < SIZE*8 ; a++ ) {
      maze[rand()%SIZE][rand()%SIZE] = '#';
  }

  createStartEndPoints();
}

void printMaze() {
  for( int a = 0 ; a < SIZE ; a++ ) {
    for( int b = 0 ; b < SIZE ; b++ ) {
        printf("%2c", maze[a][b]);
    }
    std::cout << "\n";
  }
}

bool isTraversable(int x, int y) {
  return maze[x][y] != '#';
}

POSITION getCurrentPosition() {
  /* POSITION pos; */
  /* for( int a = 0 ; a < SIZE ; a++ ) { */
  /*   for( int b = 0 ; b < SIZE ; b++ ) { */
  /*     if( maze[a][b] == '>' || */
  /*         maze[a][b] == '^' || */
  /*         maze[a][b] == '<' || */
  /*         maze[a][b] == 'v' ) { */
  /*       pos.x = a; */
  /*       pos.y = b; */
  /*       pos.face = maze[a][b]; */
  /*     } */
  /*   } */
  /* } */
  return currPos;
}

POSITION getNextPosition( POSITION tempCurrPos ) {
  POSITION nextPos = tempCurrPos;
  
  if( currPos.base == '>' ) {
    /* if( isTraversable( nextPos.x, nextPos.y+1) ) { */
    /*   nextPos.y++; */
    /* } */ 
    /* else */ 
    if( isTraversable( nextPos.x+1, nextPos.y ) ) {
      nextPos.x++;
      nextPos.face = 'v';
      nextPos.base = 'v';
    }
    else {
      nextPos.base = '^';
      nextPos.face = '>';
    }
  }
  else if( currPos.base == '^' ) {
    /* if( isTraversable( nextPos.x-1, nextPos.y ) ){ */
    /*   nextPos.x--; */
    /* } */
    /* else */ 
    if( isTraversable( nextPos.x, nextPos.y+1 ) ) {
      nextPos.y++;
      nextPos.face = '>';
      nextPos.base = '>';
    }
    else {
      nextPos.base = '<';
      nextPos.face = '^';
    }
  }
  else if( currPos.base == '<' ) {
    /* if( isTraversable( nextPos.x, nextPos.y-1 ) ) { */
    /*   nextPos.y--; */
    /* } */
    /* else */
    if( isTraversable( nextPos.x-1, nextPos.y ) ) {
      nextPos.x--;
      nextPos.face = '^';
      nextPos.base = '^';
    } else {
      nextPos.base = 'v';
      nextPos.face = '<';
    }
  }
  else if( currPos.base == 'v' ) {
    /* if( isTraversable( nextPos.x+1, nextPos.y ) ) { */
    /*   nextPos.x++; */
    /* } */
    /* else */
    if( isTraversable( nextPos.x, nextPos.y-1 ) ) {
      nextPos.y--;
      nextPos.face = '<';
      nextPos.base = '<';
    } else {
      nextPos.base = '>';
      nextPos.face = 'v';
    }
  }

  return nextPos;
}

POSITION getEndPosition() {
  /* POSITION pos; */
  /* for( int a = 0 ; a < SIZE ; a++ ) { */
  /*   for( int b = 0 ; b < SIZE ; b++ ) { */
  /*     if( maze[a][b] == '_') { */
  /*       pos.x = a; */
  /*       pos.y = b; */
  /*     } */
  /*   } */
  /* } */
  /* pos.face = '>'; */
  return endPos;
}

void move( POSITION currPos, POSITION nextPos ) {
  maze[currPos.x][currPos.y] = ' ';
  maze[nextPos.x][nextPos.y] = nextPos.face;
}

void traverseMaze() {
  while( getEndPosition().x != getCurrentPosition().x || 
         getEndPosition().y != getCurrentPosition().y ) {
    POSITION tempCurr = getCurrentPosition();
    POSITION tempNext = getNextPosition(tempCurr); 
    move( tempCurr, tempNext );
    currPos = tempNext;
    printMaze();
    /* printf("CPos: (%d, %d)\nEPos: (%d, %d)\n\n", getCurrentPosition().x, getCurrentPosition().y, getEndPosition().x, getEndPosition().y); */
    usleep(50*1000);
    /* sleep(1); */
  }
}

int main() {
  system("clear");
  generateMaze();
  printMaze();
  traverseMaze();
  return 0;
}
