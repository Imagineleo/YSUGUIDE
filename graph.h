#include"seqList.h"
#include"QDebug"
#include "omp.h"
#include"stdio.h"
const int MaxVertices = 20;
const int MaxWeight = 1000000000;
extern int ind[20];
extern int sum;
struct RowColWeight    //用于方便CreateGraph()
{
    int Row;
    int Col;
    int Weight;
};

template<class T>
class AdjWMGraph
{
private:
    SeqList<T> Vertices;
    int Edge[MaxVertices][MaxVertices];
    int numOfEdges;
public:
    AdjWMGraph(const int sz = MaxVertices);                     //构造图的节点,默认值为20个节点
    ~AdjWMGraph();
    void CreateGraph(T V[], int n, RowColWeight E[], int e);    //创建图，即为节点添加地名，并连接对应节点，添加权(距离)
    bool InsertVertices(T V);                                   //与其说插入节点，更应理解为结点添加地名，使其有效
    void InsertEdge(const int row, const int col, int Weight);  //插入两点间的距离
    T GetValue(int i);                                          //获取节点的地名
    int GetWeight(int row, int col);                            //获取两点间的距离
    int GetNumOfVertices();                                     //获取总结点数
    int GetNumOfEdges();                                        //获取总边数
    bool DeleteVertices(int i);                                 //删除节点的地名，但节点在Seqlist中并未删除哦，使其失效
    bool DeleteEdge(int row, int col);                          //删除边
    void ShortPath(int v0,bool S[],int Path[],int D[]);         //迪杰斯特拉斯算法
    void FindMinToDist(int row, int col,int *num);                       //调用迪杰斯特拉斯算法，求两点间最短距离

};

template<class T>
AdjWMGraph<T>::AdjWMGraph(const int sz) :Vertices(sz)
{
#pragma omp parallel for                                                                                    //OPENMP开启多线程
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            if (i == j)
            {
                Edge[i][j] = 0;
                printf("i=%d,thread_id=%d\n",i,omp_get_thread_num());
            }
            Edge[i][j] = MaxWeight;
        }
    }
    numOfEdges = 0;
}

template<class T>
AdjWMGraph<T>::~AdjWMGraph()
{

}

template<class T>
void AdjWMGraph<T>::CreateGraph(T V[], int n, RowColWeight E[], int e)
{
    for (int i = 0; i < n; i++)
    {
        this->InsertVertices(V[i]);                         //初始化图节点信息，此处为地点名
    }
    for (int j = 0; j < e; j++)
    {
        this->InsertEdge(E[j].Row, E[j].Col, E[j].Weight);     //初始化对应边的权值，为两点距离
    }
}

template<class T>
bool  AdjWMGraph<T>::InsertVertices(T V)
{
    return Vertices.Insert(Vertices.Length(), V);
}

template<class T>
void AdjWMGraph<T>::InsertEdge(const int row, const int col, int Weight)
{
    if (row<0 || (row>Vertices.Length() - 1 )|| col<0 || (col>Vertices.Length() - 1))
    {

        qDebug() << "row and col is out of boundage" << endl;
        return;
    }
    Edge[row][col] = Weight;
    numOfEdges++;
}

template<class T>
T AdjWMGraph<T>::GetValue(int i)
{
    if (i<0 || i>Vertices.Length() - 1)
    {
        qDebug() << "the value of i if out of boundry" << endl;
        return NULL;
    }
    return Vertices.GetData(i);
}

template<class T>
int AdjWMGraph<T>::GetWeight(int row, int col)
{
    if (row<0 || (row>Vertices.Length() - 1) || col<0 || (col>Vertices.Length() - 1))
    {

        qDebug() << "row and col is out of boundage" << endl;
        return -1;
    }
    return Edge[row][col];
}

template<class T>
int AdjWMGraph<T>::GetNumOfEdges()
{
    return numOfEdges;
}

template<class T>
int AdjWMGraph<T>::GetNumOfVertices()
{
    return Vertices.Length();
}

template<class T>
bool AdjWMGraph<T>::DeleteEdge(int row, int col)
{
    if (row<0 || (row>Vertices.Length() - 1) || col<0 || (col>Vertices.Length() - 1))
    {

        qDebug() << "row and col is out of boundage" << endl;
        return false;
    }
    numOfEdges--;
    Edge[row][col] = MaxWeight;
    return true;
}

template<class T>
bool AdjWMGraph<T>::DeleteVertices(int i)
{
    if (i > Vertices.Length() - 1 || i < 0)
    {
        qDebug() << "i is out of boundage" << endl;
        return false;
    }
#pragma omp parallel for                                                                                        //OPENMP开启多线程
    for (int j = 0; j < Vertices.Length() - 1; j++)
    {
        for (int k = 0; k < Vertices.Length() - 1; k++)
        {
            if ((j == i || k == i) && Edge[j][k]>0 && k != j)
            {
                Edge[j][k] = MaxWeight;
                numOfEdges--;
                printf("j=%d,thread_id=%d\n",j,omp_get_thread_num());
            }
        }
    }
    Vertices.SetData(i, NULL);
    return true;
}

template<class T>
void AdjWMGraph<T>::ShortPath(int v0, bool S[], int Path[], int D[])
{
    int n = this->GetNumOfVertices();
#pragma omp parallel for
    for (int v = 0; v < n; v++)
    {
        S[v] = false;
        D[v] = this->GetWeight(v0, v);
        if (D[v] < MaxWeight)
            Path[v] = v0;
        else
            Path[v] = -1;
       printf("v=%d,thread_id=%d\n",v,omp_get_thread_num());
    }
    S[v0] = true;
#pragma omp parallel for                                                                                     //OPENMP开启多线程
    for (int i = 1 ; i < n; i++)
    {
        int min = MaxWeight;
        int v = v0;
        for (int w = 0; w < n; w++)
           if (!S[w] && D[w] < min)
            {
                v = w;
                min = D[w];
            }
            S[v] = true;                //找到最小路径下角标节点

            for (int w = 0; w < n; w++)     //增加节点后更改其他非最小路径的距离
            {
                if (!S[w] && (D[v] + this->GetWeight(v, w) < D[w]))
                {
                    D[w] = D[v] + this->GetWeight(v, w);
                    Path[w] = v;
                }
            }

            printf("i=%d,thread_id=%d\n",i,omp_get_thread_num());
    }
}

template<class T>
void AdjWMGraph<T>::FindMinToDist(int row, int col,int *num)
{
   const int n = this->GetNumOfVertices();
    bool* S = new bool[n];
    int* Path = new int[n];
    int* D = new int[n];

    ShortPath(row, S, Path, D);
    if (D[col] == MaxWeight)
    {
        qDebug()<< "cannot get to here" << endl;
        delete[] S;
        delete[] Path;
        delete[] D;
        return;
    }
    else
    {
        sum=D[col];

        qDebug() << "-----------------------------------------------------------------------------" << endl;
        qDebug() << "--------------------------the way get to here is:----------------------------" << endl;
        T name[20];

        int index = 0;
        int x = 0;
        name[index++] = Vertices.GetData(col);
        ind[x++] = col;

        int i = col;
        while (Path[i] != row)
        {
            name[index++] = Vertices.GetData(Path[i]);
            ind[x++] = Path[i];
            i = Path[i];
        }
        name[index] = Vertices.GetData(row);
        ind[x++] = row;
        ind[x]='a';
        x=0;
        while(ind[x]!='a')
        {

        qDebug()<<ind[x]<<endl;
        x++;
        }
        for (int k = index; k > -1;k--)
        {
           qDebug() << name[k];
            if (k != 0)
            {
                qDebug() << "----->";
            }
        }
        delete[] S;
        delete[] Path;
        delete[] D;
        qDebug() << endl;
    }

}
