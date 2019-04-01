template<class T>
class LinearList{
public:
    virtual int Size()const = 0;
    virtual int Length()const = 0;
    virtual int Search(T x)const = 0;

    virtual T GetData(int i)const = 0;
    virtual void SetData(int i, T x) = 0;
    virtual bool Insert(int i, T x) = 0;
    virtual bool Remove(int i, T &x) = 0;
    virtual bool IsEmpty()const = 0;
};
