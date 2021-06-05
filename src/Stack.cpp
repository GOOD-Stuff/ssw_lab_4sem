#include <iostream>
#pragma once;
template<typename T>
class Stack {
private:
    T element;
    Stack<T> *next;
    Stack<T> *begin;
public:

    inline bool operator > (Stack<T> & SF){ if (this->average(&this)>SF.average(&SF)){return true;}else{return false;}  };
    inline bool operator < (Stack<T> & SF){ if (this->average(&this)<SF.average(&SF)){return true;}else{return false;}  };
    inline bool operator ==(Stack<T> & SF){
        Stack<T> *stack = this;
        Stack<T> *stack2 = *SF;
        while (stack!=NULL & stack2!=NULL){
            if(stack->element==stack2->element){return false;}
        }
    };
    inline bool operator !=(Stack<T> & SF){
        Stack<T> *stack = this;
        Stack<T> *stack2 = *SF;
        while (stack!=NULL & stack2!=NULL){
            if(stack->element==stack2->element){return true;}
        }
    };

    void print(Stack<T> *top){
        Stack<T> *stack=top;
        while (stack){
            printf("%i  ", stack->element);
            stack=stack->next;
        }
        printf("\n");
    };

    float average(Stack<T> **First){
        Stack<T> *stack = *First;
        int Data1=0;
        T Data2=0;
        float Data3;
        while(stack){
            Data1++;
            Data2=Data2+stack->element;
            stack=stack->next;
        }
        Data3=Data2/Data1;
        return Data3;
    }

    void push(Stack<T> **top, T Data){
        Stack<T> *stack;
        stack = new Stack<T>();
        stack->element=Data;
        if (*top== NULL){
            stack->begin=stack;
            *top=stack;
            }
        else
        {
            Stack<T> *stack1 = *top;
            stack->begin=stack1->begin;
            stack->next=*top;
            *top=stack;
        }

    }
    T pop(Stack **top){
        T Data;
        Stack<T> *stack = *top;
        Data=stack->element;
        *top=stack->next;
        return Data;

    }
    void insert(Stack<T> **top, T Data, int index){//взаимовязь и ограниение по размеру
        Stack<T> *stack1=*top;
        if (index<=stack1->count(&stack1)){
            for(int i =0;i<index-1;i++){
                stack1=stack1->next;
            }
            Stack<T> *stack;
            stack = new Stack<T>();
            stack->element=Data;
            stack->begin=stack1->begin;
            stack->next=stack1->next;
            stack1->next=stack;
        } else {printf("Error");}
    }
    T erase(Stack<T> **top, int index){
       T Data;
        Stack<T> *stack1=*top;
        if (index<=stack1->count(&stack1)){
            Stack<T> *stack2=stack1->next;
            for(int i =0;i<index-1;i++){
                stack1=stack1->next;
                stack2=stack1->next;
            }
            Data=stack2->element;
            stack1->next=stack2->next;
        } else {
            Data=0;
        printf("Error");
        }
        return Data;
    }
    int count(Stack<T> **top){
        int Data=0;
        Stack<T> *stack=*top;
        while (stack){
            Data++;
            stack=stack->next;
        }
        return Data;
    }
    void getbegin(Stack<T> **top, Stack<T> **point){
        Stack<T> *stack=*top;
        *point=stack->begin;
    }
    void end(Stack<T> **top, Stack<T> **point){
        Stack<T> *stack=*top;
        while (stack->next==NULL){stack=stack->next;}
        *point= stack;
    }

};


