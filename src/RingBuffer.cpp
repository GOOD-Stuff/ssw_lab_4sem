#include <cstdint>
#include <iostream>
#pragma once;

template<typename T>
class RingBuffer
{
private:
    T _data[16];
public:

    typedef uint16_t INDEX_T;

    volatile INDEX_T _readCount;

    volatile INDEX_T _writeCount;

    static const INDEX_T _mask = 15;

    inline bool Push(T value)
    {
        if(IsFull())
            return false;
        _data[_writeCount++ & _mask] = value;
        return true;
    }

    inline bool Print(){
        if(IsEmpty())
            return false;
        _readCount=0;
        for (int i=0;i<_writeCount;i++){
            printf("%i   ",_data[i]);
        }
        printf("\n");
    }

    inline bool Pop(T &value)
    {
        if(IsEmpty())
            return false;
        value = _data[_readCount++ & _mask];
        return true;
    }

    inline bool ReadAndDelete(T &value)
    {
        if(IsEmpty())
            return false;
        _readCount++;
        value = _data[_readCount & _mask];
        _data[_readCount & _mask]=0;
        return true;
    }

    inline T First()const
    {
        return _data[0];
    }

    inline T Last()const
    {
        return operator[](Count());
    }

    inline const bool insert (INDEX_T i, T Data)const
    {
        if(IsEmpty())
            return false;
        for(int j=16;j>i;i--){
            _data[j]=_data[j-1];
        }
        _data[i]=Data;
        return true;
    }

    inline T erase (INDEX_T i){
        T Data=_data[i];
        for(int j=i;j<16;i++){
            _data[j]=_data[j+1];
        }
    }

    inline bool IsEmpty()const
    {
        return _writeCount == _readCount;
    }

    inline bool IsFull()const
    {
        return ((INDEX_T)(_writeCount - _readCount) & (INDEX_T)~(_mask)) != 0;
    }

    INDEX_T Count()const
    {
        return (_writeCount - _readCount) & _mask;
    }

    inline void Clear()
    {
        _readCount=0;
        _writeCount=0;
    }

    template<bool condition, class TypeIfTrue, class TypeIfFale>
    struct StaticIf
    {
        typedef TypeIfTrue Result;
    };

    template<class TypeIfTrue, class TypeIfFale>
    struct StaticIf<false, TypeIfTrue, TypeIfFale>
    {
        typedef TypeIfFale Result;
    };

    template<unsigned size>
    struct SelectSizeForLength
    {
        static const bool LessOrEq8 = size <= 0xff;
        static const bool LessOrEq16 = size <= 0xffff;

        typedef typename StaticIf<

                LessOrEq8,
                uint8_t,
                typename StaticIf<LessOrEq16, uint16_t, uint32_t>::Result>
        ::Result Result;
    };

};

