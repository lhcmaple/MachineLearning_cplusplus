#include "/home/lhc/Desktop/My Method/header.h"
#include "/home/lhc/Desktop/My Method/linear_list.h"

using namespace std;
using namespace linear_list;

#define MAX 99999999

template<typename T,typename D>struct dataSet{//D为数值型
    sequencelist<D> data;
    D distance;
    T label;
    D getdistance(dataSet<T,D> *ds)
    {
        distance=0;
        for(int i=0;i<data.length();++i)
            distance+=pow((ds->data[i]-data[i]),2);
        distance=sqrt(distance);
    }
};

template<typename T>struct labelCount{
    T label;
    int count;
};

template<typename T,typename D>void getLabel(dataSet<T,D> *ds,labelCount<T> *lc,int k,int type)
{
    for(int j=0;j<type;++j)
        lc[j].count=0;
    for(int i=0;i<k;++i)
    {
        for(int j=0;j<type;++j)
            if(lc[j].label==ds[i].label)
            {
                lc[j].count++;
                break;
            }
    }
}

template<typename T>T resultLabel(labelCount<T> *lc,int type)
{
    T label=lc[0].label;
    int count=lc[0].count;
    for(int i=1;i<type;++i)
        if(lc[i].count>count)
        {
            label=lc[i].label;
            count=lc[i].count;
        }
    return label;
}

template<typename T,typename D>void sort(dataSet<T,D> *ds,int len)
{
    for(int i=0;i<len;++i)
    {
        int k=i;
        for(int j=i+1;j<len;++j)
            if(ds[k].distance>ds[j].distance)
                k=j;
        if(k!=i)
        {
            dataSet<T,D> temp=ds[k];
            ds[k]=ds[i];
            ds[i]=temp;
        }
    }
}