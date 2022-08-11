#include<stdio.h>
#include<string.h>
#include"Infix_Postfix.h"
int isValidInput(char *exp){
    int i=0;
    int cur_br_count=0;

    // we will check for valid bracket sequence
    // int flag=0;
    // int check_open_close=0;
    while(exp[i]!='\0'){
        // if(exp[i]>='0' && exp[i]<='9')
        //     flag=1;
        // if(exp[i]=='(' && exp[i-1]==')')
        //     check_open_close=1;
        if(exp[i]=='(') 
            cur_br_count++;
        else if(exp[i]==')' && cur_br_count>0)
            cur_br_count--;
        else if(exp[i]==')' && cur_br_count==0)
            return 0;
        
        i++;
    }

    if(cur_br_count!=0)
        return 0;
    // if (flag==0)
    //     return 0;
    // if (check_open_close==1)
    //     return 0;
    //  checking for valid  operation 
    i=0;
    while(exp[i]!='\0'){
        if(exp[i]!='+' && exp[i]!='-' && exp[i]!='*' && exp[i]!='/' 
        && exp[i]!='.' && exp[i]!=' ' && exp[i]<'0' && exp[i]>'9'){
            return 0;
        }
        i++;
    }

    //   checking for valid combination   of   operations and operators
    i=0;
    int operationDetected = 1;
    while(i != strlen(exp)){
        if(exp[i] >= '0' && exp[i] <= '9' && operationDetected == 1){
            while(exp[i] >= '0' && exp[i] <= '9' || exp[i] == '.') i++;
            operationDetected = 0;
            i--;
        }
        else if(exp[i] >= '0' && exp[i] <= '9' && operationDetected == 0) return 0;
        else if(exp[i] == '.');
        else if(exp[i] ==')' || exp[i] == '(');
        else if(exp[i] == ' ');
        else if(operationDetected == 1) return 0;
        else operationDetected = 1;

        i++;
    }
    return 1; // expression is valid
}









