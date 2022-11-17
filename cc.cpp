#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include "funciones.h"

using namespace std;

//DECLARACION DEL TABLERO Y PUNTERO 
char tablero[_TMATRIZ][_TMATRIZ];
struct puntero pos;

int main(int argc, char const *argv[]){
	//INICIA EL TABLERO
	for(int i=0;i<_TMATRIZ;i++){
		for(int j=0;j<_TMATRIZ;j++){
			tablero[i][j] = '#';
		}
	}
	//RELLENA EL TABLERO
	rellenarTablero(tablero);
	//LOOP INFINITO	
	do{
		//REVISA LAS COMBINACIONES
		revisarTres(tablero);
		//IMPRIME EL TABLERO
		imprimirTablero(tablero, pos);
		//MOVER PUNTERO
		moverPuntero(tablero, &pos, false);
		//LIMPIA LA PANTALLA
		system("cls");	
	}while(true);
	return 0;
}


