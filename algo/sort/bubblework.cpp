#include "bubblework.h"

void BubbleWork::run() {
    if (values == nullptr) {
        emit algofinished();
        return;
    }
    qsizetype len = values->length();
    for (int i=0; i < len - 1; i++) {
        for (int j=0; j<len-1-i; j++) {
            emit algoStatus(MARKED(j,j+1));
            msleep(_speed);
            if ((*values)[j] > (*values)[j+1]) {
                emit algoStatus(SWAP(j,j+1));
                msleep(_speed/2);
                std::swap((*values)[j],(*values)[j+1]);
                emit updateValue();
                msleep(_speed/2);
            }
            emit algoStatus(RESTORED(j,-1));//将比较的前一个数字颜色还原
        }
    }
    emit algoStatus(MARKED(0,-1)); //结束后将最前面的也涂掉
    emit algofinished();
}
