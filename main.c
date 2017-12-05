#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int type;
	int team;
} coord ;



void affichagecase(int team, int type){
	char tabaff[3][2];
	tabaff[0][1]='X';
	tabaff[1][1]='D';
	tabaff[1][2]='L';
	tabaff[1][3]='S';
	tabaff[2][1]='D';
	tabaff[2][2]='L';
	tabaff[2][3]='S';
	printf("%c\n",tabaff[type][team]);
}

int affichageplateau(coord * plateau[][]){
	int testtype, testteam;
	for (int i=0; i<10; i++){
		for (int j=0; j<10; j++){
			testtype=plateau[i][j]->type;
			testteam=plateau[i][j]->team;
			affichecase(testteam,testtype) ;
		}
	}
}


coord * generetable(){
  //Initialisation du tableau de pointeurs
	coord * plateau[10][10];
	//Initialisation du tableau de type de cases
  coord * tcase = (int*)malloc(9*sizeof(coord)); // À EXPLIQUER
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
      else if(i==j){
        plateau[i][j] = tcase+1;
      }
      else if (i==(j-1)) {
        plateau[i][j] = tcase+2;
      }
      else{
        plateau[i][j] = tcase+3;
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
  for (int i = 7; i < 10; i++) {
    for (int j = 0; j < i-6; j++) {
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
  for (int i = 7; i < 10; i++) {
    for (int j = 9; j > 8+7-i; j--) {
      if (j==9) {
        plateau[i][j] = tcase;
      }
      else if(i==j){
        plateau[i][j] = tcase+5;
      }
      else if (i==(j-1)) {
        plateau[i][j] = tcase+6;
      }
      else{
        plateau[i][j] = tcase+7;
      }
    }
  }
	affichageplateau(plateau)
}


int main(){

generetable(tabaff);
free(tcase);
return 1;
}
