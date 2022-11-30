#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* puntero;
    puntero = NULL;
    puntero = (LinkedList*)malloc(sizeof(LinkedList));
    if(puntero != NULL)
    {
    	puntero->pFirstNode = NULL;
    	puntero->size=0;
    }
    return puntero;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int retorno = -1;
    if(this != NULL)
    {
    	retorno = this->size;
    }

    return retorno;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* retorno = NULL;
	if(this !=NULL && nodeIndex >=0 && nodeIndex<ll_len(this))
	{
		retorno = this ->pFirstNode;

		for(int i=0;i<nodeIndex;i++)//nodeIndex-1?
		{
			retorno = retorno->pNextNode;
		}
	}
	return retorno;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{

	int retorno = -1;
		Node* aux = NULL;
		Node* paux=NULL;
		Node* aNewNode = NULL;

		if(this != NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
		{
			aux = (Node*)malloc(sizeof(Node));
			if(aux != NULL)
			{
				aNewNode = aux;
				//inicializo el nuevo nodo.
				aNewNode->pElement = pElement;
				aNewNode->pNextNode=NULL; //Null ya que no se si hay siguiente nodo

				aux=NULL;//reinicio aux para no crear otra variable.

				if(nodeIndex==0)
				{
					aNewNode->pNextNode=this->pFirstNode;
					this->pFirstNode=aNewNode;
				}
				else
				{
				//aux toma la dir del nodo anterior.
				aux = getNode(this,nodeIndex-1);

				//guardo la direccion de memoria del siguiente nodo en paux.
				paux=aux->pNextNode;

				//swap
				aux->pNextNode = aNewNode; //El anterior nodo apunta al nuevo
				aNewNode->pNextNode = paux;//el nuevo nodo apunta al siguiente.
				}

				this->size++;//aumento el size
				retorno = 0;
			}

		}

		return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this !=NULL)
    {
    	if(addNode(this,ll_len(this),pElement)==0)
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodoAux = NULL;
    if(this != NULL && index>=0 && index<=ll_len(this))
    {
    	nodoAux = getNode(this,index);
    	if(nodoAux!=NULL)
    	{
    		returnAux=nodoAux->pElement;
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)//pisa
{
    int returnAux = -1;
    Node* pAux = NULL;
    if(this != NULL && index>=0 && index<ll_len(this))
    {
    	pAux=getNode(this,index); //se podra usar ll_get para directamente tener el elemento?
    	if(pAux != NULL)
    	{
    		pAux->pElement=pElement;
    		returnAux = 0;
    	}//necesito hacer un free del anterior elemento
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista //CORRECCION: nodo!
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* prevNode = NULL;
    Node* actualNode = NULL;

    if(this != NULL && index >= 0 && index<ll_len(this)) //es < porque el indice es el tamanio -1
    {

    	actualNode = getNode(this,index);

    	if(index == 0)
    	{
    		this->pFirstNode = actualNode->pNextNode;
    	}
    	else
    	{
    		prevNode = getNode(this,index-1);
    		if(prevNode != NULL)
    		{
    			prevNode->pNextNode = actualNode->pNextNode;
    		}
    	}
    	free(actualNode);
    	this->size--;
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len=0;

    if(this != NULL)
    {
    	len = ll_len(this)-1;
    	for(int i=len;i>=0;i--) //recorro de atras para adelante para no perder las referencias.
    	{
    		ll_remove(this,i);
    	}
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* auxElement=NULL;
    if(this != NULL)//no valido elemento por null, por si se quiere buscar un nodo con elemento null.
    {
    	for(int i=0;i<ll_len(this);i++)
    	{
    		auxElement = ll_get(this,i);
    		if(pElement==auxElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}

    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_len(this))
    	{
    		returnAux=0;
    	}
    	else
    	{
    		returnAux=1;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)//desplaza
{
    int returnAux = -1;

    if(this != NULL&&index>=0&&index<=ll_len(this))//<=ll_len() ya que tal vez quiera pushear un elemento al final, entre el ultimo nodo y la "nada"
    {
    	returnAux = addNode(this,index,pElement);
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this != NULL&&index>=0&&index<ll_len(this))
    {
    	returnAux = ll_get(this,index);
    	ll_remove(this,index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_indexOf(this,pElement)!=-1)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* eAux=NULL;
    if(this!=NULL&&this2!=NULL)
    {
    	returnAux = 1;
    	for(int i=0;i<ll_len(this2);i++)
    	{
    		eAux = ll_get(this2,i);
    		if(!(ll_contains(this,eAux)))
    		{
    			returnAux = 0;
    			break;
    		}
    	}
    }


    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* auxElement = NULL;
    if(this != NULL && from>=0 && to<=ll_len(this) && to>from)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
		{
    		for(int i = from; i<to; i++)
    		{
    			auxElement = ll_get(this,i);
    			ll_add(cloneArray,auxElement);
    		}
		}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL)
    {
    	//cloneArray = ll_newLinkedList();
    	cloneArray = ll_subList(this,0,ll_len(this));//ll_len()-1se aplica automatico en ll_sublist

    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* auxFirstElement;
    void* auxSecondElement;

    if(this != NULL && pFunc!=NULL && order>=0 && order<=1)
    {
    	returnAux = 0;

    	for(int i=0;i<ll_len(this)-1;i++)
    	{
    		for(int j=i+1;j<ll_len(this);j++)
    		{
    			auxFirstElement = ll_get(this,i);
    			auxSecondElement = ll_get(this,j);
    			if(pFunc(auxFirstElement,auxSecondElement)>0&&order==1)
    			{
    				ll_set(this,i,auxSecondElement);
    				ll_set(this,j,auxFirstElement);
    			}
    			else if(pFunc(auxFirstElement,auxSecondElement)<0&&order==0)
    			{
    				ll_set(this,i,auxSecondElement);
    				ll_set(this,j,auxFirstElement);
    			}

    		}
    	}
    }
    return returnAux;
}

int ll_map(LinkedList*this, void(*fn)(void* element))
{
	int returnAux = -1;

	if(this != NULL && fn != NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			//le paso cada elemento con ll_get().
			fn(ll_get(this,i));
		}
		returnAux = 0;
	}

	return returnAux;
}

LinkedList* ll_filter(LinkedList* this,int(*fn)(void*,char*))
{
	LinkedList*newList = NULL;
	void* auxElement = NULL;
	char genero[50];
	if(this != NULL && fn != NULL)
	{
		newList = ll_newLinkedList();
		if(newList!=NULL && utn_getStr(genero,"Ingrese el genero deseado (Ojo con mayuscula y minuscula): ","Error, reintente.",50,3)==0)
		{
			for(int i=0;i<ll_len(this);i++)
			{
				auxElement = ll_get(this,i);
				if(fn(auxElement,genero)==1)
				{
					ll_add(newList,auxElement);
				}
			}
		}

	}

	return newList;
}
