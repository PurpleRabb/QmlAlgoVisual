#include "quicksort.h"
#include <QStack>

void QuickSort::run()
{
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    qDebug() << "QuickSort";
    quickSortNoRec(values,0,values->length()-1);
    emit updateValue();
    emit algofinished();
}

int QuickSort::partition(QList<int>* data,int l,int r)
{
    int x = (*data)[r];	//基准
    if(l >= r)
        return l;
    while(l < r){
        while(l < r && (*data)[l] < x){
            l++;
        }
        if(l < r){
            (*data)[r] = (*data)[l];
            r--;
        }
        while(l < r && (*data)[r] > x){
            r--;
        }
        if(l < r){
            (*data)[l] = (*data)[r];
            l++;
        }
    }
    (*data)[l] = x;
    return l;

}

void QuickSort::quickSortNoRec(QList<int>* data,int l,int r)
{
    QStack<int> st;
    if(l < r)
    {
        int tmp = partition(data,l,r);
        if(tmp-1 > l)	//左边不止一个元素
        {
            st.push(tmp-1);
            st.push(l);
        }
        if(tmp+1 < r)
        {
            st.push(r);
            st.push(tmp+1);
        }
        while(!st.empty()){
            int start = st.top();
            st.pop();
            int end = st.top();
            st.pop();

            int tmp = partition(data,start,end);
            if(tmp-1 > start)	//左边不止一个元素
            {
                st.push(tmp-1);
                st.push(start);
            }
            if(tmp+1 < end)
            {
                st.push(end);
                st.push(tmp+1);
            }
        }
    }
}
