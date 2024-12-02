/*
*****************************************************************************
*							Créditos: 					*
*****************************************************************************
*									Enunciado								*
*****************************************************************************
Introducir una única línea que contenga entre 2 y 10 palabras separadas por coma (,), sin espacios, y 
presentarlas en orden inverso. Las palabras tendrán un máximo de 10 letras. El número de palabras es 
desconocido, sólo sabemos que serán como mínimo 2 y como máximo 10, el programa debe adaptarse 
a lo que introduzca el usuario.
*/

/* Incluimos las bibliotecas */
#include <stdio.h>

/* Definimos algunas variables */
#define longMax 110 // Longitud máxima = 10 palabras * 10 letras + 9 comas + 1 \0
#define longMin 8 // Longitud mínima = 2 palabras * 3 letras mínimo + 1 coma + 1 \0

/* Definimos las funcines */
int comprobarInput(int *longitud); // Comprueba que la longitud de cada palabra es la adecuada
int comprobarLongitud(int longitud); 
void matrizAdd(int *longitud); // Guardamos las letras en la matriz 
void matrizOutput(int fila, int columna); // Imprime la matriz del revés

/* Definimos las variables globales */
char cadenaUser[longMax]={0};
char matrizCadena[10][11] = {{0}};
int numPalabras = 0;

int main(){
	int longitud=0; // Longitud de la cadena ingresada
	int error=0;
	
	do{	
		longitud = 0; // En caso de error se reincia la variable
		
		printf("\n[?] Introduzca una lista: "); // Input
		
		error = comprobarInput(&longitud);
		
		/* Comprueba la longitud e la cadena */
		if(((numPalabras < 2) && (error == 0))){
			error = 1;
			printf("\n[-] Error, no superas la lóngitud mínima");
		} else if(((numPalabras > 10) && (error == 0))){
			error = 1;
			printf("\n[-] Error, has  superado la longitud máxima");
		}
		
	} while(error == 1);
	
	matrizAdd(&longitud); // Guardamos las letras en la matriz y la imprimimos del revés
	
	return 0;
}

int comprobarInput(int *longitud){
	char letra = '\0';
	int posicion = 0;
	int numeroLetras = 0;
	int salida = 0;
	
	while(letra != '\n'){\
		letra = getchar();		
		numeroLetras++;	// Sumamos una letra a la longitud de la palabra
		
		if((letra == ',') || (letra == '\n')){ 
			numeroLetras--; // Evitamos que nos cuente la "," y el "\n"
		}
	
		/* Comprueba que se ha ingresado una letra y una coma*/
		if (!((letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') || (letra == ','))){	
		
			if(letra == '\n'){ // En caso de que termine la cadena
				
				salida = comprobarLongitud(numeroLetras);
				cadenaUser[posicion] = '\0';
			} else{ // En caso de error
			
				salida = 1;
				printf("\n[-] Error: Solo se permiten letras y comas.\n");
				
				while(getchar() != '\n'); // limpiamos el buffer
				break;
			}
		} else{
			
			if(letra == ','){
				if(comprobarLongitud(numeroLetras) == 1){ // Comprueba si cumple la longitud que quermos
					break;
				}
				
				numeroLetras = 0;
			}
			
			cadenaUser[posicion] = letra;
			posicion++;
			*longitud+=1;
		}
	}
	
	return salida;
}

int comprobarLongitud(int longitud){
	int salida = 0;
	
	if(longitud < 3){
		
		salida = 1;
		printf("\n[-] Error: las palabras son de mínimo 3 letras\n");
	} else if(longitud > 10){
		
		salida = 1;
		printf("\n[-] Error: las palabras son de maximo 10 letras\n");
	}
	
	numPalabras++; // Cúenta el núemro de palabras que hay
	
	return salida;
}

void matrizAdd(int *longitud){
	int fila=0, columna=0;
	
	for(int i=0; i <= *longitud; i++){
		char letra = cadenaUser[i];
		
		/* Condición si encuentra una coma */
		if(letra == ','){
			matrizCadena[fila][columna] = '\0'; // Fín de la palabra
			fila++;
			columna = 0;
		} else{
			matrizCadena[fila][columna] = letra;
			columna++;
		}
	}
	
	matrizOutput(fila, columna); // Imprimimos la matriz
}

void matrizOutput(int fila, int columna){	
	printf("\n[+] La cadena del revés es: ");
	
	for (int filaOutput = fila; filaOutput >= 0; filaOutput--) {
        for (int columna = 0; matrizCadena[filaOutput][columna] != '\0'; columna++) {
            printf("%c", matrizCadena[filaOutput][columna]);
        }
		
        if (filaOutput > 0){
			printf(","); // Agregar coma entre palabras
		}
    }
}