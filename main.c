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

void requestmove(pion * plateau[][10],coord * movefrom,coord * moveto){
	switch (plateau[movefrom->x][movefrom->y]->type) {
		case 1:

		break;
		case 2:

		break;
		case 3:

		break;
	}
	movefrom->x = -1;
	movefrom->y = -1;
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
	switch (colored) {
		case 2 :
			printf("\x1b[31m%s\x1b[0m ",tabaff[team][type]);
		break;
		case 1 :
			printf("\x1b[33m%s\x1b[0m ",tabaff[team][type]);
		break;
		default:
			printf("%s ",tabaff[team][type]);
		break;
	}
}

int affichageplateau(pion * plateau[][10],coord focused, coord selected){
	int testtype, testteam;
	for (int i=0; i<10; i++){
		for (int j=0; j<10; j++){
      if (plateau[j][i] != NULL) {
        testtype=plateau[j][i]->type;
  			testteam=plateau[j][i]->team;
      }
      else{
        testtype = 0;
        testteam = 0;
      }
			if (j == selected.x && i == selected.y) {

				affichecase(testteam,testtype,2);
			}
			else if (j == focused.x && i == focused.y) {
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
        plateau[j][i] = tcase;
      }
      else if((3-j)==i){
        plateau[j][i] = tcase+1;
      }
      else if (i==(j-1)) {
				plateau[j][i] = tcase+3;
      }
      else{
				plateau[j][i] = tcase+2;
      }
    }
  }
  //Triangle 2
  for (int i = 0; i < 4; i++) {
    for (int j = 9; j > 5+i; j--) {
      if (j==9) {
        plateau[j][i] = tcase;
      }
      else if(i==(j-6)){
        plateau[j][i] = tcase+1;
      }
      else if (i==(j-7)) {
        plateau[j][i] = tcase+2;
      }
      else{
        plateau[j][i] = tcase+3;
      }
    }
  }
  //Triangle 3
  for (int i = 6; i < 10; i++) {
    for (int j = 0; j < i-5; j++) {
      if (j==0) {
        plateau[j][i] = tcase;
      }
      else if((i-6)==j){
        plateau[j][i] = tcase+5;
      }
      else if ((i-7)==j) {
        plateau[j][i] = tcase+6;
      }
      else{
        plateau[j][i] = tcase+7;
      }
    }
  }
  //Triangle 4
  for (int i = 6; i < 10; i++) {
    for (int j = 9; j > 8+6-i; j--) {
      if (j==9) {
        plateau[j][i] = tcase;
      }
      else if(i==(15-j)){
        plateau[j][i] = tcase+5;
      }
      else if (i==(16-j)) {
        plateau[j][i] = tcase+6;
      }
      else{
        plateau[j][i] = tcase+7;
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

coord coordselect;
coordselect.x = -1;
coordselect.y = -1;

coord focused;
focused.x = 0;
focused.y = 0;

affichageplateau(plateau,focused,coordselect);

int isplaying = 1;

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
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//printf("\n");
	if (c == '\033') {
		if (getchar()) {
			switch (getchar()) {int c;
static struct termios oldt, newt;
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
	}
	else if(c=='\n'){
		if (coordselect.x != -1 && coordselect.y != -1) {
			requestmove(plateau,&coordselect,&focused);
		}
		else{
			if (plateau[focused.x][focused.y]!=NULL) {
				if (plateau[focused.x][focused.y]->team == isplaying) {
					coordselect = focused;
					printf("Sélectionné !\n");
				}
				else if (!plateau[focused.x][focused.y]->team) {//team 0 = case maudite
					printf("Vous ne pouvez pas sélectionner une case maudite !\n");
				}
				else if (plateau[focused.x][focused.y]->type == 4) {//type 4 = portail
					printf("Vous ne pouvez pas déplacer un portail !\n");
				}
				else{
					printf("Vous ne pouvez pas sélectionner un pion ennemi !\n");
				}
			}
			else{
				printf("Vous ne pouvez pas sélectionner une case vide\n");
			}
		}
	}
		affichageplateau(plateau,focused,coordselect);
}


/*restore the old settings*/
tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
free(tcase);
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
return 1;
}
