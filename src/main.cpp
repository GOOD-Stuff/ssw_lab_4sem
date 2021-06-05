#include <iostream>
#include "Stack.cpp"
#include "Queue.cpp"
#include "Vector.cpp"
int main() {
    Stack<int> *StackFirst = NULL;
    Stack<int> *StackSecond = NULL;
    Stack<int> *StackThird = NULL;

    int random;
    for(int i=0;i<10;i++){
        random=rand();
        StackFirst->push(&StackFirst,random);
        random=rand();
        StackSecond->push(&StackSecond,random);
    }

    printf("First stack:  ");
    StackFirst->print(StackFirst);
    printf("Second stack:  ");
    StackSecond->print(StackSecond);

    printf("Average of first stack:  %e\n",StackFirst->average(&StackFirst));
    printf("Average of second stack:  %e\n",StackSecond->average(&StackSecond));

    StackThird->concatination(&StackFirst,&StackSecond,&StackThird);
    printf("Result of concatination:  ");
    StackThird->print(StackThird);



    Queue<int> *uFirst = NULL;
    Queue<int> *uSecond = NULL;
    Queue<int> *uThird = NULL;

    for(int i=0;i<10;i++){
        random=rand();
        uFirst->push(&uFirst,random);
        random=rand();
        uSecond->push(&uSecond,random);
    }

    printf("First Queue:  ");
    uFirst->print(uFirst);
    printf("First Queue:  ");
    uSecond->print(uSecond);

    printf("Average of first Queue:  %e\n",uFirst->average(&uFirst));
    printf("Average of second Queue:  %e\n",uSecond->average(&uSecond));

    uThird->concatination(&uFirst,&uSecond,&uThird);
    printf("Result of concatination:  ");
    uThird->print(uThird);

    Queue<int> *VFirst = NULL;
    Queue<int> *VSecond = NULL;
    Queue<int> *VThird = NULL;

    for(int i=0;i<10;i++){
        random=rand();
        VFirst->push(&VFirst,random);
        random=rand();
        VSecond->push(&VSecond,random);
    }

    printf("First Vector:  ");
    uFirst->print(VFirst);
    printf("First Vector:  ");
    uSecond->print(VSecond);

    printf("Average of first Vector:  %e\n",VFirst->average(&VFirst));
    printf("Average of second Vector:  %e\n",VSecond->average(&VSecond));


    VThird->concatination(&VFirst,&VSecond,&VThird);
    printf("Result of concatination:  ");
    VThird->print(VThird);
    return 0;
}
