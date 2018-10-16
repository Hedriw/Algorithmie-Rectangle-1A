/*Standard lib*/
#include <stdio.h>
#include <stdlib.h>


typedef struct stack stack;

struct stack {
    int size;
    int curr_pos;
    int *array;
};


stack* _stack(int p_size){
  stack* stack = malloc(sizeof(stack));
  stack->array = malloc(p_size*sizeof(int));
  stack->size = p_size;
  stack->curr_pos = -1;
  return stack;
}

void print_stack(stack* stack){
  if(stack!=NULL){
    printf("[ ");
    for(int i = 0;i<=stack->curr_pos;i++){
      printf("%i ",stack->array[i]);
    }
    printf("]\n");
  }
}

void resize(stack *stack,int new_size){
  int *tmp = malloc(new_size*sizeof(int));
  for(int i = 0;i<=stack->curr_pos;i++){
    tmp[i] = stack->array[i];
  }
  free(stack->array);
  stack->array = tmp;
  stack->size = new_size;
}

int push(stack* stack, int value){
  if(stack!=NULL){
    if(stack->curr_pos+1>=stack->size){
      int new_size = stack->size * 2;
      resize(stack,new_size);
    }
      stack->array[stack->curr_pos+1]=value;
      stack->curr_pos++;
  }
}

int isEmpty(stack *stack){
  if(stack!=NULL){
    if(stack->curr_pos==-1) return 0;
  }
  return 1;
}

int pop(stack* stack){
  if(!isEmpty(stack)){
    stack->array[stack->curr_pos];
  }
}

int main(int argc, char const *argv[]) {
  stack* test_stack =  _stack(10);
  for(int j =0;j<20500;j++){
    push(test_stack,j);
  }
  print_stack(test_stack);
  printf("%i",test_stack->size);
  free(test_stack);
  return 0;
}
