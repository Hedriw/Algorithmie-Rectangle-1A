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
     int curr_pos; /*\< cursor represent the top of the stack*/
     cell* linkedList; /*\< The stack is represent by linked list so it's the first element of the linked list*/
 };
/**
 * \struct tuple
 * \brief Objet chaîne de caractères.
 */
struct tuple {
	int position; /*\< First value of the tuple most use for a couple of value (position,height) or (X,Y)*/
	int height; /*\< Second value of the tuple most use for a couple of value (position,height) or (X,Y)*/
};
/**
 * \struct cell
 * \brief Struct represents linked list.
 */
struct cell{
    tuple* tuple; /*\< Tuple pointer that save the couple of value from the current cell*/
    cell* next; /*\< Cell pointer of the next cell*/
};

/**
 * \fn tuple* _tuple(int position,int height);
 * \brief Constructor of tuple;
 *
 * \param position The value will be assign to the first value of the tuple.
 * \param height The value will be assign to the second value of the tuple.
 * \return A tuple pointer.
 * \prec \p position, \height can't be NULL.
 */
tuple* _tuple(int position,int height);
/**
 * \fn cell* _cell(int position,int height,cell* next);
 * \brief Constructor of cell.
 *
 * \param position The value will be assign to the first value of the tuple in the cell.
 * \param height The value will be assign to the second value of the tuple in the cell.
 * \return A cell pointer.
 * \prec \p position, \height can't be NULL.
 */
cell* _cell(int position,int height,cell* next);
/**
 * \fn void free_cell(cell* c);
 * \brief Free all allocated memory of the cell.
 *
 * \param c The cell who will be free.
 * \prec \p c can't be NULL.
 */
void free_cell(cell* c);
/**
 * \fn void AddHeadList(cell** currentList, int position,int height);
 * \brief Add a cell to the first place of the linked list.
 *
 * \param currentList The linked list that you want add an element.
 * \param position The value will be assign to the first value of the tuple in the create cell.
 * \param height The value will be assign to the second value of the tuple in the create cell.
 * \prec \p position, \height can't be NULL.
 */
void AddHeadList(cell** currentList, int position,int height);
/**
 * \fn void void DeleteHead(cell** list);
 * \brief Remove a cell to the first place of the linked list.
 *
 * \param list The linked list that you want remove the first element.
 * \prec \p position, \height can't be NULL.
 */
void DeleteHead(cell** list);
/**
 * \fn stack* _stack();
 * \brief Constructor of stack.
 *
 * \return A stack pointer.
 */
stack* _stack();
/**
 * \fn int _isEmpty(stack *stack);
 * \brief Function tell if a stack is empty or not.
 * \param stack The stack that you want to know if she empty.
 * \return Return 1 if the stack in parameters is empty, else return 0.
 */
int _isEmpty(stack *stack);
/**
 * \fn tuple _pop(stack* stack);
 * \brief Function that remove top element of the stack.
 * \param stack The stack that you want to pop the top.
 * \return Return a tuple that have been pop if the stack is not empty. Else return a default tuple (Position : 0, Height : 0).
 */
tuple _pop(stack* stack);
/**
 * \fn void _push(stack* stack, int position,int height);
 * \brief Function that add an element on top of the stack.
 * \param stack The stack that you want to push an tuple.
 * \param position The value will be assign to the first value of the tuple in the added element.
 * \param height The value will be assign to the second value of the tuple in the added element.
 */
void _push(stack* stack, int position,int height);
#endif
