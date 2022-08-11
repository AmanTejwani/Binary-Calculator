#include<stdio.h>
#include<stdlib.h>
#define PLUS 1
#define MINUS -1
#define EQUAL 0
#define NUMBER1  1
#define NUMBER2 2

typedef struct child_node{
    struct child_node* prev;
    struct child_node* next;
    int digit;
}child_node;
typedef struct child_node* CHILD_NODE;

typedef struct parent_list{
    struct child_node* head;
    struct child_node* tail;
    int sign; //sign of number

}parent_list;
typedef struct parent_list* PARENT_LIST;

void init_parent(PARENT_LIST *a){
    (*a) = (PARENT_LIST)malloc(sizeof(parent_list));
    (*a)->sign = PLUS;
    (*a)->head = NULL;

    (*a)->tail = NULL;

    return;
}

void append(PARENT_LIST a, char ch){
    if( (a)->head == NULL){
        CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
        newchild_node->prev = NULL;
        newchild_node->next = NULL;
        newchild_node->digit = ch - '0';
        (a)->head = newchild_node;
        (a)->tail = newchild_node;

    }
    else{
        child_node* newchild_node = (child_node*)malloc(sizeof(child_node));
        newchild_node->next = NULL;
        newchild_node->digit = ch - '0';
        newchild_node->prev = (a)->tail;
        (a)->tail->next = newchild_node;
        (a)->tail = newchild_node;

    }
}

int length_of_parent(PARENT_LIST a){
    int len = 0;
    CHILD_NODE ptr = (a)->head;
    while(ptr != NULL){
        len++;
        ptr = ptr->next;
    }
    return len;
}

void appendLeft(PARENT_LIST num_list, int digit){
    CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
    newchild_node->prev = NULL;
    newchild_node->next = NULL;
    newchild_node->digit = digit;
    if((num_list->head) == NULL){
        num_list->head = newchild_node;
        num_list->tail = newchild_node;
    }
    else{
        newchild_node->next = num_list->head;
        num_list->head->prev = newchild_node;
        num_list->head = newchild_node;
    }
}

void zero_at_end(PARENT_LIST a, int n){// adds n zeroes at end of number
    if( (a)->head == NULL ) {// if number was never initialized
        CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
        newchild_node->next = NULL;
         newchild_node->prev = NULL;
        (a)->head = newchild_node;
        (a)->tail = newchild_node;
        }
    while(n-- >0){
        CHILD_NODE newchild_node = (CHILD_NODE)malloc(sizeof(child_node));
        newchild_node->digit = 0;
        newchild_node->next = NULL;
        newchild_node->prev = (a)->tail;
        (a)->tail->next = newchild_node;
        (a)->tail = newchild_node;
    }
}

void zero_at_start(PARENT_LIST num_list, int n){
    while (n-->0)
    {
        appendLeft(num_list, 0);
    }

}

void make_equal_length(PARENT_LIST num1, PARENT_LIST num2){


    int num1Len = length_of_parent(num1);
    int num2Len = length_of_parent(num2);
    if(num1Len > num2Len) zero_at_start(num2, (num1Len - num2Len));
    else if(num2Len > num1Len) zero_at_start(num1, (num2Len - num1Len));
}

void rem_ext_zero(PARENT_LIST num_list){
    CHILD_NODE a = num_list->head;
    if(a == NULL) return;
    while(a !=NULL && a->digit == 0 ){
        a = a->next;
    }
    num_list->head = a;
    if(a== NULL ) num_list->head = NULL;
    if(num_list->head != NULL)num_list->head->prev = NULL;
    if(length_of_parent(num_list) == 0) append(num_list, '0');
}


//    returns  1  if num1 is greater and returns 2 if  num2  is greater   and returns   0  if both of the numbers are equal.   
int getBiggerNumber(PARENT_LIST num1, PARENT_LIST num2){
    rem_ext_zero(num1);
    rem_ext_zero(num2);
    make_equal_length(num1, num2);
    CHILD_NODE ptr1 = num1->head;
    CHILD_NODE ptr2 = num2->head;
    while(ptr1!=NULL){
        if(ptr1->digit != ptr2->digit){
            if(ptr1->digit > ptr2->digit) return NUMBER1;
            else return NUMBER2;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return EQUAL;
}

void printNumber(PARENT_LIST a){
    if(a == NULL) {
        printf("%s", "number is null");
        return;
    }
    if(a->head == NULL ) {
        printf("%s", "Number has no head");
        return;
    }
    rem_ext_zero(a);
    CHILD_NODE ptr = (a)->head;
    if(a->sign == MINUS) printf("%c", '-');
    if(ptr == NULL) {
        //printf("%d", 0);
        return;
    }
    while(ptr != NULL) {
        printf("%d", ptr->digit);
        ptr = ptr->next;
    }
}

void makeEachDigitLessThanTen(PARENT_LIST num1){
    CHILD_NODE ptr1 = num1->tail;
    int carry = 0;
    while(ptr1->prev != NULL){
        if(ptr1->digit > 9){
            carry = (ptr1->digit) / 10;
            ptr1->prev->digit += carry;
            ptr1->digit = (ptr1->digit) % 10;
        }
        ptr1 = ptr1->prev;
        carry = 0;
    }
    ptr1->digit += carry;
    if(ptr1->digit > 9){
        appendLeft(num1, (ptr1->digit) / 10);
        ptr1->digit = (ptr1->digit)  % 10;
    }
}

int isZero(PARENT_LIST num1){
    rem_ext_zero(num1);
    CHILD_NODE ptr = num1->head;
    while(ptr != NULL){
        if(ptr->digit > 0) return 0;
        ptr = ptr->next;
    }
    return 1;
}


