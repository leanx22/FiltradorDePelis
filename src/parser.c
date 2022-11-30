/*
 * parser.c
 *
 *  Created on: 30 nov. 2022
 *      Author: leank
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "LinkedList.h"
#include "pelis.h"
#include "parser.h"

int parser_PeliDesdeTexto(FILE* pFile , LinkedList* listaPelis)
{
	int retorno = -1;


	char bufId[4];
	char bufNombre[100];
	char bufGenero[50];
	char bufDuracion[4];

	ePelicula* aux = NULL;

	if(pFile!=NULL && listaPelis!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufId,bufNombre,bufGenero,bufDuracion);
		do{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufId,bufNombre,bufGenero,bufDuracion)==4)
			{
				aux = peli_newParametros(atoi(bufId),bufNombre,bufGenero,atoi(bufDuracion));
				retorno = ll_add(listaPelis,aux);
			}

		}while(!feof(pFile));
		if(fclose(pFile)!=0)
		{
			printf("\nNo se pudo cerrar el archivo!");
			system("PAUSE");
		}
	}

    return retorno;
}
