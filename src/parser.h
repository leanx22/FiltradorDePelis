/*
 * parser.h
 *
 *  Created on: 30 nov. 2022
 *      Author: leank
 */

#ifndef PARSER_H_
#define PARSER_H_
#endif /* PARSER_H_ */

/// @brief Funcion parser para leer el archivo desde el csv.
///
/// @param pFile ruta del archivo.
/// @param listaPelis lista de peliculas.
/// @return retorna -1 en caso de error o 0 si OK
int parser_PeliDesdeTexto(FILE* pFile , LinkedList* listaPelis);
