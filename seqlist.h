#include"LinearList.h"
#include<iostream>
using namespace std;
const int defaultSize = 20;

template<class T>
class SeqList :public LinearList<T>{
private:
    T* data;
    int MaxSize;
    int n;
public:
    SeqList(int sz = defaultSize)
    {
        data = new T[sz];
        if (!data)
        {
            cout << "new data error" << endl;
            return;
        }
        MaxSize = sz;
        n = 0;

    }
    SeqList(const SeqList<T>& Seq);
    ~SeqList();
    int Size()const;
    int Length()const;
    bool IsEmpty()const;
    int Search(T x)const;
    bool Insert(int i, T x);
    bool Remove(int i, T &x);
    T GetData(int i)const;
    void SetData(int i, T x);
};

//template<class T>
//SeqList<T>::SeqList(int sz = defaultSize)
//{
//    data = new T[sz];
//    if (!data)
//    {
//        cout << "new data error" << endl;
//        return;
//    }
//    MaxSize = sz;
//    n = 0;
//}

template<class T>
SeqList<T>::SeqList(const SeqList<T>& Seq)
{
    this->data = Seq.data;
    this->MaxSize = Seq.MaxSize;
    this->n = Seq.n;
}

template<class T>
SeqList<T>::~SeqList()
{
    delete[]data;
}

template<class T>
bool SeqList<T>::IsEmpty()const
{
    return n == 0;
}

template<class T>
int SeqList<T>::Length()const
{
    return n;
}

template<class T>
int SeqList<T>::Size()const
{
    return MaxSize;
}

template<class T>
bool SeqList<T>::Insert(int i, T x)  //i为数组下标，从0开始
{
    if (i<0 || i>n)
    {
        cout << "the value of i is error" << endl;
        return false;
    }
    for (int j = n - 1; j > i - 1; j--)
        data[j + 1] = data[j];
    data[i] = x;
        n++;
        return true;
}

template<class T>
bool SeqList<T>::Remove(int i, T &x)
{
    if (i<0 || i>n - 1)
    {
        cout << "the value of i is error" << endl;
        return false;
    }
    for (int j = i; j < n - 1; j++)
        data[i] = data[i + 1];
    n--;
    return true;
}

template<class T>
int SeqList<T>::Search(T x)const             //返回的是下标
{
    for (int i = 0; i < n; i++)
    {
        if (data[i] == x)
            return i;
    }
    return -1;
}

template<class T>
T SeqList<T>::GetData(int i)const
{
    if (i<0 || i>n - 1)
    {
        cout << "the value of i is error" << endl;
        return NULL;
    }
    return data[i];
}

template<class T>
void SeqList<T>::SetData(int i, T x)
{
    if (i<0 || i>n - 1)
    {
        cout << "the value of i is error" << endl;
        return;
    }
    data[i] = x;
}
