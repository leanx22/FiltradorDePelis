//Guia Leandro 2do Parcial
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "LinkedList.h"
#include "pelis.h"
#include "parser.h"
#include <time.h>

#define PATH "movies.csv"

int main(void) {
	setbuf(stdout,NULL);

	int opcion;
	int continuar=1;

	LinkedList* listaPelis = ll_newLinkedList();
	FILE* pFile = NULL;
	LinkedList* listaAux = NULL;

	int flag3=0;
	int flag5=0;

	do{
		system("CLS");
		if(utn_pedirInt(&opcion,"\nMENU:\n1.Cargar archivos.\n2.Imprimir Lista.\n3.Asignar tiempos.\n4.Filtrar por tipos."
		    			"\n5.Mostrar duraciones\n6.Guardar peliculas.\n7.Salir.\n>Ingrese una opcion: ","\nError, reintente.",1,11,99)==0)
		{

			switch(opcion)
			{
			case 1:
				pFile=fopen("movies.csv","r");
				if(pFile != NULL && parser_PeliDesdeTexto(pFile,listaPelis)==0)
				{
					printf("\nArchivo cargado OK!\n");
				}else{
					printf("\nError al cargar archivo!");
				}system("PAUSE");
				break;
			case 2:
				if(ll_isEmpty(listaPelis)==0)
				{
					listarPelis(listaPelis,1);
				}else{
					printf("\nNo se puede imprimir una lista vacia!.");
				}
				printf("\n");
				system("PAUSE");
				break;
			case 3:
				if(ll_isEmpty(listaPelis)==0)
				{
					srand(time(NULL));
					ll_map(listaPelis,peli_asignarTiempo);
					printf("\nTiempos OK\n");
					flag3=1;
				}else{
					printf("\nSe necesita cargar el archivo primero!.\n");
				}system("PAUSE");
				break;
			case 4:
				if(ll_isEmpty(listaPelis)==0)
				{
					listaAux = ll_filter(listaPelis,filtrarPelis);
					if(ll_isEmpty(listaAux)==0)
					{
						peli_guardarModoTexto(listaAux,"listaFiltrada.csv");
						printf("\nGuardado OK!");
					}else{
						printf("\nLista vacia!.");
					}
				}else{
					printf("\nSe necesita cargar el archivo primero!\n");
				}
				system("PAUSE");
				break;
			case 5:
				if(flag3==1&&ll_sort(listaPelis,ordenarXgenero,1)==0 && ll_sort(listaPelis,ordenarXDuracion,1)==0)
				{
					listarPelis(listaPelis,1);
					flag5=1;
				}else{
					printf("\nError de ordenamiento, se necesita cargar el archivo o SETEAR LOS TIEMPOS antes!.");
				}
				printf("\n");
				system("PAUSE");
				break;
			case 6:
				if(flag5==1 && peli_guardarModoTexto(listaPelis,"case6PelisOrdenadas.csv")==0)
				{
					printf("\nGuardado OK!\n");
				}else{
					printf("\nError de guardado, se debe entrar al case 5 primero.\n");
				}system("PAUSE");
				break;
			case 7:
				continuar = 0;
				break;
			}


		}





	}while(continuar==1);

	return 0;
}
