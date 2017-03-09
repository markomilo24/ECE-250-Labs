/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  m3milova@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - jj2park test cases used for testing components of the project
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	// deleta all
    delete [] stack_array;
    delete [] maximum_array;
    delete [] minimum_array;
}

int Dynamic_range_stack::top() const {
		//underflow check
		if (entry_count <= 0) {
        throw underflow();
    }
	// return top of stack
    return stack_array[entry_count-1];
}

int Dynamic_range_stack::maximum() const {
		//underflow check
		if (entry_count <= 0) {
        throw underflow();
    }
	// return top of max array stack
	return maximum_array[max_count-1];
}

int Dynamic_range_stack::minimum() const {
		//underflow check
		if (entry_count <= 0) {
        throw underflow();
    }
	// return top of min stack
	return minimum_array[min_count-1];
}

int Dynamic_range_stack::size() const {
	// size of array = entry stack
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
    //return true if it is empty false if not empty
	if (entry_count == 0){
		return true;
    }
    else {
	    return 0;
    }
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
	// copy over to new array if overflow occurs
    entry_count = (entry_count + 1);
    if (entry_count > current_capacity){
    	current_capacity = 2*current_capacity;
        int *stack_array_copy = new int [(current_capacity)];
        int *maximum_array_copy = new int [(current_capacity)];
        int *minimum_array_copy = new int [(current_capacity)];
        
        for (int i = 0; i < entry_count; i++){
            stack_array_copy[i] = stack_array[i];
        }
        for (int i = 0; i < max_count; i++){
            maximum_array_copy[i] = maximum_array[i];
        }
        for (int i = 0; i < min_count; i++){
            minimum_array_copy[i] = minimum_array[i];
        }

        delete [] stack_array;
        delete [] maximum_array;
        delete [] minimum_array;

        stack_array = stack_array_copy;
		maximum_array = maximum_array_copy;
		minimum_array = minimum_array_copy;

        stack_array[entry_count - 1] = obj;
        if(max_count == 0){
        	max_count++;
            maximum_array[max_count-1] = obj;
		}
        else if (obj > maximum_array[max_count-1]){
        	max_count++;
            maximum_array[max_count-1] = obj;
			
        }
        if(min_count == 0){
        	min_count++;
            minimum_array[min_count - 1] = obj;
		}
        else if (obj <  minimum_array[min_count -1]){
        	min_count++;
            minimum_array[min_count - 1] = obj;
        }
    }
    // if no overflow, push normally
    else {
        stack_array[entry_count - 1] = obj;
        if(max_count == 0){
        	max_count++;
            maximum_array[max_count-1] = obj;
		}
        else if (obj > maximum_array[max_count-1]){
        	max_count++;
            maximum_array[max_count-1] = obj;
			
        }
        if(min_count == 0){
        	min_count++;
            minimum_array[min_count - 1] = obj;
		}
        else if (obj <  minimum_array[min_count -1]){
        	min_count++;
            minimum_array[min_count - 1] = obj;
        }
    }
}

int Dynamic_range_stack::pop() {
	//check for underflow error
	if (entry_count <= 0) {
        throw underflow();
    }
	// make temporary variable to check if the stack array top = the min/max array tops so you can push both if necessary
    int entry_count_helper = stack_array[entry_count-1];
	entry_count = (entry_count - 1);

    if (entry_count_helper == maximum_array[max_count-1]){
            max_count = (max_count - 1);
    }

    if (entry_count_helper == minimum_array[min_count-1]){
            min_count = (min_count - 1);
    }

    return entry_count_helper;
}

void Dynamic_range_stack::clear() {
	// CLear all variables, delete arrays, initialize new ones
    delete [] stack_array;
    delete [] maximum_array;
    delete [] minimum_array;
    int *stack_array_new = new int [current_capacity];
    int *maximum_array_new = new int [current_capacity];
    int *minimum_array_new = new int [current_capacity];
    stack_array = stack_array_new;
	maximum_array = maximum_array_new;
	minimum_array = minimum_array_new;
    current_capacity = initial_capacity;
    entry_count = 0;
    max_count = 0;
    min_count = 0;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
