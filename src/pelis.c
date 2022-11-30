/*
 * pelis.c
 *
 *  Created on: 30 nov. 2022
 *      Author: lean
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "LinkedList.h"
#include "pelis.h"
#include <string.h>
#include <time.h>

ePelicula* peli_new()
{
	return (ePelicula*)malloc(sizeof(ePelicula));
}

ePelicula* peli_newParametros(int id,char* nombre,char* genero,int duracion)
{
	ePelicula* aux = NULL;
	aux = peli_new();
	if(aux!=NULL)
	{
		aux->id = id;
		strcpy(aux->titulo,nombre);
		strcpy(aux->genero,genero);
		aux->duracion=duracion;
	}
	return aux;
}

int peli_getId(ePelicula* this,int* id)
{
	int retorno = -1;

	if(this!=NULL && id!=NULL)
	{
		*id=this->id;
		retorno = 0;
	}
	return retorno;
}

int peli_getTitulo(ePelicula* this,char* titulo)
{
	int retorno = -1;

	if(this!=NULL && titulo!=NULL)
	{
		strcpy(titulo,this->titulo);
		retorno = 0;
	}

	return retorno;
}

int peli_getGenero(ePelicula* this,char* genero)
{
	int retorno = -1;

	if(this!=NULL && genero!=NULL)
	{
		strcpy(genero,this->genero);
		retorno = 0;
	}

	return retorno;

}

int peli_getDuracion(ePelicula* this,int* duracion)
{
	int retorno = -1;

	if(this!=NULL && duracion!=NULL)
	{
		*duracion = this->duracion;
		retorno = 0;
	}

	return retorno;

}

void peli_asignarTiempo(void* pElement)
{
	if(pElement!=NULL)
	{
	((ePelicula*)pElement)->duracion=(rand() % (240 - 100)) + 100;
	}

}

int listarPelis(LinkedList* lista,int cls)
{
	int retorno = -1;
	int tam;

	int auxid;
	int id;
	char nombre[100];
	char genero[30];
	int duracion;

	ePelicula* aux = NULL;


	if(lista!=NULL)
	{
		if(cls==1){
			system("CLS");
		}
		printf("\n| ID |     TITULO COMPLETO     |            GENERO            |  DURACION  |");
		printf("\n----------------------------------------------------------------------------");
		tam = ll_len(lista);
		for(int i=0;i<tam;i++)
		{
			aux=ll_get(lista,i);
			peli_getId(aux,&id);
			peli_getTitulo(aux,nombre);
			peli_getGenero(aux,genero);
			peli_getDuracion(aux,&duracion);
			if(auxid!=id && id!=0)
			{
				printf("\n|%4d|%-25s|%-30s|%12d|",id,nombre,genero,duracion);
			}
			auxid=id;
		}
		retorno = 0;
	}

	return retorno;
}

int peli_guardarModoTexto(LinkedList* this,char*path)
{
	int retorno = -1;
	int tam;
	FILE* archivo=NULL;
	ePelicula* aux = NULL;

	int id;
	char titulo[100];
	char genero[50];
	int duracion;

	if(this!=NULL && path!=NULL)
	{
		archivo=fopen(path,"w");
		if(archivo!=NULL)
		{
			tam=ll_len(this);
			fprintf(archivo,"id_peli,titulo,genero,duracion\n");
			for(int i=0;i<tam;i++)
			{
				aux=ll_get(this,i);
				if(aux!=NULL)
				{
					peli_getId(aux,&id);
					peli_getTitulo(aux,titulo);
					peli_getGenero(aux,genero);
					peli_getDuracion(aux,&duracion);

					fprintf(archivo,"%d,%s,%s,%d\n",id,titulo,genero,duracion);
				}
			}
			fclose(archivo);
			retorno=0;
		}
	}


	    return retorno;
}

int filtrarPelis(void* pElement,char*genero)
{
	int retorno=-1;
	if(pElement!=NULL){
		retorno = 0;
		if(strcmp(((ePelicula*)pElement)->genero,genero)==0){
			retorno = 1;
		}
	}

	return retorno;
}

int ordenarXgenero(void* this,void* this2)
{
	int retorno = 0;
	ePelicula* j1;
	ePelicula* j2;

	char genero[50];
	char genero2[50];

	j1=(ePelicula*)this;
	j2=(ePelicula*)this2;

	peli_getGenero(j1,genero);
	peli_getGenero(j2,genero2);

	if(this!=NULL && this2!=NULL)
	{
		if(strcmp(genero,genero2)>0)
		{
			retorno = 1;
		}else{
			retorno = -1;
		}
	}
	return retorno;
}

int ordenarXDuracion(void* this,void* this2)
{
	int retorno = 0;
	ePelicula* j1;
	ePelicula* j2;

	int duracion;
	int duracion2;
	char genero[50];
	char genero2[50];

	j1=(ePelicula*)this;
	j2=(ePelicula*)this2;

	peli_getGenero(j1,genero);
	peli_getGenero(j2,genero2);

	peli_getDuracion(j1,&duracion);
	peli_getDuracion(j2,&duracion2);

	if(this!=NULL && this2!=NULL)
	{
		if(strcmp(genero,genero2)==0)
		{
			if(duracion<duracion2)
			{
				retorno = 1;
			}else{
				retorno = -1;
			}
		}
	}
	return retorno;
}


