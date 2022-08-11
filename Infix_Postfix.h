#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"

//mapping + operation to int = -1;
//mapping - operation to int = -2;
//mapping * operation to int = -3;
//mapping / operation to int = -4;
//mapping ( operation to int = -5;
//mapping ) operation to int = -6;
//mapping ^ operation to int = -7;

PARENT_LIST resultOfOperation(int a, PARENT_LIST num1, PARENT_LIST num2){
    PARENT_LIST result;
    init_parent(&result);
    if(a == -1) result = addNumbers(num1, num2);
    else if(a == -2) result = subNumbers(num2, num1);
    else if(a == -3) result = multiplyNumbers(num1, num2);
    else if(a == -4) result = divideNumbers(num2, num1);
    else if(a == -7) result = getExponent(num2, num1);
    return result;
}

int precedence(char chr){
    if(chr == '+' || chr == '-') return 1;
    else if(chr == '*' || chr == '/') return 5;
    else if(chr == '^') return 9;
}

char associativity(char a){
     char b;
     if(a == '+' || a=='-'){
         b = 'L';
     }
     else if( (a)== '*' || (a)=='/'){
         b =  'L';
     }
     else if((a) == '^'){
        b = 'R';
     }
     return b;
}

char mapping(int digit){
    if(digit == -1) return '+';
    else if(digit == -2) return '-';
    else if(digit == -3) return '*';
    else if(digit == -4) return '/';
    else if(digit == -5) return '(';
    else if(digit == -6) return ')';
    else if(digit == -7) return '^';
}

int reverseMapping(char a){
    if(a == '+') return -1;
    else if(a == '-') return -2;
    else if(a == '*') return -3;
    else if(a == '/') return -4;
    else if(a == '(') return -5;
    else if(a == ')') return -6;
    else if(a == '^') return -7;
}


STACK getPostfixStack(char* infixExpr){
    STACK final_stack;
    STACK intermediate_stack;
    STACK reversed_final_stack;
    init_stack(&final_stack);
    init_stack(&intermediate_stack);
    init_stack(&reversed_final_stack);
    int i = 0;
    while(i < strlen(infixExpr)){
        // everytime this creates linked list of numbers 
        if(infixExpr[i] >= '0' && infixExpr[i] <='9'){
            PARENT_LIST new_parent_list;
            init_parent(&new_parent_list);
            while(infixExpr[i] >= '0' && infixExpr[i] <='9'){
                append(new_parent_list, infixExpr[i]);
                i++;
            }
            i--;
            push(final_stack, new_parent_list);
        }

        //   it passes if we encountered an empty space 
        else if(infixExpr[i] == ' ');

        //isEmpty(intermediate_stack) == 1    is true initially
        else if(isEmpty(intermediate_stack) == 1 || peek(intermediate_stack)->number->head->digit == reverseMapping('(')) {
                PARENT_LIST new_parent_list;
                init_parent(&new_parent_list);
                CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
                newchild_node->next = NULL;
                newchild_node->digit = reverseMapping(infixExpr[i]);
                new_parent_list->head = newchild_node;
                new_parent_list->tail = newchild_node;
                push(intermediate_stack, new_parent_list);
            }
        else if(infixExpr[i] == '('){
            PARENT_LIST new_parent_list;
            init_parent(&new_parent_list);
            CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
            newchild_node->next = NULL;
            newchild_node->digit = reverseMapping('(');
            new_parent_list->head = newchild_node;
            new_parent_list->tail = newchild_node;
            push(intermediate_stack, new_parent_list);
            }
        else if(infixExpr[i] == ')'){
            while(peek(intermediate_stack)->number->head->digit != reverseMapping('(')){
                    push(final_stack , (peek(intermediate_stack))->number);
                    pop(intermediate_stack);
                }
                pop(intermediate_stack);
            }

            //   here wee are storing    value in our   newchild_node->digit   which is the associativity precedence  value 
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit)) < precedence(infixExpr[i])){
            PARENT_LIST new_parent_list;
            init_parent(&new_parent_list);
            CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
            newchild_node->digit = reverseMapping(infixExpr[i]);
            newchild_node->next = NULL;
            new_parent_list->head = newchild_node;
            new_parent_list->tail = newchild_node;
            push(intermediate_stack, new_parent_list);
        }

        //   here if associativity prcedence  is smaller then   our  element in the stack joins the final_stack and the value is then poped out from our expression 
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit)) > precedence(infixExpr[i])){
            push(final_stack, peek(intermediate_stack)->number);
            pop(intermediate_stack);
            i--;
        }

        // here if associativity prcedence  is equal  then   our  element in the stack joins the final_stack and the value is then poped out from our expression
        // and then current element is pushed into  intermediate_stack
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit))== precedence(infixExpr[i])){
            PARENT_LIST new_parent_list;
            init_parent(&new_parent_list);
            CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
            newchild_node->digit = reverseMapping(infixExpr[i]);
            newchild_node->next = NULL;
            newchild_node->prev = NULL;
            if(associativity(infixExpr[i]) == 'L'){
                push(final_stack, (peek(intermediate_stack))->number);
                pop(intermediate_stack);
                new_parent_list->head = newchild_node;
                new_parent_list->tail = newchild_node;
                push(intermediate_stack, new_parent_list);
            }
            else if(associativity(infixExpr[i])== 'R'){
                push(intermediate_stack, new_parent_list);
            }
        }
        i++;
    }

    while(isEmpty(intermediate_stack) == 0){
         push(final_stack, peek(intermediate_stack)->number);
         pop(intermediate_stack);
     }

    while(isEmpty(final_stack) == 0){
        push(reversed_final_stack, peek(final_stack)->number);
        pop(final_stack);
    }

    return reversed_final_stack;
}

void printStack(STACK stack){
    stackNode* ptr = stack->top;
    while(ptr!=NULL){
        if(ptr->number->head->digit >= 0)
            printNumber(ptr->number);
        else printf("%c", mapping(ptr->number->head->digit));
        printf("%c", ' ');
        ptr = ptr->next;
    }
}

PARENT_LIST evaluatePostfixStack(STACK postfix_stack){
    STACK ans_stack;
    init_stack(&ans_stack);
    while(isEmpty(postfix_stack) == 0){
        if(peek(postfix_stack)->number->head->digit < 0){
            PARENT_LIST result;
            init_parent(&result);
            PARENT_LIST num_list1;
            init_parent(&num_list1);
            PARENT_LIST num_list2;
            init_parent(&num_list2);
            num_list1 = peek(ans_stack)->number;
            pop(ans_stack);
            num_list2 = peek(ans_stack)->number;
            pop(ans_stack);
            result = resultOfOperation(peek(postfix_stack)->number->head->digit, num_list1, num_list2);
            push(ans_stack, result);
            pop(postfix_stack);
        }
        else{
            push(ans_stack, peek(postfix_stack)->number);
            pop(postfix_stack);
        }
    }
    return ans_stack->top->number;
}



