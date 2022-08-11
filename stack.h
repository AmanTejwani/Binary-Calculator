#include<stdio.h>
#include<stdlib.h>
#include"Operations.h"
// #include"PARENT_LIST.h"

typedef struct stackNode{
    struct stackNode* next;
    PARENT_LIST number;
}stackNode;
typedef struct stackNode* STACKNODE;

typedef struct stack{
    int size;
    struct stackNode* top;
}stack;
typedef struct stack* STACK;

void init_stack(STACK *stack){
    (*stack) = (STACK)malloc(sizeof(stack));
    (*stack)->size = 1000;
    (*stack)->top = NULL;
}

int getStackSize(STACK stack){
    STACKNODE ptr = stack->top;
    int size = 0;
    while(ptr != NULL){
        size++;
        ptr = ptr->next;
    }
    return size;
}

int isEmpty(STACK stack){
    if(stack->top == NULL) return 1;
    else return 0;
}

int isFull(STACK stack){
    if(getStackSize(stack) == stack->size) return 1;
    else return 0;
}

void push(STACK stack, PARENT_LIST num_list ){
    if(isFull(stack) == 1) {
        printf("%s", "Yo have exceed");
        return;
    }
    else if(isEmpty(stack) == 1){
        STACKNODE new_stack_node = (STACKNODE)malloc(sizeof(stackNode));
        new_stack_node->next = NULL;
        new_stack_node->number = num_list;
        (stack)->top = new_stack_node;
        return;
    }
    else {
        STACKNODE new_stack_node = (STACKNODE)malloc(sizeof(stackNode));
        new_stack_node->next = (stack)->top;
        new_stack_node->number = num_list;
        (stack)->top = new_stack_node;
        return;
    }
}

void pop(STACK stack){
    if(isEmpty(stack)) return;
    if(stack->top->next == NULL) {
        stack->top = NULL;
        return;
    }
    stack->top = stack->top->next;
    return;
}

STACKNODE peek(STACK stack){
    if(isEmpty(stack)) return NULL;
    return stack->top;
}


