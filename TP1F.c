#include <stdio.h>
#include <stdlib.h>
#include "var_array_2.h"
#include "funciones.h"

 /**
 *              TP  1
 *             =======
 *
 *     JUAN D'AMBRA  PADRON: 95159  PRACTICA: JUEVES.
 *
 * En el TP genero un archivo error.txt que dice que falla los argumentos ingresados, se genera en el mismo directorio.
 * los algoritmos para ordenar son :
 *   -bs (bubble sort)
 *   -hs (heap sort)
 *   -ls (shell sort)
 *   -qs (quick sort)
 *   -ss (selection sort)
 *   -rs (radix sort)
 *
 *  El programa devuelve EXIT_FAILURE si se ingresan mal los argumentos.
 *
 **/

int main(int argc, char **argv)
{
    int valido=validarArgs(argc,argv);
	if (valido== EXIT_FAILURE)
	{
		errorTxt(EXIT_FAILURE);
	}
	else if (valido==MENU)
        {
            menuGui();
            return EXIT_SUCCESS;
        }
	else if (valido==HELP)
        {
            help();
            return EXIT_SUCCESS;
        }
    else {
	V_Array vector;
	int a=sizeof(int);
	VA_create(&vector,a);
	leerValor(argv[3],&vector);
    ordenarVector(obtenerOrd(argv[1]),&vector);
	pasarAarchivo(argv[5],vector);
	VA_destroy(&vector);
	}
    return valido;

}
