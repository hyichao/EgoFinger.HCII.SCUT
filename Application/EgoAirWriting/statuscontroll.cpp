#include "statuscontroll.h"

StatusControll::StatusControll()
{

}

StatusControll::~StatusControll()
{

}

void StatusControll::initStatus()
{
    cur_status = STATUS_BG;
    status = STATUS_BG;
    for(int i=0; i<7; i++){
        shift_counter.push_back(0);
    }

    // allow status shifting only when accumulate to thresh
    shift_thresh.push_back(5); //BG
    shift_thresh.push_back(5); //Close
    shift_thresh.push_back(5); //Open
    shift_thresh.push_back(5); //L-Shape
    shift_thresh.push_back(5); //I-Shape
    shift_thresh.push_back(5); //Victory
    shift_thresh.push_back(5); //Fist

    isShiftingStatus = false;
    isRecognizing = false;
    recognizingCounter = -30;
}

void StatusControll::calcCurrentStatus(const float* categ_vec, int length)
{
    const float* roi_categ = categ_vec+8;
    float roi_max = 0;
    int roi_max_index = 0;
    for(int i=0;i<length;i++){
        if(roi_categ[i]>roi_max){
            roi_max = roi_categ[i];
            roi_max_index = i;
        }
    }

    const float* rot_roi_categ = categ_vec+15+8;
    float rot_roi_max = 0;
    int rot_roi_max_index = 0;
    for(int i=0;i<length;i++){
        if(rot_roi_categ[i]>rot_roi_max){
            rot_roi_max = rot_roi_categ[i];
            rot_roi_max_index = i;
        }
    }

    if(rot_roi_max_index==roi_max_index)
        cur_status = GesStatus(roi_max_index);
    else
        cur_status = cur_status;
}

void StatusControll::switchStatus()
{
    for(uint i=0;i<shift_counter.size();i++){
      if(cur_status==GesStatus(i) && status!=GesStatus(i)){
          // only when current_status != current_status will cause switching
          if(shift_counter[i]<shift_thresh[i]){
              shift_counter[i]++;
              isShiftingStatus = false;
              break;
          } else {
              status = GesStatus(i);
              isShiftingStatus = true;
              for(uint i=0;i<shift_counter.size();i++)
                  shift_counter[i]=0;
              break;
          }
      }
    }
}

bool StatusControll::judgeBackground()
{
    if(status==STATUS_BG) return true;
    else return false;
}

bool StatusControll::judgeClose()
{
    if(status==STATUS_CLOSE) return true;
    else return false;
}

bool StatusControll::judgeOpen()
{
    if(status==STATUS_OPEN) return true;
    else return false;
}

bool StatusControll::judgeLback()
{
    if(status==STATUS_LSHAPE) return true;
    else return false;
}

bool StatusControll::judgeIback()
{
    if(status==STATUS_ISHAPE) return true;
    else return false;
}

bool StatusControll::judgeVictory()
{
    if(status==STATUS_VICTORY) return true;
    else return false;
}

bool StatusControll::judgeFist()
{
    if(status==STATUS_FIST) return true;
    else return false;
}



