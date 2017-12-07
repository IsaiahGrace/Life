//gcc -Werror -Wall main.c -o Life
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>

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
    width = size.ws_col;
  }

  srand(time(NULL));

  int **map = malloc(height * sizeof(int *));
  int **next = malloc(height * sizeof(int *));
  for(i = 0; i < height; i++) {
    map[i] = malloc(width * sizeof(int));
    next[i] = malloc(width * sizeof(int));
  }

  //Initilize Map
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      if(i == 0 || j == 0 || i == (height - 1) || j == (width - 1)) {
      map[i][j] = 0;
    } else {//if (i == 1 || i == (height - 2) || j == 1 || j == (width - 2)) {
      //map[i][j] = 1;
      map[i][j] = (rand() & 1);
    } //else {
      //map[i][j] = 0;
    //}
      next[i][j] = 0;
    }
    printf("\n");
  }
  printf("\033[1A");

  for(k = 0; k < 100; k++) {
    //Print Map as is
    alive = 0;
    for(i = 0; i < height - 1; i++) {
    printf("\033[1A");
  }
    printf("%d\n", k);
    for(i = 1; i < height - 1; i++) {
      for(j = 1; j < width - 1; j++) {
        if(map[i][j]) {
          printf("\u2588");
          alive = 1;
        } else {
          printf("\u2591");
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
        map[i][j] = next[i][j];
        next[i][j] = 0;
      }
    }
    if(!alive) {break;}
    //wait one second 1_000_000 = 1 sec
    usleep(100000);
  }

  //Free malloc'd memory
  for(i = 0; i < height; i++) {
    free(map[i]);
    free(next[i]);
  }
  free(map);
  free(next);

  return EXIT_SUCCESS;
}
