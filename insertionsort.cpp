#include "insertionsort.h"

void InsertionSort::run()
{
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    qsizetype len = values->length();
    int i, j,temp;
    for(i=1; i < len; i++) {
        msleep(_speed);
        if(VALUES[i] < VALUES[i-1]) { //判断是否是需要插入到有序数列的元素
            temp = VALUES[i]; //将要插入的元素保存
            algoStatus(MARKED(i,-1));
            for(j=i-1; j>=0; j--) {
                if(VALUES[j] > temp) {
                    VALUES[j+1] = VALUES[j]; //将他前面的元素后移
                }
                else
                    break;
            }
            VALUES[j+1] = temp; //找到插入的位置，其他元素已经后移保存直接插入即可
            algoStatus(MARKED(j+1,-1));
            emit algoStatus(RESTORED(i,-1));
            emit updateValue();
        }
    }
    //emit algoStatus(RESTORED(j,-1));
    //algoStatus(MARKED(0,-1));
    emit algofinished();
}
