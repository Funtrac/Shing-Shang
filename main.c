#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*
A faire :
- Vérifier que le déplacement n'est pas enregistré
*/


typedef struct{
	int type;
	int team;
} pion ;
typedef struct{
	int x;
	int y;
} coord ;

void clearboard(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
void displaylogo(){
	printf("------------------------------------------------------------------------------\n");
	printf("  ____    _       _                     ____    _                             \n");
	printf(" / ___|  | |__   (_)  _ __     __ _    / ___|  | |__     __ _   _ __     __ _ \n");
	printf(" \\___ \\  | '_ \\  | | | '_ \\   / _` |   \\___ \\  | '_ \\   / _` | | '_ \\   / _` |\n");
	printf("  ___) | | | | | | | | | | | | (_| |    ___) | | | | | | (_| | | | | | | (_| |\n");
	printf(" |____/  |_| |_| |_| |_| |_|  \\__, |   |____/  |_| |_|  \\__,_| |_| |_|  \\__, |\n");
	printf("                              |___/                                     |___/ \n");
	printf("------------------------------------------------------------------------------\n");
	printf("\n\n");
}
void displaycurrent(int joueur,char msg[]) {
	if (msg != " ") {
		printf("%s\n",msg);
	}
	else{
		printf("                          C'est à Joueur %d de jouer                          \n", joueur);
	}
	printf("\n");
}
void displayfooter(){
	printf("\n& : quitter |  ←↕→ : se déplacer  |  Entrée (↵) : sélectionner une case  \n");
}
void displayconf(){
	printf("\nq : quitter sans sauvegarder |  w : sauvegarder et quitter | ! : annuler \n");
}
void displayintro() {
	printf("------------------------------------------------------------------------------\n");
	printf("  ____    _       _                     ____    _                             \n");
	printf(" / ___|  | |__   (_)  _ __     __ _    / ___|  | |__     __ _   _ __     __ _ \n");
	printf(" \\___ \\  | '_ \\  | | | '_ \\   / _` |   \\___ \\  | '_ \\   / _` | | '_ \\   / _` |\n");
	printf("  ___) | | | | | | | | | | | | (_| |    ___) | | | | | | (_| | | | | | | (_| |\n");
	printf(" |____/  |_| |_| |_| |_| |_|  \\__, |   |____/  |_| |_|  \\__,_| |_| |_|  \\__, |\n");
	printf("                              |___/                                     |___/ \n");
	printf("______________________________________________________________________________\n");
	printf("\n\n");
	printf("                          DUVAL Lucas - MEURDRAC Téo                          \n");
	printf("                       2017 - Université Caen Normandie                       \n");
	printf("\n\n\n\n\n\n");
	printf("                           ───────────────────────                            \n");
	printf("                           Press Enter to Continue                            \n");
	printf("                           ───────────────────────                            \n");
	printf("\n\n");
}
void clearcoordtable(coord table[], int index){
	for (int i = 0; i <= index; i++) {
		table[i].x = 0;
		table[i].y = 0;
	}
}
int abs(int x){
	if (x <0 ){
		x=-x;
	}
	return x;
}

int movesinge(pion * plateau[][10],coord movefrom,coord moveto, int isplaying){
	int val = 0;
	coord coordcheck;
	if(abs(movefrom.x-moveto.x) <=2 && abs(movefrom.y-moveto.y) <= 2){
		printf("Working\n");
		//test si déplacement de 1 ou de 2
		if(abs(movefrom.x-moveto.x) == 2 || abs(movefrom.y-moveto.y) == 2){
			//si déplacement de 2 alors
			printf("Dep 2\n");
			//test si coord = une case du carré 5x5 impossible a atteindre
			if(!(abs(movefrom.x-moveto.x) == 2 && abs(movefrom.y-moveto.y)==1) && (!(abs(movefrom.x-moveto.x) == 1 && abs(movefrom.y-moveto.y)==2))){
				//calcul de la case "de passage"
				coordcheck.x = movefrom.x+(moveto.x-movefrom.x)/2;
				coordcheck.y = movefrom.y+(moveto.y-movefrom.y)/2;
				if(plateau[coordcheck.x][coordcheck.y] == NULL){
					plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
					plateau[movefrom.x][movefrom.y] = NULL;
					val = 1; //return normal move value
				}
				else{
					if(plateau[coordcheck.x][coordcheck.y]->team == isplaying && plateau[coordcheck.x][coordcheck.y]->type <= plateau[movefrom.x][movefrom.y]->type){
						//if same team && type1>=type2
						plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
						plateau[movefrom.x][movefrom.y] = NULL;
						val = 2;
					}
					else if(plateau[coordcheck.x][coordcheck.y]->type <= plateau[movefrom.x][movefrom.y]->type){
						//If ennemy team && type1>=type2
						plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
						plateau[movefrom.x][movefrom.y] = NULL;
						plateau[coordcheck.x][coordcheck.y] = NULL;
						val = 2; //return jump value
					}
				}
			}
		}
		else{
			//si déplacement de 1
			printf("Dep 1\n");
			if(plateau[moveto.x][moveto.y] == NULL){//test si occupé
				plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
				plateau[movefrom.x][movefrom.y] = NULL;
				val = 1;//return normal move value
			}
		}
	}
	printf("val = %d\n",val);
	return val;
}
int movelion(pion * plateau[][10],coord movefrom,coord moveto, int isplaying){
	int val = 0;
	coord coordcheck;
	if(abs(movefrom.x-moveto.x) <=1 && abs(movefrom.y-moveto.y) <= 1){
		printf("Working\n");
			if(plateau[moveto.x][moveto.y] == NULL){//test si occupé
				plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
				plateau[movefrom.x][movefrom.y] = NULL;
				val = 1;//return normal move value
			}
		}
	printf("val = %d\n",val);
	return val;
}

int movedragon(pion * plateau[][10],coord movefrom,coord moveto, int isplaying){
	int val = 0;
	coord coordcheck;
	if(abs(movefrom.x-moveto.x) <=2 && abs(movefrom.y-moveto.y) <= 2){
		printf("Working\n");
		//test si déplacement de 1 ou de 2
		if(abs(movefrom.x-moveto.x) == 2 || abs(movefrom.y-moveto.y) == 2){
			//si déplacement de 2 alors
			printf("Dep 2\n");
			//test si coord = une case du carré 5x5 impossible a atteindre
			if(!(abs(movefrom.x-moveto.x) == 2 && abs(movefrom.y-moveto.y)==1) && (!(abs(movefrom.x-moveto.x) == 1 && abs(movefrom.y-moveto.y)==2))){
				//calcul de la case "de passage"
				coordcheck.x = movefrom.x+(moveto.x-movefrom.x)/2;
				coordcheck.y = movefrom.y+(moveto.y-movefrom.y)/2;
				if(plateau[coordcheck.x][coordcheck.y]->team == isplaying && plateau[coordcheck.x][coordcheck.y]->type <= plateau[movefrom.x][movefrom.y]->type){
					//if same team && type1>=type2
					plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
					plateau[movefrom.x][movefrom.y] = NULL;
					val = 2;
				}
				else if(plateau[coordcheck.x][coordcheck.y]->type <= plateau[movefrom.x][movefrom.y]->type){
					//If ennemy team && type1>=type2
					plateau[moveto.x][moveto.y] = plateau[movefrom.x][movefrom.y];
					plateau[movefrom.x][movefrom.y] = NULL;
					plateau[coordcheck.x][coordcheck.y] = NULL;
					val = 2; //return jump value
				}
			}
		}
	}
printf("val = %d\n",val);
return val;
}
int requestmove(pion * plateau[][10],coord movefrom,coord moveto,int isplaying,int mustBeJump){
	int val = 0;
	switch (plateau[movefrom.x][movefrom.y]->type) {
		case 1:
		printf("Requested\n");
		val = movesinge(plateau,movefrom,moveto,isplaying);
		break;
		case 2:
		val = movelion(plateau,movefrom,moveto,isplaying);
		break;
		case 3:
		val = movedragon(plateau,movefrom,moveto,isplaying);
		break;
	}
	return val;
}
void nextplayer(int * isp){
	if (*isp==1)
	*isp=2;
	else
	*isp=1;
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

void affichageplateau(pion * plateau[][10],coord focused, coord selected,int isplaying,char * msg){
	int testtype, testteam;
	displaylogo();
	displaycurrent(isplaying,msg);
	for (int i=0; i<10; i++){
		for (int k = 0; k < 28; k++) {
			printf(" ");
		}
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
	displayfooter();
}


void generetable(pion * plateau[][10], pion * tcase){
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
	//Portails Blancs
	plateau[4][1] = tcase+4;
	plateau[5][1] = tcase+4;
	//Portails Noirs
	plateau[4][8] = tcase+8;
	plateau[5][8] = tcase+8;

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
	int g,val;
	int isplaying = 1;
	int brek = 0;
	char * msg = "";
	static struct termios oldt, newt;
	coord movememory[100];
	int countmemory = 0;
	int allowAllMove = 0;
	/*tcgetattr gets the parameters of the current terminal
	STDIN_FILENO will tell tcgetattr that it should write the settings
	of stdin to oldt*/
	tcgetattr( STDIN_FILENO, &oldt);
	/*now the settings will be copied*/
	newt = oldt;

	/*ICANON normally takes care that one line at a time will be processed
	that means it will-1 return if it sees a "\n" or an EOF or an EOL*/
	newt.c_lflag &= ~(ICANON);

	/*Those new settings will be set to STDIN
	TCSANOW tells tcsetattr to change attributes immediately. */
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	clearboard();
	displayintro();

	while (getchar()!= '\n') {
		clearboard();
		displayintro();
	}
	//Initialisation du tableau de pointeurs
	pion * plateau[10][10];
	//Initialisation du tableau de tmsgype de cases
	pion * tcase = (pion *) malloc(9*sizeof(coord)); // À EXPLIQUER
	clearboard();
	generetable(plateau,tcase);

	coord coordselect;
	coordselect.x = -1;
	coordselect.y = -1;

	coord focused;
	focused.x = 0;
	focused.y = 0;

	affichageplateau(plateau,focused,coordselect,isplaying,"");


	while(brek != 1 && (g=getchar())){
		clearboard();
		if (g == '\033') {
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
			affichageplateau(plateau,focused,coordselect,isplaying,msg);
		}
		else if(g=='\n'){
			if (coordselect.x != -1 && coordselect.y != -1 && (plateau[focused.x][focused.y] == NULL || plateau[focused.x][focused.y]->type == 4)) {
				allowAllMove = 1;
				for (int i = 0; i < countmemory; i++) {
					if (movememory[i].x == coordselect.x && movememory[i].y == coordselect.y) {
							allowAllMove--;
					}
				}
				if (allowAllMove) {
					val = requestmove(plateau,coordselect,focused,isplaying,0);
				}
				else{
					requestmove(plateau,coordselect,focused,isplaying,1);
				}


				if (val == 1) {
					nextplayer(&isplaying);
					msg = "";
					coordselect.x = -1;
					coordselect.y = -1;
				}
				else if(val == 2){
					msg = "                Voulez-vous continuer a jouer ? (O/N)                    ";
					while(g != 'o' && g != 'O' && g != 'n' && g != 'N'){
						affichageplateau(plateau,focused,coordselect,isplaying,msg);
						g = getchar();
					}
					if (g == 'n' && g == 'N') {
						nextplayer(&isplaying);
						clearcoordtable(movememory,countmemory);
						countmemory = 0;
						coordselect.x = -1;
						coordselect.y = -1;
						msg = " ";
					}
					else{
						msg = " ";
						movememory[countmemory] = focused;
						countmemory++;
						coordselect.x = -1;
						coordselect.y = -1;
					}
				}
				else if (!val) {
					msg = "                          Déplacement impossible !                              ";
					coordselect.x = -1;
					coordselect.y = -1;
				}
			}
			else{
				if (plateau[focused.x][focused.y]!=NULL) {
					if (plateau[focused.x][focused.y]->team == isplaying && plateau[focused.x][focused.y]->type != 4) {
						coordselect = focused;
						msg = "                               Sélectionné !                                  ";
					}
					else if (!plateau[focused.x][focused.y]->team) {//team 0 = case maudite
						msg = "             Vous ne pouvez pas sélectionner une case maudite !               ";

					}
					else if (plateau[focused.x][focused.y]->type == 4) {//type 4 = portail
						msg = "                  Vous ne pouvez pas déplacer un portail !                    ";
					}
					else{
						msg = "              Vous ne pouvez pas sélectionner un pion ennemi !                ";
					}
				}
				else{
					msg = "                 Vous ne pouvez pas sélectionner une case vide                  ";
				}
			}
			affichageplateau(plateau,focused,coordselect,isplaying,msg);
		}
		else if (g == '&') {
			val = 1;
			do {
				if (g == 'w' || g == 'W') {
					val = -1;
					brek = 1;
				}
				else if (g == 'q' || g == 'Q') {
					brek = 1;
					val = -1;
				}
				else if(g == '!'){
					val = -1;
				}
				clearboard();
				displaylogo();
				displayconf();
				if (g != 'w' && g != 'W' && g != 'q' && g != 'Q' && g != '!') {
					g = getchar();
				}
			}while (val != -1);
		}
	}


	/*restore the old settings*/
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	free(tcase);
	clearboard();
	return 1;
}
