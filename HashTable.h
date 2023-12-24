#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include <iostream>

#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V>{

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;

	int h(std::string key){
		int suma = 0;
		int i = 1;
		while(i <= key.length()){ //la funcion at(i) obtiene caracter en posicion i
			suma += int(key.at(i)); //convierte en ASCII
			i++;
		}
		return suma % max;
	}


    public:
        HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}

	~HashTable(){
		delete table;
	}

	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		//out<<"List =>  ["<<std::endl<<th<<std::endl<<"]";
	//	return out;
	}

	V operator[](std::string key){
		int cubeta = h(key);
		int posicion = table[cubeta].search(key);
		if(posicion >= 0){
			return table[cubeta].get(posicion).value;
		}
		else{
			throw std::runtime_error("No se ha podido encontrar la clave");
		}
	}

	void insert(std::string key, V value) override{
		int cubeta = h(key);
		int posicion = table[cubeta].search(key); //posicion dentro de la cubeta especifica
		std::cout<< "La posicion es: "<< posicion<< std::endl;

		if(table[cubeta].get(posicion).key == key){ //si la clave ya existe:error
			throw std::runtime_error("La clave ya existe");
		}
		
		else{
			table[cubeta].insert(posicion, TableEntry(key, value));
			std::ostream& operator<<(std::ostream &out, const TableEntry<V> &elem);
			n++;
		}
	}

	V search(std::string key) override{
		int cubeta = h(key);
                int posicion = table[cubeta].search(key); //esto te devuelve la posicion en la lista de nodos
                        
                if (posicion >= 0){
                	return table[cubeta].get(posicion).value; // llamas a get para que te devuelva el valor     
                }
		else{
			throw std::runtime_error("No se ha podido encontrar la clave");
                }
	}

	V remove(std::string key) override{
		int cubeta = h(key);
                int posicion = table[cubeta].search(key); //esto te devuelve la posicion en la lista de nodos

                if (posicion >= 0){
			n--;
			V valor = table[cubeta].get(posicion).value;
                        table[cubeta].remove(posicion);
			return valor;
                }
                else{
                        throw std::runtime_error("No se ha podido encontrar la clave");
                }

	}
	int entries() override{
		return n;
	}

        
};

#endif
