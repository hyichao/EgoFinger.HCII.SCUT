#ifndef STATUSCONTROLL_H
#define STATUSCONTROLL_H

#include "common.h"

class StatusControll
{
public:
    StatusControll();
    ~StatusControll();

public:
    vector<int> shift_thresh;
    vector<int> shift_counter;

    GesStatus status;
    GesStatus cur_status;

    bool isShiftingStatus;
    bool isRecognizing;
    int recognizingCounter;
    bool isDeleting;

    void initStatus();

    void calcCurrentStatus(const float* categ_vec, int length);
    void switchStatus();

    bool judgeBackground();
    bool judgeClose();
    bool judgeOpen();
    bool judgeLback();
    bool judgeIback();
    bool judgeVictory();
    bool judgeFist();
};

#endif // STATUSCONTROLL_H
