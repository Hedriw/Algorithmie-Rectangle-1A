/**
 * \file structures.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all functions and definitions for the structs used in the program.
 */

#ifndef STRUCT_HEADER_FILE
#define STRUCT_HEADER_FILE

typedef struct tuple tuple;
typedef struct stack stack;

/**
 * \struct stack
 * \brief struct that represents a pile
 */
struct stack {
    int size;
    int curr_pos;
    tuple *array;
};

/**
 * \struct tuple
 * \brief Objet chaîne de caractères.
 */
struct tuple {
	int position;
	int height;
};

tuple _tuple(int position,int height);
stack* _stack(int p_size);
void resize(stack *stack,int new_size);
int _isEmpty(stack *stack);
tuple _pop(stack* stack);
int _push(stack* stack, int position,int height);
int TupleSize(tuple t,int currentPosition);
void print_stack(stack* stack);

#endif
