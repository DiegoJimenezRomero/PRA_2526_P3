#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template<typename V>
class BSTreeDict: public Dict<V>
{
	private:
		//ABB usado para gestionar los elementos del diccionario
		BSTree<TableEntry<V>>* tree;

	public:
		//Métodos propios

		//Constructor
		BSTreeDict()
		{
			tree = new BSTree<TableEntry<V>>();
		}

		//Destructor
		~BSTreeDict()
		{
			delete tree;
		}

		//Sobrecarga del operador << para imprimir el contenido del diccionario
		friend ostream& operator <<(ostream &out, const BSTreeDict<V> &bs)
		{
			out << *(bs.tree);
			return out;
		}

		//Sobrecarga del operador [] para imprimir el elemento que se encuentra en la entrada especificada
		V operator[](string key)
		{
			return search(key);
		}

		//Métodos heredados
		
		//Metodo para insertar el par key->value en el diccionario
		void insert(string key, V value) override
		{
			//Se crea el par key->value en un puntero a un objeto de tipo TableEntry para poder introducirlo en el diccionario
			TableEntry<V> To_insert = TableEntry<V>(key, value);
			//Se inserta el par en el arbol haciendo uso del método insert creado en BSTree.h
			tree->insert(To_insert);
		}

		//Método para buscar el vlaor correspondiente al key especificado en el diccionario.
		V search(string key) override
		{
			//Se crea un par sin valor para buscar la clave en el diccionario
			TableEntry<V> To_search = TableEntry<V>(key);
			//Se busca en el diccionario el par key->value haciendo uso del método search creado en BSTree.h
			return tree->search(To_search).value;
		}

		//Método para eliminar el par key->value del diccionario
		V remove(string key) override
		{
			//Se crea un valor para almacenar el valor a eliminar
			V result = search(key);
			//Se crea un par sin valor para buscar la clave en el diccionario
			TableEntry<V> To_eliminate = TableEntry<V>(key);
			//Se elmina el par key->value haciendo uso del método remove creado en BSTree.h
			tree->remove(To_eliminate);
			//Se devuelve el valor que estaba almacenado
			return result;
		}

		//Método para devolver el número de elementos del diccionario
		int entries() override
		{
			return tree->size();
		}
};

#endif
