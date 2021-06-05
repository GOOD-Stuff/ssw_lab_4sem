#include <iostream>

template<typename T>
class Stack {
private:
    T element;
    Stack *next;

public:

    void print(Stack *top){
        Stack *stack=top;
        while (stack){
            printf("%i  ", peek(&stack));
            stack=stack->next;
        }
        printf("\n");
    };

    void push(Stack **top, T Data){
        Stack *stack;
        stack = new Stack();
        stack->element=Data;
        if (top== NULL){
            *top=stack;
        }
        else
        {
            stack->next=*top;
            *top=stack;
        }

    }
    int pop(Stack **top){
        T Data;
        Stack *stack = *top;
        Data=stack->element;
        *top=stack->next;
        return Data;

    }
    int peek(Stack **top){
        Stack *stack = *top;
        return stack->element;

    }
    int count(Stack **top){
        int Data=0;
        Stack *stack=*top;
        while (stack){
            Data++;
            stack=stack->next;
        }
        return Data;
    }
    float average(Stack **top){
        int count=0;
        float summ=0;
        Stack *stack=*top;
        while (stack){
            count++;
            summ+=stack->element;
            stack=stack->next;
        }
        summ/=count;
        return summ;
    }
    void Sort(Stack **top){
        Stack *stack=*top;
        int size =stack->count(&stack);
        T mas[size];
        for(int i=0;i<size;i++){
            mas[i]=stack->pop(&stack);
        }
        T temp;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (mas[j] > mas[j + 1]) {
                    // меняем элементы местами
                    temp = mas[j];
                    mas[j] = mas[j + 1];
                    mas[j + 1] = temp;
                }
            }
        }
        for(int i=0;i<size;i++){
            stack->push(&stack,mas[i]);
        }
        *top=stack;

    }
    void concatination(Stack **FirstStack, Stack **SecondStack,Stack **ThirdStack){
        Stack *FS=*FirstStack;
        Stack *SS=*SecondStack;
        Stack *TS=NULL;
        FS->Sort(&FS);
        SS->Sort(&SS);
        int size=FS->count(&FS)+SS->count(&SS);
        for (int i=0; i<size;i++){
            if (SS==NULL ||FS->element>=SS->element) {
                push(&TS,pop(&FS));
            }
            else
            {
                push(&TS,pop(&SS));
            }
        }

        *ThirdStack=TS;
    }
};
