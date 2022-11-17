#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

//DECLARACION DEL TAMAÑO DE LA MATRIZ
#define _TMATRIZ 5
//DECLARACION DE LAS FUNCIONES
void imprimirTablero(char tablero[][_TMATRIZ], struct puntero pos);
void rellenarTablero(char tablero[][_TMATRIZ]);
void moverPuntero(char tablero[][_TMATRIZ], struct puntero *pos, bool enter);
void revisarTres(char tablero[][_TMATRIZ]);
//MATRIZ DE COMBINACION
char combi[3] = {0,0,0};
//CONTADOR DE COMBINACION
int combinacion = 0;

//ESTRUCTURA DEL PUNTERO
struct puntero{
	//POSICIONES DEL PUNTERO
	unsigned int posX,posY,preposX,preposY;	
};

//FUNCION QUE IMPRIME EL TABLERO
void imprimirTablero(char tablero[][_TMATRIZ], struct puntero pos){
	//RECORRE E IMPRIME EL TABLERO Y EL PUNTERO
	for(int i=0; i < _TMATRIZ; i++){
		for(int j=0; j < _TMATRIZ; j++){						
			//MARCA LA POSICION DEL PUNTERO
			if(i == pos.posY && j == pos.posX){
				cout<<"["<<tablero[i][j]<<"] ";	
			}
			//IMPRIME UNA CASILLA DE LA TABLA
			else{
				cout<<tablero[i][j]<<"   ";	
			}
		}	
		cout<<"\n \n";			
	}
}

//FUNCION PARA RELLENAR EL TABLERO
void rellenarTablero(char tablero[][_TMATRIZ]){
	//RESETEA LA SEMILLA PARA UN NUMERO RANDOM CON EL TIEMPO DEL SISTEMA
	srand(time(NULL));
	
	//RECORRE LA MATRIZ Y LA RELLENA
	for(int i=0; i < _TMATRIZ; i++){
		for(int j=0; j < _TMATRIZ; j++){
			//GENERA UN NUMERO ALEATORIO ENTRE 1 - 4
			switch(rand() % 4 + 1){
				case 1:
					//VERIFICA SI LA POSICION ESTA VACIA
					if(tablero[i][j] == '#'){
						tablero[i][j] = 'S';	
					}
				break;
				case 2:
					//VERIFICA SI LA POSICION ESTA VACIA
					if(tablero[i][j] == '#'){
						tablero[i][j] = 'X';
					}
				break;
				case 3:
					//VERIFICA SI LA POSICION ESTA VACIA
					if(tablero[i][j] == '#'){
						tablero[i][j] = 'P';
					}
				break;
				case 4:
					//VERIFICA SI LA POSICION ESTA VACIA
					if(tablero[i][j] == '#'){
						tablero[i][j] = 'O';
					}
				break;
			}
		}			
	}
}

//FUNCION QUE MUEVE EL PUNTERO
void moverPuntero(char tablero[][_TMATRIZ], struct puntero *pos, bool enter){
	//PAUSA
	system("pause");
	//TECLA ARRIBA
	if(GetAsyncKeyState(VK_UP) & 0x0001){
		//MUEVE EL PUNTERO HACIA ARRIBA
		if(pos->posY != 0){
		(pos->posY)--;
		}
	}
	//TECLA ABAJO
	if(GetAsyncKeyState(VK_DOWN) & 0x0001){
		//MUEVE EL PUNTERO HACIA ABAJO
		if(pos->posY != (_TMATRIZ - 1)){
		(pos->posY)++;
		}
	}
	//TECLA IZQ
	if(GetAsyncKeyState(VK_LEFT) & 0x0001){
		//MUEVE EL PUNTERO HACIA LA IZQUIERDA
		if(pos->posX != 0){
		(pos->posX)--;
		}
	}
	//TECLA DER
	if(GetAsyncKeyState(VK_RIGHT) & 0x0001){
		//MUEVE EL PUNTERO HACIA LA DERECHA
		if(pos->posX != (_TMATRIZ - 1)){
		(pos->posX)++;
		}
	}
	//TECLA ENTER / INTERCAMBIA DE LUGAR LOS ELEMENTOS
	if(GetAsyncKeyState(VK_RETURN) & 0x0001 && enter == false){
		//GUARDA EL VALOR DEL ELEMENTO SELECCIONADO
		char primerValor = tablero[pos->posY][pos->posX];
		//GUARDA LA POSICION DEL PRIMER ELEMENTO SELECCIONADO
		char *primerPos  = &tablero[pos->posY][pos->posX];
		(pos->preposY) = pos->posY;
		(pos->preposX) = pos->posX;
		//DEJA AL USUARIO MOVER EL PUNTERO
		moverPuntero(tablero, pos, true);
		//GUARDA EL VALOR DE LA SEGUNDA POSICION EN LA PRIMERA
		*primerPos = tablero[pos->posY][pos->posX];
		//GUARDA EL VALOR DE LA PRIMERA POSICION EN LA SEGUNDA
		tablero[pos->posY][pos->posX] = primerValor;
		revisarTres(tablero);
		if(combinacion == 0){
			tablero[pos->posY][pos->posX] = *primerPos;
			pos->posY = pos->preposY;
			pos->posX = pos->preposX;
			tablero[pos->posY][pos->posX] = primerValor;
		}
	}
	if(GetAsyncKeyState(VK_ESCAPE) & 0x0001 && enter == false){
		cout<<"\n        ********************* \n"<<"        * GRACIAS POR JUGAR * \n"<<"        ********************* \n";
		exit(0);
	}
}

//FUNCION QUE REVISA LAS COMBINACIONES
void revisarTres(char tablero[][_TMATRIZ]){
	combinacion = 0;
	for(int i=0;i<_TMATRIZ;i++){
		for(int j=0;j<_TMATRIZ;j++){
			combi[2] = combi[1];
			combi[1] = combi[0];
			combi[0] = tablero[i][j];
			if(combi[2] == combi[1] && combi[0] == combi[1]){
				//VERIFICA SI NO ESTA EN LA CIMA DEL TABLERO
				if(i != 0){
					//MUEVE TODAS LAS COLUMNAS DE LA COMBINACION HACIA ABAJO
					while(i>0){
						//REVISA SI HUBO OTRA COMBINACION ARRIBA
						if(tablero[i-1][j] != '#'){
							tablero[i][j]   = tablero[i-1][j];
							tablero[i][j-1] = tablero[i-1][j-1];
							tablero[i][j-2] = tablero[i-1][j-2];	
							i--;
						}
						else{
							i--;
						}	
					}
					//DEJA VACIO LA FILA SUPERIOR DEL TABLERO EN LAS CASILLAS DONDE SE HIZO LA COMBINACION		
					tablero[i][j]   = '#';
					tablero[i][j-1] = '#';
					tablero[i][j-2] = '#';
				}
				else{
					//DEJA VACIO LA FILA SUPERIOR DEL TABLERO EN LAS CASILLAS DONDE SE HIZO LA COMBINACION
					tablero[i][j]   = '#';
					tablero[i][j-1] = '#';
					tablero[i][j-2] = '#';
				}		
				//HUBO COMBINACION
				combinacion++;
			}
		}
		//RESETEA LA MATRIZ
		combi[1] = 0;
		combi[0] = 0;
		//RELLENA EL TABLERO
		rellenarTablero(tablero);
	}
}
