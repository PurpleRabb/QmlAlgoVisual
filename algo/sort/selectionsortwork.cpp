#include "selectionsortwork.h"


void SelectionSortWork::run() {
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    qsizetype len = values->length();
    qDebug() << "values len:" << len;
    //对数组a排序,length是数组元素数量
    for( int i = 0; i < len; i++ ) {
        // 找到从i开始到最后一个元素中最小的元素,k存储最小元素的下标.
        int k = i;
        for( int j = i + 1; j < len; j++ ) {
            if( (*values)[j] < (*values)[k] )
            {
                emit algoStatus(MARKED(k,-1));//标记要判断交换的两个数字
                k = j;
            }
        }

        // 将最小的元素a[k] 和 开始的元素a[i] 交换数据.
        if( k != i ) {
            std::swap((*values)[k],(*values)[i]);
        }

        emit updateValue();
        msleep(_speed);
    }
    emit algofinished();
}
