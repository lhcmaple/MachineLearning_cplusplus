#include"c.h"

//#define DEBUG

int main(int argv,char *argc[])
{
    //获取文件路径名
    char *(file[6][LEN]);
    char *(name[6]);
    for(int i=0;i<6;++i)
    {
        name[i]=argc[1+i*(LEN+1)];
        int k=0;
        while(name[i][k]!=':')++k;
        name[i][k]='/';
        for(int j=0;j<LEN;++j)
            file[i][j]=argc[1+i*(LEN+1)+j+1];
    }

    //样本空间
    struct datatype trainset[480];
    struct datatype testset[240];
    struct datatype *(sortset[480]);//排序指针
    for(int i=0;i<480;++i)
        sortset[i]=trainset+i;

    //解析数据
    readdata(trainset,testset,name,file);

#ifdef DEBUG
    for(int i=0;i<480;++i)
    {
        cout<<trainset[i].label<<":"<<endl;
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<81;++k)
                cout<<trainset[i].data[j][k]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
#endif

    //检验算法
    for(int k=5;k<20;++k)
    {
        int count=0;
        for(int i=0;i<240;++i)
        {
            int labelcount[4]={0};
            for(int j=0;j<480;++j)
                trainset[j].getdistance(testset+i);
            sort(sortset,480);
            for(int l=0;l<k;++l)
                ++labelcount[sortset[l]->label-1];
            if(testset[i].label==getsuitlabel(labelcount,4))
                ++count;
            //cout<<testset[i].label<<":"<<getsuitlabel(labelcount,4)<<endl;
        }
        cout<<k<<endl;
        cout<<"percentage:"<<(double)count/240*100<<endl;
    }

    return 0;
}