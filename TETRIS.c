//Tetris
// By Anderson Castro B.

#include<stdio.h>
// Para utilizar la funcion de numeros aleatorios
#include <stdlib.h>
#include <time.h>
// Para utilizar Sleep
#include <unistd.h>
//Define constantes el numero de filas V y el numero de columnas H
#define V 40
#define H 40

//Para kbhit() in linux
#include <string.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

//Para clear
#define clear() printf("\033[H\033[J")

//Prototipos de las funciones
void inicio(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody);
void borde(char campo[V][H]);
void dl(char l[4][6]);
void dlarg(char larg[2][8]);
void dcuad(char cuad[4][4]);
void dt(char t[4][6]);
void dz(char z[4][1]);
void leercampo(char campo[V][H], long long puntaje);
void inifig(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody);
void loopcampo(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody, long long puntaje);
void draw(char campo[V][H], long long puntaje);
void input(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int *r ,int *inix, int *iniy, int *modx, int *mody, int *fin, int izq, int der, long long *puntaje);
void update(char campo[V][H], char campop[V][H],char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody);
void loopcampo2(char campo[V][H], char campop[V][H],char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody, long long puntaje);
void input2(char campo[V][H], char campop[V][H],char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int *r ,int *inix, int *iniy, int *modx, int *mody, int *fin, int izq, int der, long long *puntaje);
void final(void);
void izquno(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k);
void izqdos(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k);
void izqtres(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k);

//Toque entre figuras
void toca(char campo[V][H], char campop[V][H], int *rr, int *inixx, int *iniyy, int *modxx, int *finn, int *izq, int *der);
void figl(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr);
void figt(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr);
void figcuad(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr);
void figlarg(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr);
void figz(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr);
//

//Para correr filas
void corre(char campop[V][H], int fil);
//
int kbhit(void);
//


int main(void){
	int n,m;
	int r;//Para obtener una figura aleatoria
	int inix, iniy;//Posicion incial de la figura
	int modx, mody;//Posicion Modificada
	char campo[V][H]; //Campo de Juego
	char campop[V][H]; //Campo auxiliar
	char l[4][6]; //Figura L
	char larg[2][8]; //Figura larga
	char cuad[4][4]; //Figura cuadrada
	char t[4][6]; //Figura T
	char z[4][1]; //Figura larga delgada
	long long puntaje = -100;

	 //Inicializamos campop
	 //Este es utilizado para guardar el campo una vez la figura termine su recorrido
	 for(n = 0; n <= V-1; n++){
	 	for(m = 0; m <= H-1; m++){
	 		campop[n][m] = ' ';
		 }
	 }

    srand(time(NULL)); //El mayordomo pone a girar la diana

    //Inicializar posiciones
	r = rand()%5;// Numero aleatorio
	inix = (rand()%31) + 1;
	iniy = 1;

	//Inicializar modificaciones
	modx = rand()%4;// Numero aleatorio
	mody = 1;

	//system("COLOR 0C");
	printf("\n\n\n\n\n\n\n\n");
	printf("               |\\ \n");
	printf("        -------- \\                                          WELCOME TO C\n");
	printf("        |         \\                                      THIS GAME IS TETRIS\n");
    printf("        |         /                                    I HOPE YOU ENJOY THE GAME\n");
    printf("        -------- /                              -->EVERYTHING GLORY IS TO GOD FOREVER<--\n");
    printf("               |/ \n");
    printf("\n\n");
    printf("|    |    |    |    |    |    |    |\n");
    printf("v    v    v    v    v    v    v    v\n\n");

    //Pause
	getchar();

	//Funciones Principales
	inicio(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody);
	loopcampo(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody, puntaje);


	return 0;
}


// KBHIT()
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}


//Esta funcion inicializa el campo de juego e introduce la figura inicial
void inicio(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody){
	borde(campo);
	dl(l);
	dlarg(larg);
	dcuad(cuad);
	dt(t);
	dz(z);
	inifig(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody);
}


// Figura Borde del juego
void borde(char campo[V][H]){
	int i,j;

	for (i = 0; i <= V-1; i++){
		for (j = 0; j <= H-1; j++){
			if (i == 0 || i == V-1 ){
				campo[i][j] = '/';
			}
			else if (j == 0 || j == H-1){
				campo[i][j] = '/';
			}
			else{
				campo[i][j] = ' ';
			}
		}
	}
}


// Figura L
void dl(char l[4][6]){
	int i,j;

	for(i = 0; i < 4; i++){
		for (j = 0; j < 6; j++){
			if (i > 1){
				l[i][j] = 'O';
			}
			else{
				if(j < 2){
					l[i][j] = 'O';
				}
				else{
					l[i][j] = ' ';
				}
			}
		}
	}
}


// Figura larga
void dlarg(char larg[2][8]){
	int i,j;

	for(i = 0; i < 2; i++){
		for (j = 0; j < 8; j++){
			larg[i][j] = 'O';
		}
	}
}


//Figura cuadrado
void dcuad(char cuad[4][4]){
	int i,j;

	for(i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			cuad[i][j] = 'O';
		}
	}
}

// Figura t
void dt(char t[4][6]){
	int i,j;

	for(i = 0; i < 4; i++){
		for (j = 0; j < 6; j++){
			if (i > 1){
				t[i][j] = 'O';
			}
			else{
				if(j == 2 || j == 3){
					t[i][j] = 'O';
				}
				else{
					t[i][j] = ' ';
				}
			}
		}
	}
}


//Figura Z
void dz(char z[4][1]){
	int i;

	for(i = 0; i < 4; i++){
		z[i][0] = 'O';
	}
}


//Lectura de Objetos
void leercampo(char campo[V][H], long long puntaje){
	int i,j;
	//leer campo
	for (i = 0; i< V; i++){
		//Espacio
		//__________________________________________________________________//
		switch (i){
		///////_____________________________////////
		case 14:
		printf("                                 ***   SCORE   ****      ");
		break;
		case 16:
		printf("                                 ##################      ");
		break;
		case 17:
		case 18:
		printf("                                 #                #      ");
		break;
		case 19:
		 //___________________________________________//
        if(puntaje < 10){
        printf("                                 #       %lld        #      ",puntaje); }
        else if(puntaje <= 900){
        printf("                                 #      %lld       #      ",puntaje); }
        else if(puntaje > 900 && puntaje <= 9900){
        printf("                                 #      %lld      #      ",puntaje); }
        else if(puntaje > 9900 && puntaje <= 99900){
        printf("                                 #      %lld     #      ",puntaje); }
        else if(puntaje > 99900 && puntaje <= 999900){
        printf("                                 #     %lld     #      ",puntaje); }
        else if(puntaje > 999900 && puntaje <= 9999900){
        printf("                                 #    %lld     #      ",puntaje); }
        else if(puntaje > 9999900 && puntaje <= 99999900){
        printf("                                 #   %lld     #      ",puntaje); }
		//___________________________________________//
		break;
		case 20:
		case 21:
		printf("                                 #                #      ");
		break;
	    case 22:
		printf("                                 ##################      ");
		break;
		///////_____________________________////////
		default:
		printf("                                                         ");//57
		break;
	    }
	    //__________________________________________________________________//
		for (j = 0; j < H; j++){
			printf("%c",campo[i][j]);
			}
			printf("     ");
			//Para imprimir Titulo del Juego
			switch (i){
				case 0:
				printf("XXXXXXXXX XXXXX XXXXXXX XXXX   XXXXX   XXXX      \n");
				break;
				case 1:
				printf("    X     X        X    X   X    X    X    X     \n");
				break;
				case 2:
				printf("    X     X        X    X   X    X    X          \n");
				break;
				case 3:
				printf("    X     XXXX     X    XXXX     X     XXXX      \n");
				break;
				case 4:
				printf("    X     X        X    X   X    X         X     \n");
				break;
				case 5:
				printf("    X     X        X    X   X    X     X   X     \n");
				break;
				case 6:
				printf("    X     XXXX     X    X   X  XXXXX    XXX      \n");
				break;
				case 7:
				printf("\n");
				break;
				case 8:
				printf("\n");
				break;
				case 9:
				printf("    BY ANDERSON CASTRO B\n");
				break;
				default:
				printf("\n");
				break;
				//Fin del titulo del juego
			}
	}
}


//Posicion inicial de todos lo objetos en el campo al actualizarla
void inifig(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody){
int i,j, h, k;
int cont = 0;//para rayo
int tra = 0;

//Para el ciclo #1
int a,s;

//Ciclo #1 para leer lo guardado en el campo auxiliar
for(a = 1; a <= V-2; a++){
	for(s = 1; s <= H-2; s++){
		campo[a][s] = campop[a][s];
	}
}

///////////////////////////////////
for(i = iniy+1; i <= 38; i++){
	if((campo[i][inix] == ' ' || campo[i][inix] == '|')&& tra == 0){
		cont++;
	}
	else{
		tra = 1;
	}
}

//_______________________________//
for(i = iniy+1; i <= iniy+cont ; i+=2){
    campo[i][inix] = '|';
}
///////////////////////////////////

  //Para imprimir las figuras en el campo, en la posicion que se encuentren.
  switch (modx) {

  //-------------------------------------------//
  case 0:

  switch (r) {

  //oooooooooooooooo//
  case 0:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +5; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 i++;
			   }
			   else{
                 campo[h][j] = l[k][i];
                 i++;
               }
            //
           }
           k += 1;
       }
       i = 0;
    }
  break;
  //oooooooooooooooo//

  case 1:

  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 1){
           for (j = inix; j<= inix +7; j++){
                 campo[h][j] = larg[k][i];
                 i++;
           }
           k += 1;
       }
       i = 0;
    }
  break;
  //oooooooooooooooo//

  case 2:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
                 campo[h][j] = cuad[k][i];
                 i++;
           }
           k += 1;
       }
       i = 0;
    }
  break;
  //oooooooooooooooo//

  case 3:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +5; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 i++;
			   }
			   else{
                 campo[h][j] = t[k][i];
                 i++;
               }
            //
           }
           k += 1;
       }
       i = 0;
    }
  break;
  //oooooooooooooooo//

  default:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           campo[h][inix] = z[k][0];
           k += 1;
       }
    }
  break;
  //oooooooooooooooo//
  }

  break;
  //-------------------------------------------//

  case 1:
  izquno(campo, l, larg, cuad, t, z, r, inix, iniy, k);
  break;
  //-------------------------------------------//

  case 2:
  izqdos(campo, l, larg, cuad, t, z, r, inix, iniy, k);
  break;
  //-------------------------------------------//

  default:
  izqtres(campo, l, larg, cuad, t, z, r, inix, iniy, k);
  break;
  //-------------------------------------------//
 }

 	//Eliminar residuos del rayo
	for(i = 1; i <= V-2; i++){
		for(j = 1; j <= H-2; j++){
			if(campop[i][j] == '|'){
				campop[i][j] = ' ';
			}
		}
	}
	//
}


//Primer ciclo
void loopcampo(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody, long long puntaje){
	int i,j;
	int fin;
	fin = 0;
	int izq,der = 0;

	puntaje += 100;

	do{
		draw(campo, puntaje);//Dibujar en pantalla
		// Figura toca a otra figura
        toca(campo, campop, &r, &inix, &iniy, &modx, &fin, &izq, &der);
        //
		input(campo, campop,l, larg, cuad, t, z, &r,&inix, &iniy, &modx, &mody, &fin, izq, der, &puntaje);//Verificar y modificar posiciones
		update(campo, campop,l, larg, cuad, t, z, r, inix, iniy, modx, mody);//Actualizar matriz
		usleep(150000);//controla la velocidad de cambio de actualizacion
	}while(fin == 0);
	if (fin == 1){
    srand(time(NULL)); //El mayordomo pone a girar la diana
	r = rand()%5;// Numero aleatorio
	modx = rand()%4;// Numero aleatorio
	inix = (rand()%31) + 1;// Numero aleatorio
	//se entra en otro ciclo, para que ingrese otra figura al campo.
	loopcampo2(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody, puntaje);
    }
}


//Ejecuta la funcion leercampo
void draw(char campo[V][H], long long puntaje){
	system("clear");
	//clear();
	leercampo(campo, puntaje);
}


//Modifica el campo de juego para en Primer ciclo
void input(char campo[V][H], char campop[V][H],char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int *r ,int *inix, int *iniy, int *modx, int *mody, int *fin, int izq, int der, long long *puntaje){
    char tecla;
    int i,j;//Para loops
    int m;//Para loops
    int b, p, con, fil;//Para fila llena
    static int confin;//Para finalizar
	static int len;//Para realentizar el juego
	int cont2, salo;//Para finalizar
    salo = 0;
    con = 0;
    cont2 = 0;

	   //Verificaciones

	   //Figura toca el suelo
	   if(*iniy == V-2){

		*fin = 1;
		*iniy = 1;
		for(i = 0; i<= V-1; i++){
		    for(j = 0; j <= H-1; j++){
			campop[i][j] = campo[i][j];
	    	}
    	}
	  }///////////////



	  //Fila llena
	  for(b = 1; b <= V-2; b++ ){
	  	for(p = 1; p <= H-2; p++){
	  	if(campop[b][p] == 'O'){
	  		con++;
		  }
	    }
	    if(con == 38){
	    	fil = b;
	    	//Elimina fila rellena
	          for(m = 1; m <= H-2; m++){
	              campop[fil][m] = ' ';
	             }
	        //Corra las filas hacia abajo
	          corre(campop, fil);
	          *puntaje += 2000;
	    }////////////////////////
	    	else{
	    	fil = 0;
			con = 0;
			}
	  }///////////////


	  //\BFAcaba el juego?
	  for(m = 1; m<= H-1; m++){
	  	//
	  	if(salo == 0){
	  	//
	  	if(campo[1][m] == 'O'){
	  		confin += 1;
	  		salo = 1;
	  	    }
	  		else{
	  			cont2 += 1;
			  }
	    }//
	  }/////////////////

      // Para finalizar
	  if(cont2 > 37){
	  	confin = 0;
	  }//


	//MODIFICACIONES
	//Mover figura en el campo
	if(len == 1){
	  *iniy += *mody;
	  len = 0;
	}
	else{
     len++;
    }


	//Game over
	if(confin > 25){
	final();
    }
	//////////End game over



	//Modifica la posicion de la figura en campo, con entradas externas
	//Derecha, izquierda y hacia abajo
	if(kbhit() > 0){
		tecla = getchar();

	    //Movimiento izquieda

		if(izq == 0){
		//__________________//
		if(tecla == 'a'){
			if(*inix > 1){
			    *inix += -1;
		    }
		}
		//////////////////
		if(tecla == 'q'){
	           *inix += -2;
		    }
		//__________________//
	    }

     //Movimiento hacia la derecha

        if(der == 0){
		//__________________//
		if(tecla == 'd'){
		   *inix += +1;
	    }
	    /////////////////////
	    if(tecla == 'e'){
	       *inix += +2;
		}
		//__________________//
	}

		//Para bajar mas rapido
		if(tecla == 's'){
			if(*iniy < 30){
			*iniy += 2;
		    }
		}

		//Para hacer girar la figura
	     if(tecla == 'w'){
	     	if(*modx == 3){
	     		*modx = 0;
	     	    }
	     		else{
	     			*modx += 1;
				 }
			 }

		//Para poner pausea
		if(tecla == 'p'){
		printf("                  PAUSE\n");
		//Pause
		getchar();
	    }
	}
	////////////////////////////Acaba movimiento

	izq = 0;
	der = 0;
}


//Se encarga de actualizar el campo
void update(char campo[V][H], char campop[V][H],char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx,int mody){
	borde(campo);
	dl(l);
	dlarg(larg);
	dcuad(cuad);
	dt(t);
	dz(z);
	inifig(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody);
}


//Segundo ciclo
void loopcampo2(char campo[V][H],char campop[V][H] ,char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r ,int inix, int iniy, int modx, int mody, long long puntaje){
	int i,j,fin;
	fin = 0;
	int izq, der = 0;

	puntaje += 100;

	do{
		draw(campo, puntaje);//Dibujar en pantalla
		// Figura toca a otra figura
        toca(campo, campop, &r, &inix, &iniy, &modx, &fin, &izq, &der);
        //
		input2(campo, campop, l, larg, cuad, t, z, &r,&inix, &iniy, &modx, &mody, &fin, izq, der, &puntaje);//Verificar y modificar posiciones
		update(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody);//Actualizar matriz
		usleep(150000);//controla la velocidad de cambio de actualizacion
	}while(fin == 0);

	//srand(time(NULL)); //El mayordomo pone a girar la diana
	r = rand()%5;// Numero aleatorio
	modx = rand()%4;// Numero aleatorio
	inix = (rand()%31) + 1;// Numero aleatorio
	//Entra nueva mente al ciclo uno, para seguir jugando
	loopcampo(campo, campop, l, larg, cuad, t, z, r, inix, iniy, modx, mody, puntaje);
}


//Modifica el campo de juego para en segundo ciclo
void input2(char campo[V][H], char campop[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int *r ,int *inix, int *iniy, int *modx, int *mody, int *fin, int izq, int der, long long *puntaje){
    char tecla;
    int i,j;
    int m;
    int b, c, fil, con;
    static int confin;
	static int len;
	int cont2, salo;//Para finalizar
	salo = 0;
	cont2 = 0;
    con = 0;


    //Verificaciones


    // Figura llega al suelo
	if(*iniy == V-2){
		for(i = 0; i<= V-1; i++){
		    for(j = 0; j <= H-1; j++){
			campop[i][j] = campo[i][j];
	    	}
    	}
	}

	// Figura llega al suelo
	if(*iniy == V-2){
		*fin = 1;
		*iniy = 1;
	}


		  //Fila llena
	  for(b = 1; b <= V-2; b++ ){
	  	for(c = 1; c <= H-2; c++){
	  	if(campop[b][c] == 'O'){
	  		con++;
		  }
	    }
	    if(con == 38){
	    	fil = b;
	    	//Elimina fila rellena
	          for(m = 1; m <= H-2; m++){
	              campop[fil][m] = ' ';
	             }
	        //Corra filas
			corre(campop, fil);
			*puntaje += 2000;
	    }////////////////////////
	    	else{
	    	/*
	    	for(m = 1; m <= H-2; m++){
	            campop[fil][m] = campop[fil][m];
	        }
	        */
	    	fil = 0;
			con = 0;
			}
	  }///////////////


	  //\BFAcaba el juego?
	  for(m = 1; m<= H-1; m++){
	  	//
	  	if(salo == 0){
	  	//
	  	if(campo[1][m] == 'O'){
	  		confin += 1;
	  		salo = 1;
	  	    }
	  	    else{
	  	    cont2 += 1;
			}
	    }//
	  }/////////////////

      // Para finalizar
	  if(cont2 > 37){
	  	confin = 0;
	  }//


	//MODIFICACIONES
	//Mover figura en el campo
    if(len == 1){
	  *iniy += *mody;
	  len = 0;
	}
	else{
     len++;
    }

    //Game over
	if(confin > 25){
	final();
    }
	//////////End game over

	//Modifica la posicion de la figura en campo, con entradas externas
	//Derecha, izquierda y hacia abajo
	if(kbhit() == 1){
		tecla = getchar();

	//Movimiento izquieda

		if(izq == 0){
		//__________________//
		if(tecla == 'a'){
			if(*inix > 1){
			    *inix += -1;
		    }
		}
	    //////////////////
		if(tecla == 'q'){
	           *inix += -2;
		    }
		//__________________//
	    }

	//Movimiento hacia la derecha

        if(der == 0){
		//__________________//
		if(tecla == 'd'){
		   *inix += +1;
	    }
	    /////////////////////
	    if(tecla == 'e'){
	           *inix += +2;
		}
		//__________________//
	}

	//Para bajar mas rapido
	if(tecla == 's'){
			if(*iniy < 30){
			*iniy += 2;
		    }
		}

		//Para hacer girar la figura
	     if(tecla == 'w'){
	     	if(*modx == 3){
	     		*modx = 0;
	     	    }
	     		else{
	     			*modx += 1;
				 }
			 }

	    //Para poner pause
	    if(tecla == 'p'){
		   printf("                  PAUSE\n");
		   //Pause
		   getchar();
	    }
	////////////////////////////Acaba movimiento
	}

	izq = 0;
	der = 0;
}



//Finaliza el juego cuando el jugador pierde(XD)
void final(void){

	printf("              !GAME  OVER!              \n");
	getchar();

}


//Funcion para giro 1; hacia la izquierda
void izquno(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k){
	int i,j,h;

	switch(r){
	//ooooooooooooo//
	case 0:
  	k = 0;
  	i = 3;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
           	     //
           	     if(campo[h][j] == 'O'){
           	     	campo[h][j] = 'O';
           	     	k++;
					}
				 else{
                 campo[h][j] = l[k][i];
                 k++;
                 }

                 //
           }
           i--;
       }
       k = 0;
    }
    break;
	//ooooooooooooo//

	case 1:
	k = 0;
  	i = 3;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +1; j++){
                 campo[h][j] = larg[k][i];
                 k++;
           }
           i--;
       }
       k = 0;
    }
    break;
    //ooooooooooooo//

    case 2:
    k = 0;
    i = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
                 campo[h][j] = cuad[k][i];
                 i++;
           }
           k += 1;
       }
       i = 0;
    }
    break;
    //ooooooooooooo//

    case 3:
    k = 0;
  	i = 5;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 5){
           for (j = inix; j<= inix +3; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 k++;
			   }
			   else{
                 campo[h][j] = t[k][i];
                 k++;
               }
           //
           }
           i--;
       }
       k = 0;
    }
    break;
    //ooooooooooooo//

    case 4:
   	k = 0;
  	i = 3;

    for (j = inix; j<= inix +3; j++){
        campo[iniy][j] = larg[k][i];
        i--;
        }

   break;
   //ooooooooooooo//
   }
}


//Funcion para giro 2; hacia la izquierda
void izqdos(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k){
int i, j, h;

 switch (r) {
  //ooooooooooooo//
  case 0:
  	i = 5;
  	k = 3;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +5; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 i--;
           	}
           		else{
                 campo[h][j] = l[k][i];
                 i--;
                }
           //
           }
           k--;
       }
       i = 5;
    }
  break;
  //ooooooooooooo//

  case 1:
  	i = 0;
  	k = 1;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 1){
           for (j = inix; j<= inix +7; j++){
                 campo[h][j] = larg[k][i];
                 i++;
           }
           k--;
       }
       i = 0;
    }
  break;
  //ooooooooooooo//

  case 2:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
                 campo[h][j] = cuad[k][i];
                 i++;
           }
           k += 1;
       }
       i = 0;
    }
  break;
  //ooooooooooooo//

  case 3:
  	i = 0;
  	k = 3;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +5; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 i++;
			   }
			   else{
                 campo[h][j] = t[k][i];
                 i++;
               }
            //
           }
           k--;
       }
       i = 0;
    }
  break;
  //ooooooooooooo//

  default:
  	k = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           campo[h][inix] = z[k][0];
           k += 1;
       }
    }
  break;
  //ooooooooooooo//
  }
}


//Funcion para giro 2; hacia la izquierda
void izqtres(char campo[V][H], char l[4][6], char larg[2][8], char cuad[4][4], char t[4][6], char z[4][1], int r, int inix, int iniy, int k){
	int i,j,h;

	switch(r){
	//ooooooooooooo//
	case 0:
  	k = 3;
  	i = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
           	//
           	if(campo[h][j] == 'O'){
           		campo[h][j] = 'O';
                 k--;
			   }
			   else{
                 campo[h][j] = l[k][i];
                 k--;
               }
           //
           }
           i++;
       }
       k = 3;
    }
    break;
	//ooooooooooooo//

	case 1:
	k = 0;
  	i = 3;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +1; j++){
                 campo[h][j] = larg[k][i];
                 k++;
           }
           i--;
       }
       k = 0;
    }
    break;
    //ooooooooooooo//

    case 2:
    k = 0;
    i = 0;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 3){
           for (j = inix; j<= inix +3; j++){
                 campo[h][j] = cuad[k][i];
                 i++;
           }
           k += 1;
       }
       i = 0;
    }
    break;
    //ooooooooooooo//

    case 3:
    k = 3;
  	i = 5;
  	for(h = 1; h <= iniy; h++){
  		if (h >= iniy - 5){
           for (j = inix; j<= inix +3; j++){
           	//
           	if(campo[h][j] == 'O'){
           		 campo[h][j] = 'O';
                 k--;
			   }
			   else{
                 campo[h][j] = t[k][i];
                 k--;
               }
            //
           }
           i--;
       }
       k = 3;
    }
    break;
    //ooooooooooooo//

    case 4:
   	k = 0;
  	i = 3;

    for (j = inix; j<= inix +3; j++){
        campo[iniy][j] = larg[k][i];
        i--;
        }

   break;
   //ooooooooooooo//
   }
}


//Verifica cuando una figura toca lateral o verticalmente a otra
void toca(char campo[V][H], char campop[V][H], int *rr, int *inixx, int *iniyy, int *modxx, int *finn, int *izq, int *der){
    int i = 0;
    int izqq, derr = 0;


	switch(*rr){
		case 0:
		figl(campo, campop, *rr, *inixx, iniyy, *modxx, finn, &izqq, &derr);
		break;

		case 1:
		figlarg(campo, campop, *rr, *inixx, iniyy, *modxx, finn, &izqq, &derr);
		break;

		case 2:
		figcuad(campo, campop, *rr, *inixx, iniyy, *modxx, finn, &izqq, &derr);
		break;

		case 3:
		figt(campo, campop, *rr, *inixx, iniyy, *modxx, finn, &izqq, &derr);
		break;

		default:
		figz(campo, campop, *rr, *inixx, iniyy, *modxx, finn, &izqq, &derr);
		break;
	}

	*izq = izqq;
	*der = derr;
}


//Verifica cuando una figura toca lateral o verticalmente a otra (Figura L)
void figl(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr){

	//Limites de alrededor

	//Posicion 0  ; 4*6
	int limax[14] = { inix, inix, inix, inix,    inix, inix+1, inix+2, inix+3, inix+4, inix+5,    inix+5, inix+5, inix+1, inix+1};
	int limay[14] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy, *iniy, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

    //Posicion 1 ; 4*4
    int limbx[12] = {inix+2, inix+2, inix, inix,    inix, inix+1, inix+2, inix+3,    inix+3, inix+3, inix+3, inix+3};
	int limby[12] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	//Posicion 3 ; 4*4
    int limcx[12] = {inix, inix, inix, inix,    inix, inix+1, inix+2, inix+3,    inix+1, inix+1, inix+3, inix+3};
	int limcy[12] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy-2, *iniy-2,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	//Posicion 2  ; 4*6
    int limdx[14] = {inix, inix, inix+4, inix+4,    inix, inix+1, inix+2, inix+3, inix+4, inix+5,    inix+5, inix+5, inix+5, inix+5};
	int limdy[14] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy-2, *iniy-2, *iniy-2, *iniy-2, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	int i, j, sal, sal1;
	sal = 0;
	sal1 = 0;

	//Accionar limites
	switch(modx){
		//____________________________________________//
		case 0:
		for(i = 0; i <= 13; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limay[i]][limax[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 9){
				if(campop[limay[i]+1][limax[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limay[i]][limax[i]+1] == 'O' || campop[limay[i]][limax[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//____________________________________________//

		case 1:
		for(i = 0; i <= 11; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limby[i]][limbx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 7){
				if(campop[limby[i]+1][limbx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limby[i]][limbx[i]+1] == 'O' || campop[limby[i]][limbx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   	else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//____________________________________________//

		case 2:

		for(i = 0; i <= 13; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limdy[i]][limdx[i]-1] == 'O'){
				   *izqq = 1;
				    sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 9){
				if(campop[limdy[i]+1][limdx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limdy[i]][limdx[i]+1] == 'O' || campop[limdy[i]][limdx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	     }
		}
		break;
		//____________________________________________//

		default:
		for(i = 0; i <= 11; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limcy[i]][limcx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 7){
				if(campop[limcy[i]+1][limcx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limcy[i]][limcx[i]+1] == 'O' || campop[limcy[i]][limcx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	    }
	 }
		break;
		//____________________________________________//
	}

}


//Verifica cuando esta figura toca lateral o verticalmente a otra (Figura t)
void figt(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr){
	//Posicion 0; 4*6
	int limax[14] = {inix+2, inix+2, inix, inix,    inix, inix+1, inix+2, inix+3, inix+4, inix+5,    inix+5, inix+5, inix+3, inix+3};
	int limay[14] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy, *iniy, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	//Posicion 1; 6*4
	int limbx[16] = {inix+2, inix+2, inix, inix, inix+2, inix+2,    inix, inix+1, inix+2, inix+3,    inix+3, inix+3, inix+3, inix+3, inix+3, inix+3};
	int limby[16] = {*iniy-5, *iniy-4, *iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy-2, *iniy-2, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3, *iniy-4, *iniy-5};

	//Posicion 2; 4*6
	int limcx[14] = {inix, inix, inix+2, inix+2,    inix, inix+1, inix+2, inix+3, inix+4, inix+5,    inix+3, inix+3, inix+5, inix+5};
	int limcy[14] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy-2, *iniy-2, *iniy, *iniy, *iniy-2, *iniy-2,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	//Posicion 3; 6*4
	int limdx[16] = {inix, inix, inix, inix, inix, inix,    inix, inix+1, inix+2, inix+3,    inix+1, inix+1, inix+3, inix+3, inix+1, inix+1};
	int limdy[16] = {*iniy-5, *iniy-4, *iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy-2, *iniy-2,    *iniy, *iniy-1, *iniy-2, *iniy-3, *iniy-4, *iniy-5};

	int i,j;
	int sal, sal1;
	sal = sal1 = 0;

		//Accionar limites
	switch(modx){
		//____________________________________________//
		case 0:
		for(i = 0; i <= 13; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limay[i]][limax[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 9){
				if(campop[limay[i]+1][limax[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limay[i]][limax[i]+1] == 'O' || campop[limay[i]][limax[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	     }
		}
		break;
		//____________________________________________//

		case 1:
		for(i = 0; i <= 15; i++){
			/////////////////////
			if(i <= 5 && sal == 0){
				if(campop[limby[i]][limbx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>5 && i<= 9){
				if(campop[limby[i]+1][limbx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limby[i]][limbx[i]+1] == 'O' || campop[limby[i]][limbx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//____________________________________________//

		case 2:

		for(i = 0; i <= 13; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limcy[i]][limcx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 9){
				if(campop[limcy[i]+1][limcx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limcy[i]][limcx[i]+1] == 'O' || campop[limcy[i]][limcx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//____________________________________________//

		default:
		for(i = 0; i <= 15; i++){
			/////////////////////
			if(i <= 5 && sal == 0){
				if(campop[limdy[i]][limdx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>5 && i<= 9){
				if(campop[limdy[i]+1][limdx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limdy[i]][limdx[i]+1] == 'O' || campop[limdy[i]][limdx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//____________________________________________//
	}
}


//Verifica cuando esta figura toca lateral o verticalmente a otra (Figura cuad)
void figcuad(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr){

	// limites
	int limax[12] = {inix, inix, inix, inix,    inix, inix+1, inix+2, inix+3,    inix+3, inix+3, inix+3, inix+3};
	int limay[12] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy, *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	int i, j;
	int sal,sal1;
	sal = sal1 = 0;

			for(i = 0; i <= 11; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limay[i]][limax[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 7){
				if(campop[limay[i]+1][limax[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limay[i]][limax[i]+1] == 'O' || campop[limay[i]][limax[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
}


//Verifica cuando esta figura toca lateral o verticalmente a otra (Figura larg)
void figlarg(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr){
	//caso 0 y 2
	int limax[12] = {inix, inix,    inix, inix+1, inix+2, inix+3, inix+4, inix+5, inix+6, inix+7,    inix+7, inix+7};
	int limay[12] = {*iniy-1, *iniy,    *iniy, *iniy, *iniy, *iniy, *iniy, *iniy, *iniy, *iniy,    *iniy, *iniy-1};

	//caso 1 y 2
	int limbx[10] = {inix, inix, inix, inix,    inix, inix+1,    inix+1, inix+1, inix+1, inix+1};
	int limby[10] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy, *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	int i, j;
	int sal,sal1;
	sal = sal1 = 0;


	switch(modx){
		case 0:
		case 2:
	    //_____________________________________________//

			for(i = 0; i <= 11; i++){
			/////////////////////
			if(i <= 1 && sal == 0){
				if(campop[limay[i]][limax[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				  }
				else{
					*izqq = 0;
				}
			}
			else if(i>1 && i<= 9){
				if(campop[limay[i]+1][limax[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if (sal1 == 0 ){
		   	if(campop[limay[i]][limax[i]+1] == 'O' || campop[limay[i]][limax[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//_____________________________________________//

		case 1:
		case 3:
		//_____________________________________________//

			for(i = 0; i <= 9; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limby[i]][limbx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				  }
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 5){
				if(campop[limby[i]+1][limbx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if (sal1 == 0 ){
		   	if(campop[limby[i]][limbx[i]+1] == 'O' || campop[limby[i]][limbx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	     }
		}
		break;
		//_____________________________________________//
	}
}


//Verifica cuando esta figura toca lateral o verticalmente a otra (Figura z)
void figz(char campo[V][H], char campop[V][H], int r, int inix, int *iniy, int modx, int *fin, int *izqq, int *derr){
	//caso 1 y 3
	int limax[6] = {inix,    inix, inix+1, inix+2, inix+3,    inix+3};
	int limay[6] = {*iniy,    *iniy, *iniy, *iniy, *iniy,    *iniy};

	//caso 0 y 2
	int limbx[9] = {inix, inix, inix, inix,    inix,    inix, inix, inix, inix};
	int limby[9] = {*iniy-3, *iniy-2, *iniy-1, *iniy,    *iniy,    *iniy, *iniy-1, *iniy-2, *iniy-3};

	int i,j;
	int sal, sal1;
	sal = 0;
	sal1 = 0;

	switch(modx){
		case 0:
		case 2:
	    //_____________________________________________//

			for(i = 0; i <= 8; i++){
			/////////////////////
			if(i <= 3 && sal == 0){
				if(campop[limby[i]][limbx[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>3 && i<= 4){
				if(campop[limby[i]+1][limbx[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limby[i]][limbx[i]+1] == 'O' || campop[limby[i]][limbx[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//_____________________________________________//

		case 1:
		case 3:
		//_____________________________________________//

			for(i = 0; i <= 5; i++){
			/////////////////////
			if(i == 0 && sal == 0){
				if(campop[limay[i]][limax[i]-1] == 'O'){
				   *izqq = 1;
				   sal = 1;
				}
				else{
					*izqq = 0;
				}
			}
			else if(i>0 && i<= 4){
				if(campop[limay[i]+1][limax[i]] == 'O'){
					//pare
					*fin = 1;
		            *iniy = 1;
		            for(i = 0; i<= V-1; i++){
		                for(j = 0; j <= H-1; j++){
			               campop[i][j] = campo[i][j];
	    	               }
    	             }
					//
				}
			}
		   /////////////////////
		   else{
		   	if(sal1 == 0){
		   	if(campop[limay[i]][limax[i]+1] == 'O' || campop[limay[i]][limax[i]+1] == '/'){
		   		*derr = 1;
		   		sal1 = 1;
			   }
			   else{
			   	*derr = 0;
			   }
		   }
	      }
		}
		break;
		//_____________________________________________//
	}
}


void corre(char campop[V][H], int fil){
	int i,j;

	for(i = fil; i>= 1; i--){
		for(j = 1; j<= H-2; j++){
			if(i>1){
			   campop[i][j] = campop[i-1][j];
			}
			else{
			   campop[i][j] = ' ';
			}
		}
	}
}

