#include <iostream>
using namespace std;
template<typename T>
class Vector {
private:
    unsigned int count{0};
    unsigned int size{0};
    int *buffer{nullptr};
public:


    bool operator==(const Vector &struct2) {
        if (count == struct2.count) {
            int i = 0;
            do {
                if (buffer[i] != struct2.buffer[i]) return false;
                i++;
            } while ((buffer[i] == struct2.buffer[i]) && (i < count));
            return true;
        };
        return false;
    };

    bool operator!=(const Vector &struct2) {
        return !(*this == struct2);
    };

    bool operator>(const Vector &struct2) {
        int i = 0;
        if (count >= struct2.count) {
            do {
                if (buffer[i] < struct2.buffer[i]) return false;
                else if (buffer[i] > struct2.buffer[i]) return true;
                i++;
            } while ((buffer[i] == struct2.buffer[i]) && (i < (struct2.count - 1)));
            if (count > struct2.count) return true;
            else return false;
        } else {
            do {
                if (buffer[i] < struct2.buffer[i]) return false;
                else if (buffer[i] > struct2.buffer[i]) return true;
                i++;
            } while ((buffer[i] == struct2.buffer[i]) && (i < struct2.count));
        }
        return false;
    };

    bool operator<(const Vector &struct2) {

        int i = 0;
        if (count >= struct2.count) {
            do {
                if (buffer[i] < struct2.buffer[i]) return true;
                else if (buffer[i] > struct2.buffer[i]) return false;
                i++;
            } while ((buffer[i] == struct2.buffer[i]) && (i < struct2.count));
            if (count > struct2.count) return false;
            else return true;
        } else {
            do {
                if (buffer[i] < struct2.buffer[i]) return true;
                else if (buffer[i] > struct2.buffer[i]) return false;
                i++;
            } while ((buffer[i] == struct2.buffer[i]) && (i < count));
        }
        return true;
    };

    bool operator<=(const Vector &struct2) {
        return !(*this > struct2);
    };

    bool operator>=(const Vector &struct2) {
        return !(*this < struct2);
    };


   ~Vector() { delete[] buffer; };

    void push(T t1) {
        if (count == 0 && size == 0) {
            size = size + 1;
            buffer = new int[size];
        }
        if ((count + 1) > size) {
            T *Mass;
            size = size + 2;
            Mass = new T[size];
            for (int i = 0; i < count; i++)
                Mass[i] = buffer[i];
            Mass[count] = t1;
            delete[]buffer;
            buffer = Mass;
            count++;
        } else {
            buffer[count] = t1;
            count++;
        }

    };

    int pop() {
        if (count < 1)
            throw std::range_error("Going beyond the vector");
        T vozvrat = buffer[count - 1];
        if (size != 1)
            size--;//No cleanup of memory used
        T *Mass;
        Mass = new T[size];
        for (int i = 0; i < count; i++)
            Mass[i] = buffer[i];
        delete[]buffer;
        buffer = Mass;
        count--;
        return vozvrat;
    };

    int &at(int index) {
        if (index > count)
            throw std::range_error("Going beyond the vector");
        return buffer[index];
    };

    int peek() {
        if (count < 1)
            throw std::range_error("Going beyond the vector");
        return buffer[0];
    };

    int countelement() {
        return count;
    };

    void Sort() {
        T *mas;
        mas = new T[size];
        for (int i = 0; i < count; i++)
            mas[i] = buffer[i];
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
        delete[]buffer;
        buffer = mas;

    };
    void concatination(Vector **FirstList,Vector **SecondList,Vector **ThirdList){
        Vector<T> *FV=*FirstList;
        Vector<T> *SV=*SecondList;
        Vector<T> *TV=NULL;
        FV->Sort(&FV);
        SV->Sort(&SV);
        int size=FV->size+SV->size;
        for (int i=0; i<size;i++){
            if (FV!=NULL && SV!=NULL){
                if (FV->peek(&FV)>=SV->peek(&SV)) {
                    push(&TV,pop(&FV));
                }
                else
                {
                    push(&TV,pop(&SV));
                }
            }
            else {
                if (FV==NULL){push(&TV,pop(&SV));} else{push(&TV,pop(&FV));}
            }
        }

        *ThirdList=TV;
    }

    void print(){
            for (int i = 0; i < count; i++)
                printf("%i  ",  buffer[i]);
    }
    float average(){
        T v=0;
        for (int i = 0; i < count; i++)
            v+=buffer[i];
        return v/count;
    }
};