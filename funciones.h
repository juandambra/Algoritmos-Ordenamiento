
#include <stdio.h>

#include "var_array_2.h"


#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#define MENU 4
#define HELP 5
#define MAXARCH 50
#define ERROR_ORDEN 7


//valida los argumentos segun el formato especificado

int validarArgs(int numArg,char** args);

/**
 * obtiene el ordenamiento y devuelve un numero del 1 al 6 segun el tipo
 *
 **/

int obtenerOrd(char* orden);

/**
 *
 * Crea un archivo de salida.txt e imprime en el todo lo que se encuentra en el
 * vector.
 *
 **/

int pasarAarchivo(char* salida,V_Array vec);

/**
 *
 * compara dos numeros, retornando 1 si el primero es mayor y 0 si es lo contrario
 **/

int cmp(void *numero1, void *numero2);


/**
 * lee los valores del archivo y los pasa a un vector
 **/

int leerValor(char* nombre , V_Array* varray);

//swapea los ints pos1 y pos 2

int swap(V_Array* varray,int pos1, int pos2);

//funcion que pasa el error a un texto

int errorTxt(int error);

int selectionSort(V_Array* varray,funccmp pcomp);

int shellSort(V_Array* varray);

int radixsort(V_Array *a, int n);

int heapSort(V_Array *varray);

int heapify(V_Array* varray,int count);

int siftDown(V_Array* varray,int start,int end);

//interfaz grafica para los ordenamientos

void menuGui();

void titulo();

//ayuda

void help();

//ordena el vector segun el tipo de ordenacion utilizado

int ordenarVector(int ord,V_Array* vect);


#endif
