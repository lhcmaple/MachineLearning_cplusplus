#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

#define LEN 28

struct datatype{
    double data[7][81];
    double distance;
    int label;
    double calsum(double *data1,double *data2)
    {
        double sum=0;
        for(int i=0;i<81;++i)
            sum+=pow(data1[i]-data2[i],2);
        return sum;
    }
    void getdistance(datatype *d)
    {
        distance=0;
        for(int i=0;i<7;++i)
        {
            distance+=calsum(data[i],d->data[i]);
        }
        distance=sqrt(distance);
    }
};

//拼接字符串类
class str{
private:
    char *s;
public:
    str(){s=NULL;}
    const char *setstr(const char *s1,const char *s2)
    {
        int len1=0,len2=0;
        while(s1[len1])
            ++len1;
        while(s2[len2])
            ++len2;
        if(!s)
            delete[] s;
        s=new char[len1+len2+1];
        int k=0,i=0,j=0;
        while(i<len1)
            s[k++]=s1[i++];
        while(j<len2)
            s[k++]=s2[j++];
        s[k]='\0';
        return s;
    }
    const char *setstr(const char *s1,const char *s2,const char *s3)
    {
        int len1=0,len2=0,len3=0;
        while(s1[len1])
            ++len1;
        while(s2[len2])
            ++len2;
        while(s3[len3])
            ++len3;
        if(!s)
            delete[] s;
        s=new char[len1+len2+len3+1];
        int k=0,i=0,j=0,l=0;
        while(i<len1)
            s[k++]=s1[i++];
        while(j<len2)
            s[k++]=s2[j++];
        while(l<len3)
            s[k++]=s3[l++];
        s[k]='\0';
        return s;
    }
    ~str()
    {
        if(!s)
            delete[] s;
    }
};

//读取数据
void readdata(struct datatype *trainset,struct datatype *testset,char *(name[6]),char *(file[6][LEN]))
{
    ifstream ifile;
    str s;
    for(int i=0;i<6;++i)
    {
        for(int j=0;j<28;++j)
        {
            ifile.open(s.setstr("data/",name[i],file[i][j]));
            for(int k=0;k<20;++k)
            {
                if(j<4)//标记
                    trainset[i*80+j*20+k].label=j+1;

                double temp;
                for(int l=0;l<30;++l)//剔除冗余数据
                    ifile>>temp;

                for(int l=0;l<81;++l)//read data
                    ifile>>trainset[i*80+j%4*20+k].data[j/4%7][l];
            }
            for(int k=0;k<10;++k)
            {
                if(j<4)//标记
                    testset[i*40+j*10+k].label=j+1;

                double temp;
                for(int l=0;l<30;++l)//剔除冗余数据
                    ifile>>temp;

                for(int l=0;l<81;++l)//read data
                    ifile>>testset[i*40+j%4*10+k].data[j/4%7][l];
            }
            ifile.close();
        }
    }
}

//排序
void sort(struct datatype *(sortset[]),int len)
{
    for(int i=0;i<len;++i)
    {
        int k=i;
        for(int j=i+1;j<len;++j)
            if(sortset[k]->distance>sortset[j]->distance)
                k=j;
        if(k!=i)
        {
            struct datatype *temp=sortset[k];
            sortset[k]=sortset[i];
            sortset[i]=temp;
        }
    }
}

//寻找k近邻标签
int getsuitlabel(int *labelcount,int len)
{
    int suit=0;
    for(int i=1;i<len;++i)
        if(labelcount[i]>labelcount[suit])
            suit=i;
    return suit+1;
}