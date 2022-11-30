/*
 * utn.c
 *
 *  Created on: 29 abr. 2022
 *      Author: Leandro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "utn.h"

static int myGets(char* cadena, int longitud);
static int getInt(int* pResultado);
static int esNumerica(char* cadena);



static int myGets(char* cadena, int longitud)
{
	int retorno = -1;
	fflush(stdin);
	if(cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin)==cadena){
		//fflush(stdin);
		if(cadena[strlen(cadena)-1]== '\n'){
			cadena[strlen(cadena)-1] = '\0';
		}
		retorno=0;
	}

	return retorno;
}

static int esFlotante(char* cadena)
{
	int retorno = 1;
	int i = 0;

	if(cadena != NULL && strlen(cadena)>0)
	{
		while(cadena[i] != '\0')
		{
			if (cadena[i] < '0' || cadena[i] > '9')
			{
				if(cadena[i] != '.')
				{
					printf("Caracter invalido en la posicion %d !", i+1);
					retorno = 0;
					break;
				}
			}
			i++;
		}

	}

	return retorno;
}

static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[64];
	//fflush(stdin);

	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
		{
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

static int esNumerica(char* cadena)
{
	int retorno = 1;
	int i = 0;

	if(cadena != NULL && strlen(cadena)>0)
	{
		while(cadena[i] != '\0')
		{
			if (cadena[i] < '0' || cadena[i] > '9'){
				retorno = 0;
				break;
			}
			i++;
		}

	}

	return retorno;
}

int utn_pedirInt(int*pResultado,char*mensaje,char*mensajeError,int minimo,int maximo,int reintentos)
{
	int retorno =-1;
	int bufferInt;

	while (reintentos>0)
	{
		reintentos--;
		printf("\n");
		printf("%s", mensaje);
		if(getInt(&bufferInt)==0){
			if(bufferInt>=minimo && bufferInt<=maximo){
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
		}
		printf("%s", mensajeError);
	}

	return retorno;
}

int utn_getStr(char array[], char*mensaje,char*mensajeError,int tamanio,int reintentos)
{
	int retorno=-1;
	char buffer[tamanio];

	if(array != NULL && mensaje != NULL)
	{
		while(reintentos>0)
		{
			printf(mensaje);
			fflush(stdin);
			myGets(buffer, tamanio);

			for(int i=0;i<tamanio;i++)
			{
				if(buffer[i] != '\0')
				{
					if(isalpha(buffer[i]) == 0 && buffer[i] != ' ')
					{
					reintentos--;
					printf(mensajeError);
					printf("\n");
					//system("PAUSE");
					break;
					}
				}
				else
				{
					strcpy(array, buffer);
					retorno = 0;
					reintentos = 0;
					break;
				}
			}

		}
	}

	return retorno;
}

int utn_getTelefono(long*resultado, char*mensaje,char*mensajeError,int reintentos)
{
	int retorno = 0;
	char numeroTelefono[11];
	system("CLS");

	//if(*resultado != NULL && *mensaje != NULL && *mensajeError != NULL && reintentos > 0)
	//{
		while(reintentos != 0)
		{
			printf(mensaje);
			fflush(stdin);
			fgets(numeroTelefono, 11, stdin);

			if(esNumerica(numeroTelefono)!=0)
			{
				*resultado = atoi(numeroTelefono);
				retorno = 1;
				break;
			}else
			{
				printf(mensajeError);
				printf("\n");
			}
			reintentos--;
		}
	//}else{printf("\nNULL o intentos = 0!");}
	return retorno;
}

int utn_pedirFloat(float* pResultado, char* mensaje,char* mensajeError, int minimo,int maximo,int reintentos)
{
	int retorno =-1;
	float bufferResultado;
	char bufferFloat[32];

		while (reintentos>0)
		{
			printf("\n");
			printf("%s", mensaje);

			fflush(stdin);
			myGets(bufferFloat, 32);
			reintentos--;

			if(esFlotante(bufferFloat)==1)
			{
				bufferResultado = atof(bufferFloat);
				if(bufferResultado>minimo && bufferResultado<maximo)
				{
					*pResultado = bufferResultado;
					retorno = 0;
					break;
				}else{printf("\nEl numero debe ser minimo %d, y maximo: %d",minimo,maximo);}
			}else
			{
				printf("\n");
				printf(mensajeError);
				printf("\n");
				system("PAUSE");
			}
		}

		return retorno;
}

int utn_myGets(char* cadena,char*mensaje, int longitud)
{
	int retorno = -1;;
	char buffer[longitud];

	fflush(stdin);
	printf("%s",mensaje);
	if(cadena != NULL && mensaje != NULL&& longitud > 0 && fgets(buffer, longitud, stdin)==buffer){

		if(strlen(buffer)<=longitud)
		{
			if(buffer[strlen(buffer)-1]== '\n')
			{
				buffer[strlen(buffer)-1] = '\0';
			}
			strncpy(cadena,buffer,longitud);
			retorno=0;
		}
	}

	return retorno;
}

int utn_esAlfaNumerico(char str[])
{
	int retorno = -1;
	int tam;

	if(str!= NULL)
	{
		tam = strlen(str);
		for(int i=0;i<tam;i++)
		{
			if(isalpha(str[i])==0 && isdigit(str[i])==0)
			{
				retorno =-1;
				break;

			}else{
				retorno = 1;
			}
		}
	}




	return retorno;

}

///////////////////////////////////////////////////////////////////////


int utn_esNombre(char* cadena,int tamMax)
{
	int retorno = 0;
	//int tamanio = 0;

	int i=0;

	if(cadena!=NULL && strlen(cadena)<tamMax)
	{
		if(cadena[strlen(cadena)-1]=='\n')
		{
			cadena[strlen(cadena)-1]='\0';
		}

		while(cadena[i]!='\0')
		{
			if(isalpha(cadena[i])==0 && cadena[i]!=' ')
			{
				retorno = -1;
				break;
			}
			i++;
		}

	}

	return retorno;
}

int getIntComoStr(char* pResultado,char* mensaje,char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	char buffer[64];
	fflush(stdin);

	if(pResultado != NULL)
	{
		while(reintentos>0)
		{
			reintentos--;
			printf("\n%s",mensaje);

			if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer) &&
					atoi(buffer)>=minimo && atoi(buffer)<=maximo)
			{
				//*pResultado = buffer;
				strcpy(pResultado,buffer);
				retorno = 0;
				break;
			}
			printf("\n%s",mensajeError);

		}
	}
	return retorno;
}





