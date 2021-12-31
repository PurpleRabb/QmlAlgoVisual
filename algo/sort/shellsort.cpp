#include "shellsort.h"

//int* a,size_t n
void ShellSort::run()
{
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    qsizetype len = values->length();
    //1. gap > 1 预排序
    //2. gap == 1 直接插入排序
    //3. gap = gap/3 + 1; 保证最后一次排序是直接插入排序

    int gap = len;
    while ( gap > 1 )
    {
        gap = gap/3+1;
        msleep(_speed / 2);
        //单趟排序
        for(size_t i = 0;i < len - gap; ++i)
        {
            int end = i;
            int tmp = VALUES[end+gap];
            while( end >= 0 && VALUES[end] > tmp )
            {
                VALUES[end+gap] = VALUES[end];
                end -= gap;
                msleep(_speed / 2);
                emit updateValue();
            }
            VALUES[end+gap] = tmp;
            emit updateValue();
        }
    }
    emit algofinished();
}
