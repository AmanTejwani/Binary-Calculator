#include<stdio.h>
#include"TakingInput.h"

int main(){
    printf("\n \n");
    printf("------------------||Aman Tejwani , 112003146  &&   Pradnyesh Utpat , 112003147  ||--------------\n\n");
    printf("The operations that can be performed are '+' '-' '/' '*'.\n");
    printf("This calculator will run only once.\nEnter your expression now: \n");

    char userInput[2000];
    gets(userInput);

    char* inputInfix = userInput;

    if(isValidInput(inputInfix) == 0){
        printf("---------CHECK INPUT EXPRESSION-------------");
        return 0;
    }
    printf("-------------------------------------------------------------\n\n");
    STACK stack;
    init_stack(&stack);
    stack = getPostfixStack(inputInfix);
    PARENT_LIST solution = evaluatePostfixStack(stack);
    printNumber(solution);
    printf("\n\n");
    printf("--------------------------------------------------------------------------------------------");

    return 0;
}



