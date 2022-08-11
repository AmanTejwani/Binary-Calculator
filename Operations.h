#include<stdio.h>
#include"List.h"

//get difference of two number lists
// num1 - num2
PARENT_LIST subNumbers(PARENT_LIST num1 , PARENT_LIST num2 ){
    rem_ext_zero(num1);
    rem_ext_zero(num2);
    make_equal_length(num1, num2);
    PARENT_LIST difference;
    init_parent(&difference);
//    if(num1->len_dec >= num2->len_dec) difference->len_dec = num1->len_dec;
//    else difference->len_dec = num2->len_dec;
    if(num1->sign == num2->sign){//numbers have same sign
        if(num1->sign == PLUS){// both have + sign
              if(getBiggerNumber(num1, num2) == NUMBER1){
                  CHILD_NODE ptr1 = num1->tail;
                  CHILD_NODE ptr2 = num2->tail;
                  while(ptr1 !=NULL){
                      if(ptr1->digit >= ptr2->digit){
                          appendLeft(difference, (ptr1->digit)-(ptr2->digit));
                      }
                      else{
                          ptr1->prev->digit--;
                          ptr1->digit += 10;
                          appendLeft(difference, (ptr1->digit)-(ptr2->digit));
                      }
                      ptr1 = ptr1->prev;
                      ptr2 = ptr2->prev;
                  }
                  return difference;
              }
              else if(getBiggerNumber(num1, num2) == NUMBER2){
                    CHILD_NODE ptr2 = num2->tail;
                    CHILD_NODE ptr1 = num1->tail;
                    while(ptr2 != NULL){
                        if(ptr2->digit >= ptr1->digit){
                            appendLeft(difference, ptr2->digit - ptr1->digit);
                        }
                        else{
                            ptr2->prev->digit--;
                            ptr2->digit += 10;
                            appendLeft(difference, ptr2->digit - ptr1->digit);
                        }
                        ptr1 = ptr1->prev;
                        ptr2 = ptr2->prev;
                    }
                    difference->sign = MINUS;
                    return difference;
              }
              else if(getBiggerNumber(num1, num2) == EQUAL){
                  appendLeft(difference , 0);
                  return difference;
              }
        }
        else if(num1->sign == MINUS){// both have - sign
            if(getBiggerNumber(num1, num2) == NUMBER1){
                CHILD_NODE ptr1 = num1->tail;
                CHILD_NODE ptr2 = num2->tail;
                while(ptr1!= NULL){
                    if(ptr1->digit >= ptr2->digit){
                        appendLeft(difference, ptr1->digit - ptr2->digit);
                    }
                    else{
                        ptr1->prev->digit--;
                        ptr1->digit+=10;
                        appendLeft(difference, ptr1->digit - ptr2->digit);
                    }
                  ptr1 = ptr1->prev;
                  ptr2 = ptr2->prev;
                }
                difference->sign = MINUS;
                return difference;
            }
            else if(getBiggerNumber(num1, num2) == NUMBER2){
                CHILD_NODE ptr1 = num1->tail;
                CHILD_NODE ptr2 = num2->tail;
                while(ptr2!= NULL){
                    if(ptr2->digit >= ptr1->digit){
                        appendLeft(difference, ptr2->digit - ptr1->digit);
                    }
                    else{
                        ptr2->prev->digit--;
                        ptr2->digit+=10;
                        appendLeft(difference, ptr2->digit - ptr1->digit);
                    }
                    ptr1 = ptr1->prev;
                    ptr2 = ptr2->prev;
                }
                return difference;
            }
            else if(getBiggerNumber(num1, num2) == EQUAL){
                appendLeft(difference, 0);
                return(difference);
            }
        }
    }
    else if(num1->sign == MINUS){
        CHILD_NODE ptr1 = num1->tail;
        CHILD_NODE ptr2 = num2->tail;
        int carry = 0;
            while(ptr1!=NULL){
                appendLeft(difference, (carry + ptr1->digit + ptr2->digit)%10);
                carry = (carry + ptr1->digit + ptr2->digit)/10;
                ptr1 = ptr1->prev;
                ptr2 = ptr2->prev;
            }
            difference->sign = MINUS;
            return difference;
    }
    else{
        CHILD_NODE ptr1 = num1->tail;
        CHILD_NODE ptr2 = num2->tail;
        int carry = 0;
            while(ptr1!=NULL){
                appendLeft(difference, (carry + ptr1->digit + ptr2->digit)%10);
                carry = (carry + ptr1->digit + ptr2->digit)/10;
                ptr1 = ptr1->prev;
                ptr2 = ptr2->prev;
            }
            difference->sign = PLUS;
            return difference;
    }
}

//get sum of two number lists
PARENT_LIST addNumbers(PARENT_LIST num1 , PARENT_LIST num2){
    rem_ext_zero(num1);
    rem_ext_zero(num2);
    make_equal_length(num1, num2);
    PARENT_LIST sumOfNum1Num2;// sum of numbers num1 and num2
    init_parent(&sumOfNum1Num2);
    //if(num1->len_dec >= num2->len_dec) sumOfNum1Num2->len_dec = num1->len_dec;
    //else sumOfNum1Num2->len_dec = num2->len_dec;
    CHILD_NODE ptr1 = num1->tail;
    CHILD_NODE ptr2 = num2->tail;
    if(num1->sign == num2->sign){// numbers have the same sign
        int carry = 0;
        while(ptr1 != NULL){
            appendLeft(sumOfNum1Num2, (carry + (ptr1->digit) + (ptr2->digit))%10);
            carry = (carry + (ptr1->digit) + (ptr2->digit)) /10;
            ptr1 = ptr1->prev;
            ptr2 = ptr2->prev;
        }
        appendLeft(sumOfNum1Num2 , carry);
        sumOfNum1Num2->sign = num1->sign;
        return(sumOfNum1Num2);
    }
    else if(num1->sign == PLUS){
            num2->sign = PLUS;
            sumOfNum1Num2 =  subNumbers(num1, num2);
            return sumOfNum1Num2;
    }
    else{
        num1->sign = PLUS;
        sumOfNum1Num2 = subNumbers(num2, num1);
        return sumOfNum1Num2;
    }
}

//get product of two number lists
PARENT_LIST multiplyNumbers(PARENT_LIST num1, PARENT_LIST num2){
    rem_ext_zero(num1);
    rem_ext_zero(num2);
    PARENT_LIST finalSum;
    PARENT_LIST currentSum;
    init_parent(&finalSum);
    init_parent(&currentSum);
    append(finalSum, '0');

    CHILD_NODE ptr1 = num1->tail;
    CHILD_NODE ptr2 = num2->tail;
    int numberOfZeroesToBeAdded = 0;// to match order of number
    while(ptr1!=NULL){
        ptr2 = num2->tail;
        while(ptr2!=NULL){
            int binaryProduct = (ptr2->digit) * (ptr1->digit);
            appendLeft(currentSum, binaryProduct);
            ptr2 = ptr2->prev;
        }
        zero_at_end(currentSum, numberOfZeroesToBeAdded);
        makeEachDigitLessThanTen(currentSum);
        finalSum = addNumbers(finalSum, currentSum);
        init_parent(&currentSum);
        numberOfZeroesToBeAdded+=1;
        ptr1 = ptr1->prev;
    }
    if(num1->sign == num2->sign) finalSum->sign = PLUS;
    else finalSum->sign = MINUS;
    return finalSum;
}

//get quotient when num1 is divided by num2
PARENT_LIST divideNumbers(PARENT_LIST num1, PARENT_LIST num2){

    if(isZero(num2) == 1){
        printf("%s" , "Division by zero");
        return NULL;
    }
    PARENT_LIST quo;
    init_parent(&quo);

    if(getBiggerNumber(num1, num2) == NUMBER2){
        append(quo, '0');
        return quo;
    }
    else if(getBiggerNumber(num1, num2) == EQUAL){
        append(quo, '1');
        return quo;
    }
    else{
        rem_ext_zero(num1);
        rem_ext_zero(num2);
        CHILD_NODE ptr1 = num1->head;
        CHILD_NODE ptr2 = num2->head;
        PARENT_LIST subList;

        init_parent(&subList);
        append(subList, '0');
        int intermediateQuo = 0;
        while(ptr1 != NULL){
            append(subList, 48 + ptr1->digit);
            ptr1 = ptr1->next;
        while(getBiggerNumber(subList, num2) == NUMBER1 || getBiggerNumber(subList, num2) == EQUAL){
            subList = subNumbers(subList, num2);
            intermediateQuo++;
        }
        append(quo, 48 + intermediateQuo);
        intermediateQuo = 0;
        }
    }
    if(num1->sign == num2->sign) quo->sign = PLUS;
    else quo->sign = MINUS;
    return quo;
}

//get remainder when num1 is divided by num2;
PARENT_LIST getRemainder(PARENT_LIST num1, PARENT_LIST num2){
    PARENT_LIST remainder;
    init_parent(&remainder);
    if(getBiggerNumber(num1, num2) == NUMBER2){
        remainder = num1;
        return remainder;
    }
    if(isZero(num1) == 1){
        append(remainder , '0');
        return remainder;
    }
    if(isZero(num2) == 1){
        printf("%s", "Division by Zero!");
        return NULL;
    }
    remainder = subNumbers(num1, multiplyNumbers(divideNumbers(num1, num2), num2));
    return remainder;
}

//get num1 raised to num2
PARENT_LIST getExponent(PARENT_LIST num1, PARENT_LIST num2){
    PARENT_LIST ans;
    init_parent(&ans);

    if(isZero(num1)){
        append(ans, '0');
        return ans;
    }
    if(isZero(num2)){
        append(ans, '0');
        return ans;
    }
    else{
        append(ans, '1');
        PARENT_LIST oneList;
        init_parent(&oneList);
        append(oneList, '1');
        while(isZero(num2) == 0){
            num2 = subNumbers(num2, oneList);
            ans = multiplyNumbers(ans, num1);
        }
        if(num1->sign == MINUS && (num2->tail->digit %2 != 0)) ans->sign = MINUS;
        return ans;
    }
}
