#include"c.h"

void readdata(Data*,char*);
void sort(Data*,int);
int getMax(int *);


int main(int argv,char *argc[])
{
    //得到test 与 train的数据量
    int testcount,traincount;
    for(testcount=1;;++testcount)
        if(argc[testcount][1]=='r')
            break;
    char **teststr=argc+1,**trainstr=argc+testcount;
    traincount=argv-testcount;
    testcount=testcount-1;

    //构建数据块
    Data *testdata=new Data[testcount];
    Data *traindata=new Data[traincount];
    try{
        for(int i=0;i<testcount;++i)
        {
            readdata(testdata+i,teststr[i]);
        }
        for(int i=0;i<traincount;++i)
        {
            readdata(traindata+i,trainstr[i]);
        }
    }
    catch(int e){
        delete[] testdata;
        delete[] traindata;
        return e;
    }

    for(int k=5;k<20;++k)//开始测试
    {
        int count=0;
        for(int j=0;j<testcount;++j)
        {
            int number[10]={0};
            for(int i=0;i<traincount;++i)
                traindata[i].caldistance(testdata+j);
            sort(traindata,traincount);
            for(int m=0;m<k;++m)
                ++number[traindata[m].number];
            int label=getMax(number);
            if(label==testdata[j].number)
                ++count;
            cout<<testdata[j].number<<":"<<label<<endl;
        }
        cout<<k<<":"<<(double)count/testcount<<endl;
        cout<<endl;
    }

    delete[] testdata;
    delete[] traindata;
    return 0;
}