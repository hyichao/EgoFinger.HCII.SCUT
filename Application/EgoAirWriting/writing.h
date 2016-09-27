#ifndef WRITING_H
#define WRITING_H

#include "common.h"

class Writing
{
public:
    Writing();
    ~Writing();

    void addPoint(cv::Point point);
    void clearPoints();
    int getPointCount();
    vector<cv::Point> getPoints();

    string recognizeCharacter();
//    QString recognizeCharacter();

    static void UnicodeToUTF8(char *pOut, char *pIn){
        // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
        pOut[0] = (0xE0 | ((pIn[0] & 0xF0) >> 4));
        pOut[1] = (0x80 | ((pIn[0] & 0x0F) << 2)) + ((pIn[1] & 0xC0) >> 6);
        pOut[2] = (0x80 | (pIn[1] & 0x3F));
        return;
    }

private:
    vector<cv::Point> points_;

private:
    void smoothPoints();
};

#endif // WRITING_H
