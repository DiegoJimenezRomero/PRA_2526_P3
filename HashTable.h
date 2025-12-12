#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

using namespace std;

#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V>
{
	private:
		int n; //Elementos en la tabla
		int max; //Máximo de elementos en la tabla
		ListLinked<TableEntry<V>>* table; //Tabla
		int h(string key) //Método para convertir la clave en un valor numérico
		{
			int result = 0;
			for(int i = 0; i < key.size(); i++)
			{
				result += int(key.at(i));
			}
			int pos = result % max;
			return pos;
		}
	public:
		//Metodo constructor
		HashTable(int size)
		{
			//Se crea la tabla como un array de ListedLinked con valores TableEntry
			table = new ListLinked<TableEntry<V>>[size];
			//Cantidad de elementos inicial 0
			n = 0;
			//Cantidad máxima de elementos el tamaño de la tabla
			max = size;
		}

		//Método destructor
		~HashTable()
		{
			delete[] table;
		}

		//Método para saber la capacidad de la tabla
		int capacity()
		{
			return max;
		}
		
		//Sobrecarga del operador << para imprimir el contenido de la tabla hash
		friend ostream& operator <<(ostream &out, const HashTable<V> &th)
		{
			out << "Tabla Hash [Elementos guardados = "; 
			out << th.n;
			out <<	", Capacidad = "; 
			out << th.max;
			out << "]";
			out << "\n==========\n";
			for(int i = 0; i < th.max; i++)
			{
				out << "==Cubeta ";
			       	out << i; 
				out <<	"==\n";
				out << "\n"; 
				out <<	th.table[i]; 
				out <<	"\n";
				}
				out << "\n==========";
				return out;
			}

		//Sobrecarga del operador [] para que imprima el contenido guardado en la clave especificada
		V operator[](string key)
		{
			int position = h(key);
			if(position >= max) throw runtime_error("Posicion erronea");
			//Llamo a la función search para saber el valor que tiene la clave
			return search(key);
		}
	
		//Metodos heredados
		
		//Método para insertar una nueva entrada en la tabla
		void insert(string key, V value) override
		{
			//Creo la entrada a insertar (Variable de tipo TableEntry con clave key y valor value)
			TableEntry<V> newEntry = TableEntry<V>(key, value);
			//Guardo la posición del array en la que debe ir
			int position = h(key);
			if(position >= max) throw runtime_error("Posición fuera de rango");
			//Para saber si la clave ya se encuentra en la lista, utilizo la función search() de la clase ListedLinked y si no se encuentra añado el elemento al final
			int search = table[position].search(newEntry);
			//Si no está (la función search() devuelve -1 si no se encuentra nada)
			if(search == -1)
			{
				table[position].prepend(newEntry);
				n++;
			}
			else throw runtime_error("La clave ya está en la tabla");
		}
	
		//Método para buscar una entrada en la tabla
		V search(string key) override
		{
			TableEntry<V> searchedEntry = TableEntry<V>(key);
			int position = h(key);
			if(position >= max) throw runtime_error("Posición fuera de rango");
			{
				//Utilizo la función search() de la clase ListedLinked para buscar en la cubeta la clave proporcionada
				int key_position = table[position].search(searchedEntry);
				//Devuelvo el valor adecuado (el valor que tiene la clave si se ha encontrado o -1 si no se ha encontrado)
				if(key_position == -1) throw runtime_error("La clave no se encuentra en la tabla");
				else return table[position][key_position].value;
			}
		}

		//Método para eliminar un valor de la tabla
		V remove(string key) override
		{
			//Creo una entrada auxiliar para buscar la clave en la cubeta
			TableEntry<V> auxiliarEntry = TableEntry<V>(key);
			//Guardo la cubeta de la clave
			int position = h(key);
			if(position >= max) throw runtime_error("Posición fuera de rango");
			//Busco la posición de la clave dentro de la cubeta
			int key_position = table[position].search(auxiliarEntry);
			//Si no se encuentra se lanza un error y si se encuentra se elimina
			if(key_position == -1) throw runtime_error("Esa llave no se encuentra en la tabla");
			else
			{
				n--;
				return table[position].remove(key_position).value;
			}
		}

		//Método para saber la cantidad de elementos que tiene guardada la tabla
		int entries() override
		{
			return n;
		}
};

#endif
