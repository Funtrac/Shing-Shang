#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef struct{
	int type;
	int team;
} coord ;
typedef struct{
	int x;
	int y;
} selected ;



void affichecase(int team, int type,int colored){
	char * tabaff[3][5];
	tabaff[0][0]="·";
	tabaff[0][1]="▒";
	tabaff[1][1]="◇";
	tabaff[1][2]="△";
	tabaff[1][3]="○";
  tabaff[1][4]="P";
	tabaff[2][1]="◆";
	tabaff[2][2]="▲";
	tabaff[2][3]="●";
  tabaff[2][4]="P";
	if (colored) {
		printf("\x1b[33m%s\x1b[0m ",tabaff[team][type]);
	}
	else{
		printf("%s ",tabaff[team][type]);
	}

}

int affichageplateau(coord * plateau[][10],int xcolor, int ycolor){
	int testtype, testteam;
	for (int i=0; i<10; i++){
		for (int j=0; j<10; j++){
      if (plateau[i][j] != NULL) {
        testtype=plateau[i][j]->type;
  			testteam=plateau[i][j]->team;
      }
      else{
        testtype = 0;
        testteam = 0;
      }
			if (i == xcolor && j == ycolor) {
				affichecase(testteam,testtype,1);
			}
			else{
				affichecase(testteam,testtype,0);
			}
		}
    printf("\n");
	}
}


coord * generetable(coord * plateau[][10], coord * tcase){
  //Case Inaccessible
  (tcase)->type = 1;
  (tcase)->team = 0;
  //Pions Blancs et portail blanc
  (tcase+1)->type = 1;
  (tcase+1)->team = 1;

  (tcase+2)->type = 2;
  (tcase+2)->team = 1;

  (tcase+3)->type = 3;
  (tcase+3)->team = 1;

  (tcase+4)->type = 4;
  (tcase+4)->team = 1;

  //Pions Noirs et portail noir
  (tcase+5)->type = 1;
  (tcase+5)->team = 2;

  (tcase+6)->type = 2;
  (tcase+6)->team = 2;

  (tcase+7)->type = 3;
  (tcase+7)->team = 2;

  (tcase+8)->type = 4;
  (tcase+8)->team = 2;
  //Initialisation du tableau à la valeur NULL
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      plateau[i][j] = NULL;
    }
  }
  //Triangle 1
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4-i; j++) {
      if (j==0) {
        plateau[i][j] = tcase;
      }
      else if((3-j)==i){
        plateau[i][j] = tcase+1;
      }
      else if (i==(j-1)) {
				plateau[i][j] = tcase+3;
      }
      else{
				plateau[i][j] = tcase+2;
      }
    }
  }
  //Triangle 2
  for (int i = 0; i < 4; i++) {
    for (int j = 9; j > 5+i; j--) {
      if (j==9) {
        plateau[i][j] = tcase;
      }
      else if(i==(j-6)){
        plateau[i][j] = tcase+1;
      }
      else if (i==(j-7)) {
        plateau[i][j] = tcase+2;
      }
      else{
        plateau[i][j] = tcase+3;
      }
    }
  }
  //Triangle 3
  for (int i = 6; i < 10; i++) {
    for (int j = 0; j < i-5; j++) {
      if (j==0) {
        plateau[i][j] = tcase;
      }
      else if((i-6)==j){
        plateau[i][j] = tcase+5;
      }
      else if ((i-7)==j) {
        plateau[i][j] = tcase+6;
      }
      else{
        plateau[i][j] = tcase+7;
      }
    }
  }
  //Triangle 4
  for (int i = 6; i < 10; i++) {
    for (int j = 9; j > 8+6-i; j--) {
      if (j==9) {
        plateau[i][j] = tcase;
      }
      else if(i==(15-j)){
        plateau[i][j] = tcase+5;
      }
      else if (i==(16-j)) {
        plateau[i][j] = tcase+6;
      }
      else{
        plateau[i][j] = tcase+7;
      }
    }
  }
}


int main(){
//Initialisation du tableau de pointeurs
coord * plateau[10][10];
//Initialisation du tableau de type de cases
coord * tcase = (coord *) malloc(9*sizeof(coord)); // À EXPLIQUER
generetable(plateau,tcase);
affichageplateau(plateau,0,0);

selected coordselect;
selected.x = 0;
selected.y = 0

int c;
static struct termios oldt, newt;

/*tcgetattr gets the parameters of the current terminal
STDIN_FILENO will tell tcgetattr that it should write the settings
of stdin to oldt*/
tcgetattr( STDIN_FILENO, &oldt);
/*now the settings will be copied*/
newt = oldt;

/*ICANON normally takes care that one line at a time will be processed
that means it will return if it sees a "\n" or an EOF or an EOL*/
newt.c_lflag &= ~(ICANON);

/*Those new settings will be set to STDIN
TCSANOW tells tcsetattr to change attributes immediately. */
tcsetattr( STDIN_FILENO, TCSANOW, &newt);

/*This is your part:
I choose 'e' to end input. Notice that EOF is also turned off
in the non-canonical mode*/
int stop = 0;
while((c=getchar())!= '&'){
	if (c == '\033') {
		if (getchar()) {
			switch (getchar()) {
				case 'A':
					printf("Haut");
					selected.y -= 1;
				break;
				case 'B':
					printf("Bas");
					selected.y += 1;
				break;
				case 'C':
					printf("Droite");
					selected.x += 1;
				break;
				case 'D':
					printf("Gauche");
					selected.y -= 1;
				break;
			}
		}
		affichageplateau(plateau,selected.x,selected.y);
	}
}


/*restore the old settings*/
tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
free(tcase);
return 1;
}
