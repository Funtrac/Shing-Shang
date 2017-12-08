#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef struct{
	int type;
	int team;
} pion ;
typedef struct{
	int x;
	int y;
} coord ;

void deplacable(coord coordonnees, coord * autorise[][10], coord * plateau[][10]){
	int varx,vary,tmpx,tmpy;
	for (int i=0; i <3 ; i++){
		for (int j=0; j<3; j++){
			varx=coordonnees.x-1+i;
			vary=coordonnees.y-1+i;
			if (varx<0){
				varx=0;
			}
			if (vary<0){
				varx=0;
			}
			if (plateau[varx][vary]==NULL) {
				autorise[varx][vary]=1;
			}
			else {
				autorise[varx][vary]=0;
				difx=varx-coordonnees.x;
				dify=vary-coordonnees.y;
				if (plateau[varx+difx][vary+dify]==NULL) {
					autorise[varx+difx][vary+dify]=1;
				}
				else {
					autorise[varx+difx][vary+dify]=0;
				}
			}
		}
	}
}

void deplacement_singe(coord cordonnees,  coord * plateau[][10], coord movefrom, coord moveto){
	coord * autorise[10][10];
	deplacable(movefrom, autorise,plateau)
	printf("")
}

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

int affichageplateau(pion * plateau[][10],int xcolor, int ycolor){
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
			if (j == xcolor && i == ycolor) {
				affichecase(testteam,testtype,1);
			}
			else{
				affichecase(testteam,testtype,0);
			}
		}
    printf("\n");
	}
}


coord * generetable(pion * plateau[][10], pion * tcase){
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
pion * plateau[10][10];
//Initialisation du tableau de type de cases
pion * tcase = (pion *) malloc(9*sizeof(coord)); // À EXPLIQUER
generetable(plateau,tcase);
affichageplateau(plateau,0,0);

coord coordselect;
coordselect.x = 0;
coordselect.y = 0;

coord focused;
focused.x = 0;
focused.y = 0;

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
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	if (c == '\033') {
		if (getchar()) {
			switch (getchar()) {
				case 'A':
				if (focused.y > 0) {
					focused.y -= 1;
				}
				break;
				case 'B':
				if (focused.y < 9) {
					focused.y += 1;
				}
				break;
				case 'C':
				if (focused.x < 9) {
					focused.x += 1;
				}
				break;
				case 'D':
				if (focused.x > 0) {
					focused.x -= 1;
				}
				break;
			}
		}
		affichageplateau(plateau,focused.x,focused.y);
	}
	else if(c=='\n'){
		coordselect = focused;
	}
}


/*restore the old settings*/
tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
free(tcase);
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
return 1;
}
