#include "quicksort.h"
#include <QStack>

void QuickSort::run()
{
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    quickSortNoRec(values,0,values->length()-1);
    emit updateValue();
    emit algofinished();
}

int QuickSort::partion(QList<int>* root,int low,int high)
{
    int part= (*root)[low];
    while(low<high)
    {
        while(low<high&& (*root)[high]>part) high--;
        (*root)[low]=(*root)[high];
        while(low<high&& (*root)[low]<part) low++;
        (*root)[high]=(*root)[low];
    }
    (*root)[low]=part;
    return low;
}

void QuickSort::quickSortNoRec(QList<int>* root,int low,int high)
{
    QStack<int> st;
    int k;
    if(low<high)
    {
        st.push(low);
        st.push(high);
        while(!st.empty())
        {
            int j=st.top();st.pop();
            int i=st.top();st.pop();

            k=partion(root,i,j);

            if(i<k-1)
            {
                st.push(i);
                st.push(k-1);
            }
            if(k+1<j)
            {
                st.push(k+1);
                st.push(j);
            }
        }
    }
}
