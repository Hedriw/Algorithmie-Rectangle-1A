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
typedef struct cell cell;

/**
 * \struct stack
 * \brief struct that represents a pile
 */
 struct stack {
     int curr_pos;
     cell* linkedList;
 };
/**
 * \struct tuple
 * \brief Objet chaîne de caractères.
 */
struct tuple {
	int position;
	int height;
};
/**
 * \struct cell
 * \brief Struct represents linked list.
 */
struct cell{
    tuple* tuple;
    cell* next;
};
tuple* _tuple(int position,int height);
int TupleSize(tuple t,int currentPosition);

cell* _cell(int position,int height,cell* next);
void free_cell(cell* c);
void AddHeadList(cell** currentList, int position,int height);
void DeleteHead(cell** list);

stack* _stack();
int _isEmpty(stack *stack);
tuple _pop(stack* stack);
void _push(stack* stack, int position,int height);

void ShowList(cell* list);
void print_stack(stack* stack);
#endif
