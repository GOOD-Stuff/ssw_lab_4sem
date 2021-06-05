#include "Stack.cpp"
#include "DLS.cpp"
#include "RingBuffer.cpp"
#pragma once;

class common{
public:
    template<typename T>
    void Sort(Stack<T> **top){
        Stack<T> *stack=*top;
        int size =stack->count(&stack);
        T mas[size];
        for(int i=0;i<size;i++){
            mas[i]=stack->pop(&stack);
        }
        massort(mas,0,size-1);
        for(int i=0;i<size;i++){
            stack->push(&stack,mas[i]);
        }
        *top=stack;
    }

    template<typename T>
    void Sort(DLS<T> **top){
        DLS<T> *stack=*top;
        int size =stack->count(&stack);
        T mas[size];
        for(int i=0;i<size;i++){
            mas[i]=stack->pop(&stack);
        }
        massort(mas,0,size-1);
        for(int i=0;i<size;i++){
            stack->push(&stack,mas[i]);
        }
        *top=stack;
    }

    template<typename T>
    RingBuffer<T> Sort(RingBuffer<T> Ring){
        int a=Ring._writeCount;
        Ring._readCount=0;
        T b;
        T mas[a];
        for(int i=0;i<a;i++){
            Ring.Pop(b);
            mas[i]=b;
        }
        Ring.Clear();
        common *use = new common;
        use->massort(mas,0,a);
        for(int i=0;i<a;i++){
            b=mas[i];
            Ring.Push(b);
        }
        return Ring;
    };

    template<typename T>
    void massort(T* a, int first, int last)
    {

        int i = first, j = last;
        T tmp, x = a[(first + last) / 2];

        do {
            while (a[i] < x)
                i++;
            while (a[j] > x)
                j--;

            if (i <= j)
            {
                if (i < j)
                {
                    tmp=a[i];
                    a[i]=a[j];
                    a[j]=tmp;
                }
                i++;
                j--;
            }
        } while (i <= j);

        if (i < last)
            massort(a, i, last);
        if (first < j)
            massort(a, first,j);
    }

    template<typename T>
    void Segregation(Stack<T> **Original,Stack<T> **First,Stack<T> **Second, T Data){
        Stack<T> *stack1=*Original;
        Stack<T> *stack2=*First;
        Stack<T> *stack3=*Second;
        int size =stack1->count(&stack1);
        T tmp;
        for(int i=0;i<size;i++){
           tmp= stack1->pop(&stack1);
           if (tmp>Data){
               stack2->push(&stack2,tmp);
           } else {
               stack3->push(&stack3,tmp);
           }
        }
        *First=stack2;
        *Second=stack3;
    }

    template<typename T>
    void Segregation(DLS<T> **Original,DLS<T> **First,DLS<T> **Second, T Data){
        DLS<T> *stack1=*Original;
        DLS<T> *stack2 = *First;
        DLS<T> *stack3=*Second;
        int size =stack1->count(&stack1);
        T tmp;
        for(int i=0;i<size;i++){
            tmp= stack1->pop(&stack1);
            if (tmp>Data){
                stack2->push(&stack2,tmp);
            } else {
                stack3->push(&stack3,tmp);
            }
        }
        *First=stack2;
        *Second=stack3;
    }

    template<typename T>
    void Segregation (RingBuffer<T> RingFirst, T Data){
        RingFirst._readCount=0;
        RingBuffer<int> *RS = new RingBuffer<int>;
        RingBuffer<int> *RT= new RingBuffer<int>;
        RS->Clear();
        RT->Clear();
        T tmp;
        for (int i=0;i<16;i++) {
            RingFirst.Pop(tmp);
            if(tmp>Data){
                RS->Push(tmp);
            }else { RT->Push(tmp);}
        }
        printf("Second Ring buffer:  ");
        RS->Print();
        printf("Third Ring buffer:  ");
        RT->Print();
    }

};

