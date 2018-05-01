#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include"linear_list.h"
using namespace std;
using namespace linear_list;

struct Data
{
    int number;
    sequencelist<char>datalist;
    int distance;
    void caldistance(Data *data)
    {
        distance=0;
        for(int i=0;i<datalist.length();++i)
        {
            distance+=pow(data->datalist[i]-datalist[i],2);
        }
        distance=sqrt(distance);
    }
};

void readdata(Data *data,char *filename)
{
    for(int i=0;;++i)//得到分类
    {
        if(filename[i]<='9'&&filename[i]>='0')
        {
            data->number=filename[i]-'0';
            break;
        }
    }
    ifstream ifile(filename);
    if(!ifile)
        throw -1;
    for(int i=0;i<32;++i)//读取数据
    {
        char ch;
        for(int j=0;j<32;++j)
        {
            ifile.get(ch);
            data->datalist.insert(ch);
        }
        ifile.get();//linux下读取/r/n
        ifile.get();
    }
    ifile.close();
}

void sort(Data *data,int len)
{
    for(int i=0;i<len;++i)
    {
        int k=i;
        for(int j=i+1;j<len;++j)
            if(data[k].distance>data[j].distance)
                k=j;
        if(k!=i)
        {
            Data temp=data[i];
            data[i]=data[k];
            data[k]=temp;
        }
    }
}

int getMax(int *number)
{
    int num=0;
    for(int i=1;i<10;++i)
        if(number[i]>number[num])
            num=i;
    return num;
}