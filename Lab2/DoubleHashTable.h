#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  m3milova
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// delete both arrays
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    // size of the array
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // how much array can hold
	return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    //if array is empty, return true, if not return false
    if (count == 0){
    	return true;
	}
	else{
	return false;
	}
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// hash function one, for initial key 
	int key1 = static_cast<int> (obj);
	key1 = key1%array_size;
	if (key1 < 0){
		key1 = key1 + array_size;
	}
	return key1;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// hash function 2, used to calculate offset
	int key2 = static_cast<int> (obj);
	key2 = (key2/array_size)%array_size;
	if(key2 < 0){
		key2 = key2 + array_size;
	}
	if(key2%2 == 0){
		key2 = key2 + 1;
	}
	return key2;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// enter your implemetation here 
	int probe;
	int offset;
	
	probe = h1(obj);
	offset = h2(obj);
	// if the array at index probe is occupied and equal to obj return true, if not probe rest of array using offset, return true if it is found
	if(array[probe] == obj && array_state[probe] == OCCUPIED){
		return true;
	}
	else{
		for (int i = 0; i < array_size; i++){
			probe = ((probe + offset) % array_size);		
			if(array_state[(probe)] == OCCUPIED){
				if(array[probe] == obj){
					return true;
				}
			}
		}
	}
	//if not a member of the table, return false
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // value in the array at n	      
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {

	int probe;
	int offset;
	
	probe = h1(obj);
	offset = h2(obj);
	//if hash table does not have enough room, throw overflow
	if (count >= array_size){
		throw overflow();
	}
	//increment count
	count = (count + 1);
	//find the next available place for obj using the hash functions, if it is empty, break from loop
	for (int i = 0; i < array_size; i++){
		if(array_state[probe] == EMPTY){
			break;
		}
		
		if(array_state[probe] == OCCUPIED){
			probe = ((probe + offset) % array_size);
		}	
	}
	//std::cout << array_state[probe] << " " << array[probe] << " " << probe << std::endl;
	//set array_state to occupied and array to hold obj, both at index of the probe (either probe or just probe+offset, determined by for loop)
	array[probe] = obj;
	array_state[probe] = OCCUPIED;
	//std::cout << array_state[probe] << " " << array[probe] << " " << probe << std::endl;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	// enter your implemetation here 	
	int probe;
	int offset;
	
	probe = h1(obj);
	offset = h2(obj);
	
	if ((count - 1) < 0){
		return false;
	}
		//find the obj in the array, "remove it" by setting status to deleted and decrement count by 1
		//return true once deleted
		for (int i = 0; i < array_size; i++ ){
			if (array[probe] == obj && array_state[probe] == OCCUPIED){
				//std::cout << array_state[probe] << " " << array[probe] << " " << probe << std::endl;
				array_state[probe] = DELETED;
				//std::cout << "deleted" << std::endl;
				count = (count - 1);
				return true;
			}
			probe = ((probe + offset) % array_size);
		}
	//return false if nothing has been deleted since obj is not in the hash table
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	// set all states to empty
	for (int i = 0; i < array_size; i++){
		array_state[i] = EMPTY;
		array[i] = 0;
	}
	
	count = 0; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here 	
	return;
}

#endif
