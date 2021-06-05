#include <iostream>

template<typename T>
class Queue {
private:
    T element;
    Queue *next;
public:
    void print(Queue *top){
        Queue *stack=top;
        while (stack){
            printf("%i  ", stack->element); //надо переделать
            stack=stack->next;
        }
        printf("\n");
    };

    void push(Queue **top, T Data) {
        Queue *list1 = *top;

        Queue *list2;
        list2 = new Queue();
        list2->element = Data;
        if (*top == NULL) {
            *top = list2;
        } else {
            while (list1->next != NULL) {
                list1 = list1->next;
            }
            list1->next = list2;

        }
    }
    int pop(Queue **top){
        T Data;
        Queue *list1 = *top;
        if (list1->next!=NULL) {
            Queue *list2 = *top;
            list2 = list2->next;

            while (list2->next != NULL) {
                list1 = list1->next;
                list2 = list2->next;
            }
            Data = list2->element;
            list1->next = NULL;
        } else {
            Data = list1->element;
            *top=NULL;
        }
        return Data;

    }
    int peek(Queue **top){
        Queue *list2 = *top;
        if (list2->next!=NULL){
        list2=list2->next;
        while(list2->next!=NULL){
            list2=list2->next;
        }}
        return list2->element;
    }
    int count(Queue **top){
        int Data=0;
        Queue *list=*top;
        while (list){
            Data++;
            list=list->next;
        }
        return Data;
    }
    float average(Queue **top){
        int count=0;
        float summ=0;
        Queue *list=*top;
        while (list){
            count++;
            summ+=list->element;
            list=list->next;
        }
        summ/=count;
        return summ;
    }
    void Sort(Queue **top){
        Queue *list=*top;
        Queue<T> *list2 = NULL;
        int size =list->count(&list);
        T mas[size];
        for(int i=0;i<size;i++){
            mas[i]=list->pop(&list);
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
            list->push(&list2,mas[i]);
        }
        *top=list2;

    }
    void concatination(Queue **FirstList, Queue **SecondList,Queue **ThirdList){
        Queue *FL=*FirstList;
        Queue *SL=*SecondList;
        Queue *TL=NULL;
        FL->Sort(&FL);
        SL->Sort(&SL);
        int size=FL->count(&FL)+SL->count(&SL);
        for (int i=0; i<size;i++){
            if (FL!=NULL && SL!=NULL){
            if (FL->peek(&FL)>=SL->peek(&SL)) {
                push(&TL,pop(&FL));
            }
            else
            {
                push(&TL,pop(&SL));
            }
        }
        else {
            if (FL==NULL){push(&TL,pop(&SL));} else{push(&TL,pop(&FL));}
        }
        }

        *ThirdList=TL;
    }
};