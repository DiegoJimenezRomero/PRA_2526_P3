#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree
{
	private:
		int nelem; 		//Numero de elementos en el arbol
		BSNode<T>* root;	//Raiz del arbol
		BSNode<T>* search(BSNode<T>* n, T e) const
		{
			//Si no hay raiz
			if(n == nullptr) throw runtime_error("No existe esa raiz");
			//Si el elemento actual es menor que el buscado voy a la derecha
			else if(n->elem < e) return search(n->right, e);
			//Si es mayor, voy a la izquierda
			else if(n->elem > e) return search(n->left, e);
			//Si no, devuelvo la raiz actual
			else return n;
		}

		//Método para insertar un elemento de manera ordenada en el ABB
		BSNode<T>* insert(BSNode<T>* n, T e)
		{
			//Si no hay raiz creo el nuevo nodo
			if(n == nullptr) return new BSNode(e);
			//Si el elemento actual es igual que el elemento a insertar lanzo una excepcion
			else if(n->elem == e) throw runtime_error("El elemento ya está en el arbol");
			//Si es menor, lo inserto a la derecha
			else if(n->elem < e) n->right = insert(n->right, e);
			//Si es mayor, lo inserto a la izquierda
			else n->left = insert(n->left, e);
			return n;
		}

		//Método para imprimir el ABB en el orden inorder
		void print_inorder(ostream &out, BSNode<T>* n) const
		{
			if(n != nullptr)
			{
				print_inorder(out, n->left);
				if(n->left != nullptr) out << " --> ";
				out << "[" << n->elem << "]";
				if(n->right != nullptr) out << " --> ";
				print_inorder(out, n->right);
			}
		}
		
		//Metodo para eliminar un elemento e de un (sub-) arbol n
		BSNode<T>* remove(BSNode<T>* n, T e)
		{
			if(n == nullptr) throw runtime_error("Elemento no encontrado");
			else if(n->elem < e) n->right = remove(n->right, e);
			else if(n->elem > e) n->left = remove(n->left, e);
			else
			{
				if(n->left != nullptr && n->right != nullptr)
				{
					n->elem = max(n->left);
					n->left = remove_max(n->left);
				}
				else n = (n->left != nullptr)? n->left: n->right;
			}
			return n;
		}

		//Metodo para encontrar el elemento mayor
		T max(BSNode<T>* n) const
		{
			if(n == nullptr) throw runtime_error("Elemento no encontrado");
			else if(n->right != nullptr) return max(n->right);
			else return n->elem;
		}

		//Metodo para eliminar el elemento mayor
		BSNode<T>* remove_max(BSNode<T>* n)
		{
			if(n->right == nullptr) return n->left;
			else
			{
				n->right = remove_max(n->right);
				return n;
			}
		}
		
		//Método recursivo para la liberación de la memoria dinámica ocupada por el ABB
		void delete_cascade(BSNode<T>* n)
		{
			if(n == nullptr) return;
			else
			{
				delete_cascade(n->left);
				delete_cascade(n->right);
				delete n;
			}
		}
	public:
		BSTree()
		{
			root = nullptr;
			nelem = 0;
		}

		//Método para devolver el número de elementos del ABB
		int size() const
		{
			return nelem;
		}

		//Método para buscar el elemento e en el ABB. Función lanzadera de search()
		T search(T e)
		{
			return search(root, e)->elem;
		}

		//Sobrecarga del operador [] para que funcione como interfaz del método search(T e)
		T operator [](T e) const
		{
			return search(e);
		}

		//Método para insertar el elemento e de manera ordenada en el ABB
		void insert(T e)
		{
			root = insert(root, e);
			nelem++;
		}

		//Sobrecarga del operador << para imprimir el ABB bst realizando un recorrido inorder
		friend ostream& operator << (ostream &out, const BSTree<T> &bst)
		{
			bst.print_inorder(out, bst.root);
			return out;
		}

		//Método para eliminar el elemento e del ABB
		void remove(T e)
		{
			root = remove(root, e);
			nelem--;
		}

		//Método destructor
		~BSTree()
		{
			delete_cascade(root);
		}
};

#endif
