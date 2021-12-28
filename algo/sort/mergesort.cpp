#include "mergesort.h"

void MergeSort::run() {
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    int len = static_cast<int>(values->length());
    int *tmp = new int[len];
    __MergeSort(values,0,len-1,tmp);
    //emit updateValue();
    delete [] tmp;
}

#define IVALUES (*_values)

void MergeSort::__MergeSort(QList<int> *_values, int left, int right, int *tmp)
{
    if( left >= right ) //退出条件
        return;
    int mid = left+((right-left)>>1);
    msleep(_speed);
    emit updateValue();
    __MergeSort(values,left,mid,tmp); // 递归左半数组
    __MergeSort(values,mid+1,right,tmp); // 递归右半数组

    //将排好序的两部分数组归并（排序）

    int begin1 = left,end1 = mid;
    int begin2 = mid+1,end2 = right;
    int index = left;

    while( begin1<=end1 && begin2<=end2 )// 循环条件：任一个数组排序完，则终止条件，最后将没有比较完的数组直接一一拷过去
    {
        if( IVALUES[begin1] <= IVALUES[begin2] )
        {
            tmp[index++] = IVALUES[begin1++];
        }
        else
        {
            tmp[index++] = IVALUES[begin2++];
        }
    }

    while( begin1 <= end1 )//右半数组走完了
    {
        tmp[index++] = IVALUES[begin1++];
    }
    while( begin2 <= end2 )//左半数组走完了
    {
        tmp[index++] = IVALUES[begin2++];
    }

    //tmp数组已经排好序,将数组内容拷到原数组，递归向上一层走
    index = left;
    while( index <= right )
    {
        IVALUES[index] = tmp[index];
        ++index;
    }
}
