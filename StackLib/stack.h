#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <typeinfo>
#include <ctype.h>
#include <conio.h>
#include "stack_config.h"

//using data_type = double;

class Stack
{
private:
	int canary_left_;

    data_type* data_       		; //= nullptr;
    const char* name_    	; //= nullptr;
    size_t capacity_    		; //= 0;         //max size
    size_t cur_size_ 	 		; //= 0;         //size now
    int hash_        		; //= 0;
	int error_state_		;

    int canary_right_;

int   verify();
int   calc_hash();
char* error_print(int bit_of_error);


public:

	 Stack(const char* name = "Default", size_t capacity = 0);
	 ~Stack();

void push(data_type push_num);
data_type  pop();

//! GETTERS

size_t get_cur_size() {return cur_size_;};
size_t get_capacity() {return capacity_;};
data_type get_data_num(size_t number) {return data_[number];};
int		  get_error_state() {return error_state_;};
const char*	  get_name() {return name_;};

//! SETTERS
// * They should not be (you can only use push, pop)
//! OTHER

void dump();


};

auto get_byte(int digit, int number_of_bit) -> bool;


#endif
