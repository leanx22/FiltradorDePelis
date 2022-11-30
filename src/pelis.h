/*
 * pelis.h
 *
 *  Created on: 30 nov. 2022
 *      Author: lean
 */

#ifndef PELIS_H_
#define PELIS_H_

typedef struct{
	int id;
	char titulo[100];
	char genero[50];
	int duracion;

}ePelicula;

#endif /* PELIS_H_ */

ePelicula* peli_new();

ePelicula* peli_newParametros(int id,char* nombre,char* genero,int duracion);

int peli_getId(ePelicula* this,int* id);

int peli_getTitulo(ePelicula* this,char* titulo);

int peli_getGenero(ePelicula* this,char* genero);

int peli_getDuracion(ePelicula* this,int* duracion);

/// @brief Funcion utilizada para asignar tiempo aleatorio con ll_map()
///
/// @param pElement
void peli_asignarTiempo(void* pElement);

int listarPelis(LinkedList* lista,int cls);

int peli_guardarModoTexto(LinkedList* this,char*path);

int filtrarPelis(void* pElement,char*genero);

int ordenarXgenero(void* this,void* this2);

int ordenarXDuracion(void* this,void* this2);






