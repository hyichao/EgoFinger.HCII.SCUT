#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "common.h"
#include "writing.h"
#include "coordtool.h"
#include "functions.h"

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();

public:
    VideoCapture capture;
    VideoWriter writer;

    // camera io
    Mat camera_input; //input frame of camera at any different size
    Mat camera_output;
    cv::Size camera_size;
    cv::Point camera_center;

    Mat src;                                    // network input as source, cropped and transformed from camera_input, 640*480
    Mat roi;                                    // roi before angle transform
    cv::Rect initial_rect;                      // initial rect of src from camera input
    cv::Point track_center;                     // track center in src

    bool has_angle;                             // rotated prediction
    float predict_angle;                        // angle predicted by first level CNN
    cv::Point center;                           // rotation center
    Mat rot_src;                                // rotated src with a predicted angle
    Mat rot_roi;                                // crop roi with rotated bounding box of hand
    vector<cv::Point> rot_predict_hand;         // rotated prediction of hand tl br with predicted angle
    vector<cv::Point> rot_minbounding_hand;     // create mininum bounding box of hand in rotated space
    vector<cv::Point> rot_predict_finger;       // predicted fingertip in rotated space

    //ouput
    vector<cv::Point> predict_hand;             // predicted hand of common space
    vector<cv::Point> predict_hand_expanded;    // for classification roi, not used yet.
    vector<cv::Point> predict_hand_bounding;    // predicted hand bounding after reverse-rotation
    vector<cv::Point> predict_finger;           // predicted fingertip after reverse-rotation

public:
    bool initCapture(int camera_id);
    bool readFrame();

    bool cutDirectRoi();
    bool cutRotatedRoi();

    void render(GesStatus& status);
    void render(Writing& writing, GesStatus& status);
    void showPointsOnMat(Writing& writing);

    void output2TlBr(float tlx, float tly, float brx, float bry, bool isDirect, float ang, bool hasAngle);
    void output2FtJnt(float ftx, float fty, float jntx, float jnty, bool isDirect, bool hasAngle);

    void attentionOffset();
    void updateTracker();
    void reInitTrackcenter();

public:
    string recognizedCdd;
    string recognized;
    void setRecognizedCdd(string cdd);
    void addUpRecognized(string str);
};

#endif // IMAGEPROCESSOR_H
