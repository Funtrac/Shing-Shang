coord * generetable(){
  //Initialisation du tableau de pointeurs
  coord * plateau[10][10];
  //Initialisation du tableau de type de cases
  coord * tcase = malloc(9*sizeof(coord));
  //Case Inaccessible
  *(tcase)->type = 1;
  *(tcase)->team = 0;
  //Pions Blancs et portail
  *(tcase+1)->type = 1;
  *(tcase+1)->team = 1;

  *(tcase+2)->type = 2;
  *(tcase+2)->team = 1;

  *(tcase+3)->type = 3;
  *(tcase+3)->team = 1;

  *(tcase+4)->type = 4;
  *(tcase+4)->team = 1;

  //Pions Noirs et portail
  *(tcase+5)->type = 1;
  *(tcase+5)->team = 2;

  *(tcase+6)->type = 2;
  *(tcase+6)->team = 2;

  *(tcase+7)->type = 3;
  *(tcase+7)->team = 2;

  *(tcase+8)->type = 4;
  *(tcase+8)->team = 2;
  //Initialisation du tableau à la valeur NULL
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      plateau[i][j] = NULL;
    }
  }
  //Triangle 1
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4-i; j++) {
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
  for (i = 0; i < 4; i++) {
    for (j = 9; j > 5+i; j-- {
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
  for (i = 7; i < 10; i++) {
    for (j = 0; j < i-6; j++) {
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
  //Tiangle 4
  for (i = 7; i < 10; i++) {
    for (j = 9; j > 8+7-i; j--) {
      if (j==9) {
        plateau[i][j] = tcase;
      }
      else if(i==j{
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
}
