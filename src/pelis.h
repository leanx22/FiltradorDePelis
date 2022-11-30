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

//CONSTRUCTORES
ePelicula* peli_new();
ePelicula* peli_newParametros(int id,char* nombre,char* genero,int duracion);

//GETTERS
int peli_getId(ePelicula* this,int* id);
int peli_getTitulo(ePelicula* this,char* titulo);
int peli_getGenero(ePelicula* this,char* genero);
int peli_getDuracion(ePelicula* this,int* duracion);
/*//////////////////////////////////////////////////////////////////////////////////////*/

/// @brief Funcion utilizada para asignar duracion aleatoria con ll_map()
///
/// @param pElement
void peli_asignarTiempo(void* pElement);

/// @brief Funcion que lista las peliculas en formato tabla.
///
/// @param lista
/// @param cls
/// @return retorna -1 error o 0 OK
int listarPelis(LinkedList* lista,int cls);

/// @brief Funcion que guarda la lista de peliculas en formato csv
///
/// @param this lista
/// @param path ruta del archivo
/// @return 0 si OK o -1 en caso de error.
int peli_guardarModoTexto(LinkedList* this,char*path);

int filtrarPelis(void* pElement,char*genero);

/// @brief funcion usada en ll_sort()
///
/// @param this
/// @param this2
/// @return
int ordenarXgenero(void* this,void* this2);

/// @brief  funcion usada en ll_sort()
///
/// @param this
/// @param this2
/// @return
int ordenarXDuracion(void* this,void* this2);






