#include <iostream>
#pragma once;
template<typename T>
class DLS {
private:
    T element;
    DLS *next;
    DLS *prev;
    DLS *begin;
public:
    inline bool operator > (DLS<T> & SF){ if (this->average(&this)>SF.average(&SF)){return true;}else{return false;}  };
    inline bool operator < (DLS<T> & SF){ if (this->average(&this)<SF.average(&SF)){return true;}else{return false;}  };
    inline bool operator ==(DLS<T> & SF){
        DLS<T> *stack = this;
        DLS<T> *stack2 = *SF;
        while (stack!=NULL & stack2!=NULL){
            if(stack->element==stack2->element){return false;}
        }
    };
    inline bool operator !=(DLS<T> & SF){
        DLS<T> *stack = this;
        DLS<T> *stack2 = *SF;
        while (stack!=NULL & stack2!=NULL){
            if(stack->element==stack2->element){return true;}
        }
    };
    float average(DLS<T> **First){
        bool v=true;
        DLS<T> *stack = *First;
        int Data1=0;
        T Data2=0;
        float Data3;
        while(stack!=stack->begin & v){
            Data1++;
            Data2=Data2+stack->element;
            stack=stack->next;
            if(stack!=stack->begin){v= false;}
        }
        Data3=Data2/Data1;
        return Data3;
    };
    void print(DLS *top) {
        DLS *dls = top;
        while (dls) {
            printf("%i  ",dls->element);
            dls = dls->next;
        }
        printf("\n");
    };

    void push(DLS **top, T Data) {
        DLS *dls;
        dls = new DLS();
        DLS *dls2 = *top;
        dls->element = Data;
        dls->prev = NULL;
        if (*top == NULL) {
            dls->begin=dls;
            *top = dls;
        } else {
            dls->begin=dls2->begin;
            dls2->prev = dls;
            dls->next = *top;
            *top = dls;
        }

    }
    T pop(DLS **top){
        T Data;
        DLS *dls = *top;
        DLS *dls2 = dls->prev;
        Data=dls->element;
        if (dls->prev==NULL){
            *top=dls->next;
        }else if(dls->next==NULL){
            dls=dls->prev;
            dls->next=NULL;
            *top=dls;
        }
        else{
        *dls2->next=*dls->next;
        *top=dls;}
        return Data;

    }
    int count(DLS **top){
        int Data=0;
        DLS *dls=*top;
        while (dls){
            Data++;
            dls=dls->next;
        }
        return Data;
    }
    void insert(DLS **top, T Data, int index){
        DLS *dls=*top;
        for(int i =0;i<=index;i++){
            dls=dls->next;
        }
        dls->push(&dls,Data);
    }
    T erase(DLS **top, int index){
        T Data;
        DLS *dls=*top;
        for(int i =0;i<=index;i++){
            dls=dls->next;
        }
        Data=dls->pop(&dls);
        return Data;
    }
    void getbegin(DLS **top, DLS **end){
        DLS *dls=*top;
        while (dls->prev==NULL){dls=dls->prev;}
        *end= dls;}
    void getend(DLS **top, DLS **end){
        DLS *dls=*top;
        while (dls->next==NULL){dls=dls->next;}
        *end= dls;
    }



};