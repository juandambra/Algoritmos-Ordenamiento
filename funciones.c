#include "funciones.h"
#include "var_array_2.h"
#include <string.h>

void titulo()
{
    printf("\033[2J");
    printf("PROGRAMA DE ORDENAMIENTO\n");
    printf("========================\n\n");
}

int validarArch(char* archEntr)
{
    FILE* arch;
    if ((arch=fopen(archEntr,"r"))==NULL)
    {
        printf("Archivo inexistente,  ingrese uno nuevo.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void help()
{
    printf("\nLista de comandos:\n");
    printf("gui                       interfaz grafica\n");
    printf("-alg -i [archivo de entrada] -o [archivo de salida]\n");
    printf("\nalg es el algoritmo de ordenamiento utilizado, puede ser:\n");
    printf("\nqs                      QuickSort");
    printf("\nbs                      Bubble Sort");
    printf("\nss                      Selection Sort");
    printf("\nls                      Shell Sort");
    printf("\nhs                      Heap Sort\n");
    printf("\nrs                      Radix Sort\n");
}

void menuGui()
{
    char archEntr[MAXARCH], archSal[MAXARCH];
    int ord;
    int valido=EXIT_FAILURE;
    titulo();
    while (valido==EXIT_FAILURE)
    {

        printf("Ingrese archivo a ordenar: ");
        scanf("%s",archEntr);
        valido=validarArch(archEntr);
    }
    titulo();
    printf("Ingrese el tipo de ordenacion segun su numero:\n 1. Quicksort\n 2. Bubble sort\n 3. Selection sort\n 4. Shell sort\n 5. Heap sort \n 6. Radix sort\n\n");
    printf("Ordenacion: ");
    scanf("%d",&ord);
    titulo();
    printf("Ingrese archivo de salida: ");
    scanf("%s",archSal);
    titulo();
    V_Array vector;
	int a=sizeof(int);
	VA_create(&vector,a);
	leerValor(archEntr,&vector);
    ordenarVector(ord,&vector);
    pasarAarchivo(archSal,vector);
    VA_destroy(&vector);
}


int validarArgs(int numArg,char** args)
{
    if ((numArg == 2) && (strcmp(args[1],"gui")==0))
        return MENU;
    if ((numArg == 2) && ((strcmp(args[1],"-h")==0)||(strcmp(args[1],"--help")==0)))
        return HELP;
	if (numArg != 6)
		return EXIT_FAILURE;
	if (obtenerOrd(args[1])==ERROR_ORDEN)
		return EXIT_FAILURE;
	if (strcmp(args[2],"-i"))
		return EXIT_FAILURE;
	if (strcmp(args[4],"-o"))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;

}

int errorTxt(int error)
{
    if (error == EXIT_FAILURE)
        {
            FILE *error;
            error=fopen("error.txt","w");
            fprintf(error,"Error en el paso de argumentos, revisar.\n");
            fprintf(error,"Recuerde que debe respetar el formato de -(algoritmo de ordenacion) -i [archivo de entrada] -o (archivo de salida)");
        }
    return EXIT_SUCCESS;
}
int pasarAarchivo(char* salida,V_Array vec)
	{
		FILE *archivo;
		archivo=fopen(salida,"w");
		int contador=0;
		int numDeValores=VA_count(vec);
		while(contador<=numDeValores-1)
			{
				int valor;
				VA_get_i(vec,contador,&valor);
				fprintf(archivo,"%d\n",valor);
				contador+=1;
			}
		fclose(archivo);
	return EXIT_SUCCESS;
	}


int cmp(void *numero1, void *numero2)
    {
        int *a = (int*)numero1, *b =(int*)numero2;
        if (*a>*b)
            {return 1;}
        else
            {return 0;}
    }

int obtenerOrd(char* orden)
{
	if (strcmp(orden,"-qs")==0)
		return 1;   //Quicksort
	if (strcmp(orden,"-bs")==0)
		return 2;                        //Bubble sort
	if (strcmp(orden,"-ss")==0)
		return 3;                  //Selection sort
	if (strcmp(orden,"-ls")==0)
		return 4;                            //Shell sort
	if (strcmp(orden,"-hs")==0)
		return 5;                             //Heap sort
    if (strcmp(orden,"-rs")==0)
		return 6;
	return ERROR_ORDEN;
}

int ordenarVector(int ord,V_Array* vect)
{
	funccmp pcomp = cmp;
    switch (ord)
    {
        case 1:
            VA_qsort(vect,pcomp,0,VA_count(*vect)-1);
            break;
        case 2:
            VA_sort(vect,pcomp);
            break;
        case 3:
            selectionSort(vect,pcomp);
            break;
        case 4:
            shellSort(vect);
            break;
        case 5:
            heapSort(vect);
            break;
        case 6:
            radixsort(vect,VA_count(*vect));
            break;
    }

	return EXIT_SUCCESS;

}

int leerValor(char* nombre, V_Array* varray)
{
	FILE *arch;
	arch=fopen(nombre,"rw+");
	char string[11];
    int pnum;
    fscanf(arch,"%s",string);
    while (!feof(arch))
    {
        pnum=atoi(string);
        VA_add(varray,&pnum);
        fscanf(arch,"%s",string);
    }
	fclose(arch);
	return EXIT_SUCCESS;

}


int radixsort(V_Array *a, int n) {
  int i, numva, keysnum, m = 0, exp = 1;
  const int base = 10;
  int *b = (int*) malloc(n * sizeof(int));
  int *bucket = (int*) calloc(base, sizeof(int));

  //Get the greatest value in the array a and assign it to m
  for (i = 1; i < n; i++) {
    VA_get_i(*a,i,&numva);
    if (numva > m)
      m = numva;
  }

  //Loop until exp is bigger than the largest number
  while (m / exp > 0) {
    memset(bucket, 0, base * sizeof(int));

    //Count the number of keys that will go into each bucket
    for (i = 0; i < n; i++) {
        VA_get_i(*a,i,&keysnum);
      bucket[(keysnum / exp) % base]++;
    }

    //Add the count of the previous buckets to acquire the indexes after the end of each bucket location in the array
    for (i = 1; i < base; i++) {
      bucket[i] += bucket[i - 1]; //similar to count sort algorithm i.e. c[i]=c[i]+c[i-1];
    }

    //Starting at the end of the list, get the index corresponding to the a[i]'s key, decrement it, and use it to place a[i] into array b.
    for (i = n - 1; i >= 0; i--) {
    VA_get_i(*a,i,&numva);
      b[--bucket[(numva / exp) % base]] = numva;
    }

    //Copy array b to array a
    for (i = 0; i < n; i++) {
    VA_set(a,i,&b[i]);
    }

    //Multiply exp by the BASE to get the next group of keys
    exp *= base;

    #ifdef SHOWPASS
      printf("\nPASS   : ");
      print(a, n);
    #endif
  }

  free(bucket);
  free(b);
  return EXIT_SUCCESS;
}


int selectionSort(V_Array* varray,funccmp pcomp)
{
	int elem, elem2 , swap , elem3 , d , c , n , posicion;
	n=VA_count(*varray);
	for ( c = 0 ; c < ( n - 1 ) ; c++ )
	   {
		  posicion = c;
		  for ( d = c + 1 ; d < n ; d++ )
		  {
			 VA_get_i(*varray,posicion,&elem);
			 VA_get_i(*varray,d,&elem2);
			 if (pcomp(&elem,&elem2))
				posicion = d;
		  }
		  if ( posicion != c )
		  {
			 VA_get_i(*varray,posicion,&elem);
			 VA_get_i(*varray,c,&elem3);
			 swap = elem3;
			 elem3 = elem;
			 elem = swap;
			 VA_set(varray,posicion,&elem);
			 VA_set(varray,c,&elem3);
		  }
	   }

	return EXIT_SUCCESS;
}

int swap(V_Array* varray,int pos1, int pos2)
{
	int swap1,swap2;
	VA_get_i(*varray,pos1,&swap1);
    VA_get_i(*varray,pos2,&swap2);
    VA_set(varray,pos1,&swap2);
    VA_set(varray,pos2,&swap1);
    return EXIT_SUCCESS;
}

int heapSort(V_Array *varray)
{
	int count = VA_count(*varray);
	heapify(varray, count);
	int end = count - 1;
	while (end > 0)
	{
		swap(varray,end,0);
		end -= 1 ;
		siftDown(varray, 0, end);
    }
	return EXIT_SUCCESS;
}

int heapify(V_Array *varray,int count)
{
	int start = (count - 2) / 2;

	while (start >= 0)
	{
      siftDown(varray, start, count-1);
      start = start - 1;
	}
	return EXIT_SUCCESS;
}

int siftDown(V_Array* varray,int start,int end)
{
	int root = start;
	int child = (root * 2) + 1;;

	while (((root * 2) + 1) <= end)
	{

		int child1, child2, root2;
		VA_get_i(*varray,child,&child1);
		VA_get_i(*varray,child+1,&child2);
		VA_get_i(*varray,root,&root2);
		if ((child + 1 < end) && (child1 < child2))
			child += 1;
        VA_get_i(*varray,child,&child1);
		if (root2 < child1)
		{
			swap(varray,root, child);
			root = child;
        }
        else
            root=end;

	}
	return EXIT_SUCCESS;
}

int shellSort(V_Array* varray)

{

    int gap, i, j, n, temp1, temp2;

    n = VA_count(*varray);
    gap = n/2;
    while (gap>0)
    {
        for (i = gap; i < n; i++)
        {
            j= i - gap;
            VA_get_i(*varray,j,&temp1);
            VA_get_i(*varray,j+gap,&temp2);
            while (j>=0 && temp1>temp2)
            {
                swap(varray,j,j+gap);
                j-=gap;
                VA_get_i(*varray,j,&temp1);
                VA_get_i(*varray,j+gap,&temp2);
            }
        }
    gap /= 2;
    if (gap== 2)
        gap =1;
    }
    return EXIT_SUCCESS;
}
