#include "c.h"

int main(int argc,char *argv[])
{
    struct dataSet<string,double> ds[1000];
    struct labelCount<string>lc[3]={{"smallDoses"},{"largeDoses"},{"didntLike"}};
    
    for(int i=0;i<1000;++i)//输入数据
    {
        double data;
        for(int j=0;j<3;++j)
        {
            cin>>data;
            ds[i].data.insert(data);
        }
        string str;
        cin>>str;
        ds[i].label=str;
    }

    double max[3]={0,0,0},min[3]={MAX,MAX,MAX},mid[3];//权值归一化
    for(int i=0;i<800;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(max[j]<ds[i].data[j])
                max[j]=ds[i].data[j];
            if(min[j]>ds[i].data[j])
                min[j]=ds[i].data[j];
        }
    }
    for(int j=0;j<3;++j)
        mid[j]=max-min;
    for(int i=0;i<1000;++i)
    {
        for(int j=0;j<3;++j)
            ds[i].data[j]=(ds[i].data[j]-min[j])/mid[j];
    }

    for(int k=5;k<20;++k)//开始分类
    {
        int count=0;
        for(int i=800;i<1000;++i)
        {
            for(int j=0;j<800;++j)
                ds[j].getdistance(&ds[i]);
            sort<string,double>(ds,800);
            getLabel<string,double>(ds,lc,k,3);
            if(ds[i].label==resultLabel<string>(lc,3))
                count++;
        }
        cout<<k<<":"<<(double)count/2<<"%"<<endl;
    }

    return 0;
}