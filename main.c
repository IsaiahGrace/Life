//gcc -Werror -Wall main.c -o Life
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>

#define COLOR
#ifdef COLOR
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BLACK   "\x1b[22"
#define RESET   "\x1b[0m"
#endif

#ifndef COLOR
#define RED     ""
#define GREEN   ""
#define YELLOW  ""
#define BLUE    ""
#define MAGENTA ""
#define CYAN    ""
#define BLACK   ""
#define RESET   ""
#endif
//#define PURDUE  "\x1b[38;2;<194>;<142>;<14>m"

int main(int argc, char **argv) {

  int i;
  int j;
  int k;
  int crowd;
  int alive;
  int height; //ascociate with i
  int width; //ascociate with j


  if(argc == 3) {
    height = atoi(argv[1]);
    width = atoi(argv[2]);
  } else {
    struct winsize size;
  	ioctl( 0, TIOCGWINSZ, (char *) &size );
    //printf( "Rows: %u\nCols: %u\n", size.ws_row, size.ws_col);
    height = size.ws_row - 1;
    width = size.ws_col + 2;
  }

  if(argc == 2) {
    srand(atoi(argv[1]));
  } else {
    srand(time(NULL));
  }


  int **map = malloc(height * sizeof(int *));
  int **next = malloc(height * sizeof(int *));
  int **prev = malloc(height * sizeof(int *));
  for(i = 0; i < height; i++) {
    map[i] = malloc(width * sizeof(int));
    next[i] = malloc(width * sizeof(int));
    prev[i] = malloc(width * sizeof(int));
  }

  //Initilize Map
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      if(i == 0 || j == 0 || i == (height - 1) || j == (width - 1)) {
      map[i][j] = 0;
    } else {
      map[i][j] = (rand() & 1);
    }
      next[i][j] = 0;
      prev[i][j] = 0;
    }
    printf("\n");
  }
  printf("\033[1A");

  //Hardcode a glider
  /*
  map[1][2] = 1;
  map[2][3] = 1;
  map[3][1] = 1;
  map[3][2] = 1;
  map[3][3] = 1;
  */

  //Hardcode a glider gun
  /*
  map[6][2] = 1;
  map[7][2] = 1;
  map[6][3] = 1;
  map[7][3] = 1;

  map[6][12] = 1;
  map[7][12] = 1;
  map[8][12] = 1;
  map[5][13] = 1;
  map[9][13] = 1;
  map[4][14] = 1;
  map[10][14] = 1;
  map[4][15] = 1;
  map[10][15] = 1;

  map[7][16] = 1;

  map[5][17] = 1;
  map[9][17] = 1;
  map[6][18] = 1;
  map[7][18] = 1;
  map[8][18] = 1;
  map[7][19] = 1;

  map[4][22] = 1;
  map[5][22] = 1;
  map[6][22] = 1;
  map[4][23] = 1;
  map[5][23] = 1;
  map[6][23] = 1;
  map[3][24] = 1;
  map[7][24] = 1;
  map[2][26] = 1;
  map[3][26] = 1;
  map[7][26] = 1;
  map[8][26] = 1;

  map[4][36] = 1;
  map[5][36] = 1;
  map[4][37] = 1;
  map[5][37] = 1;
  */

  //Start LIFE
  for(k = 0; k < 1000; k++) {
    //Print Map as is
    alive = 0;
    for(i = 0; i < height - 1; i++) {
    printf("\033[1A");
  }
    printf("%d\n", k);
    for(i = 1; i < height - 1; i++) {
      for(j = 1; j < width - 1; j++) {
        if(map[i][j]) {
          if(prev[i][j]) {
            printf(""RESET"\u2588");
          } else {
            printf(""GREEN"\u2588");
          }
          alive = 1;
        } else {
          if(prev[i][j]) {
            printf(""RED"\u2591");
          } else {
          printf(""RESET"\u2591");
          }
        }
      }
      printf("\n");
    }
    if(!alive) {break;}

    //Update The next map
    for(i = 1; i < height - 1; i++) {
      for(j = 1; j < width - 1; j++) {
        //Count Neighbours
        crowd = 0;
        if(map[i - 1][j - 1]) {crowd++;}
        if(map[i][j - 1]) {crowd++;}
        if(map[i + 1][j - 1]) {crowd++;}

        if(map[i - 1][j + 1]) {crowd++;}
        if(map[i][j + 1]) {crowd++;}
        if(map[i + 1][j + 1]) {crowd++;}

        if(map[i + 1][j]) {crowd++;}
        if(map[i - 1][j]) {crowd++;}

        //Update next with values
        if(crowd < 2) {next[i][j] = 0;}
        if(crowd == 2 && map[i][j]) {next[i][j] = 1;}
        if(crowd == 3) {next[i][j] = 1;}
        if(crowd > 3) {next[i][j] = 0;}
      }
    }

    //Transfer next values to map and reset next
    alive = 0;
    for(i = 0; i < height - 1; i++) {
      for(j = 0; j < width - 1; j++) {
        if(map[i][j] != next[i][j]) {alive = 1;}
        prev[i][j] = map[i][j];
        map[i][j] = next[i][j];
        next[i][j] = 0;
      }
    }
    if(!alive) {break;}
    //wait one second 1,000,000 = 1 sec
    usleep(10000);
  }

  //Free malloc'd memory
  for(i = 0; i < height; i++) {
    free(map[i]);
    free(next[i]);
    free(prev[i]);
  }
  free(map);
  free(next);
  free(prev);

  return EXIT_SUCCESS;
}
