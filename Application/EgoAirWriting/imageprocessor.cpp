#include "imageprocessor.h"

ImageProcessor::ImageProcessor()
{

}

ImageProcessor::~ImageProcessor()
{

}

bool ImageProcessor::initCapture(int camera_id)
{
    capture.open(camera_id);

    if (!capture.isOpened()) {
        qDebug() << "Can not open camera" << endl;
        return false;
    }
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    qDebug() << "Open up camera succussfully";

//    writer.open("Video.avi", CV_FOURCC('M','J','P','G'), 30.0, cv::Size(640,480));

    cv::Mat first_camera_input;
    capture>>first_camera_input;

    camera_size.width = first_camera_input.cols;
    camera_size.height = first_camera_input.rows;

    qDebug() << "Camera size : width = " << camera_size.width << ", height = " << camera_size.height;
    camera_center.x = camera_size.width/2;
    camera_center.y = camera_size.height/2;

    initial_rect = cv::Rect(cv::Point(camera_center.x-SRC_SIZE.width/2, camera_center.y-SRC_SIZE.height/2),
                            cv::Point(camera_center.x+SRC_SIZE.width/2, camera_center.y+SRC_SIZE.height/2));

    track_center.x = camera_size.width/2;
    track_center.y = camera_size.height/2;

    return true;
}

bool ImageProcessor::readFrame()
{
    capture>>camera_input;
    if(!camera_input.data){
        LOG(FATAL)<<"Error camera input";
        return false;
    }
    int offset_x =  camera_center.x - track_center.x;
    int offset_y = camera_center.y - track_center.y;
    cv::Mat translate_mat = (cv::Mat_<double>(2,3) << 1,0,offset_x,0,1,offset_y);
    cv::Mat translated_camera_input;
    cv::warpAffine(camera_input, translated_camera_input, translate_mat, camera_input.size(),
                   cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(127, 127, 127));
    src = translated_camera_input(initial_rect);

    return true;
}

void ImageProcessor::render(Writing& writing, GesStatus& status)
{
    cv::Point point = predict_finger[0];

    switch(status){
      case STATUS_BG:
        showPointsOnMat(writing);break;
      case STATUS_CLOSE:
        showPointsOnMat(writing);break;
      case STATUS_OPEN:
        showPointsOnMat(writing);break;
      case STATUS_LSHAPE:
        showPointsOnMat(writing);break;
      case STATUS_ISHAPE:
        writing.addPoint(point);
        if(writing.getPointCount()>5){
            string str = writing.recognizeCharacter();
            setRecognizedCdd(str);
        }
        showPointsOnMat(writing);break;
      case STATUS_VICTORY:
        showPointsOnMat(writing);break;
      case STATUS_FIST:
        showPointsOnMat(writing);break;
      default:
        showPointsOnMat(writing);break;
    }
//    writer<<camera_output;
}

void ImageProcessor::render(GesStatus& status)
{
    camera_output = camera_input;

    if(status==STATUS_BG){
        return;
    }
    if(status==STATUS_ISHAPE){
        // predict hand with green
        cv::circle(camera_output, predict_hand[0], 3, COLOR_GREEN, 3);
        cv::circle(camera_output, predict_hand[1], 3, COLOR_GREEN, 3);
        cv::rectangle(camera_output, cv::Rect(predict_hand[0], predict_hand[1]), COLOR_GREEN, 3);

//        predict bounding hand with red
//        for(uint i = 0; i<4;i++)
//            cv::line(camera_output, predict_hand_bounding[i],predict_bounding_hand[(i+1)%4],COLOR_RED,3);

        // predict finger with red
        cv::circle(camera_output, predict_finger[0], 3, COLOR_RED, 3);
        cv::circle(camera_output, predict_finger[1], 3, COLOR_RED, 3);
    } else {
        // predict hand with green
        cv::circle(camera_output, predict_hand[0], 3, COLOR_GREEN, 3);
        cv::circle(camera_output, predict_hand[1], 3, COLOR_GREEN, 3);
        cv::rectangle(camera_output, cv::Rect(predict_hand[0], predict_hand[1]), COLOR_GREEN, 3);

//        predict bounding hand with red
//        for(uint i = 0; i<4;i++)
//            cv::line(camera_output, predict_hand_bounding[i],predict_bounding_hand[(i+1)%4],COLOR_RED,3);
    }
//    writer<<camera_output;
}


void ImageProcessor::output2TlBr(float x1, float y1, float x2, float y2, bool isDirect,
                                 float ang, bool hasAngle)
{
    //output
    cv::Point tl;
    cv::Point br;
    int src_width = src.cols, src_height = src.rows;
    if(!isDirect){
        tl = cv::Point(x1*src_width-x2*src_width/2,y1*src_height-y2*src_height/2);
        br = cv::Point(x1*src_width+x2*src_width/2,y1*src_height+y2*src_height/2);
    } else{
        tl = cv::Point(x1*src_width, y1*src_height);
        br = cv::Point(x2*src_width, y2*src_height);
    }
    vector<cv::Point> raw_predict_hand;
    raw_predict_hand.push_back(tl);
    raw_predict_hand.push_back(br);
    predict_hand.assign(2,cv::Point(0,0));
    predict_hand_expanded.assign(2,cv::Point(0,0));
    CoordTool::EnlargeBoundingBox(raw_predict_hand,predict_hand,0.1,src.cols,src.rows);
    CoordTool::EnlargeBoundingBox(raw_predict_hand,predict_hand_expanded,0.3,src.cols,src.rows);

    if(hasAngle){
        float cos_value_plus1 = ang;        //some tricky while training
        float cos_value = cos_value_plus1-1;
        has_angle = hasAngle;
        predict_angle = acos(cos_value)*180/M_PI;
        center = cv::Point((predict_hand[0].x+predict_hand[1].x)/2, (predict_hand[0].y+predict_hand[1].y)/2);
    } else{
        has_angle = hasAngle;
        predict_angle = 0;
        center = cv::Point((predict_hand[0].x+predict_hand[1].x)/2, (predict_hand[0].y+predict_hand[1].y)/2);
    }
}

bool ImageProcessor::cutDirectRoi()
{
    CoordTool::protectPointsFromEdge(predict_hand_expanded,src.cols,src.rows);

    cv::Mat temp(src, cv::Rect(predict_hand_expanded[0],predict_hand_expanded[1]));
    temp.copyTo(roi);

    return (roi.data)?true:false;
}

bool ImageProcessor::cutRotatedRoi()
{
   // rotation
   cv::Mat rot_mat(2, 3, CV_32FC1);  //旋转矩阵
   rot_mat = cv::getRotationMatrix2D(center, 90-predict_angle, 1);// anti-clockwise
   rot_src = cv::Mat::zeros(src.rows, src.cols, src.type());
   warpAffine(src, rot_src, rot_mat, rot_src.size(),
              cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(127, 127, 127));

   vector<cv::Point> points(4);
   points[0] = cv::Point(predict_hand[0].x, predict_hand[0].y);
   points[1] = cv::Point(predict_hand[1].x, predict_hand[0].y);
   points[2] = cv::Point(predict_hand[1].x, predict_hand[1].y);
   points[3] = cv::Point(predict_hand[0].x, predict_hand[1].y);
   // 4 points in rotated src
   rot_predict_hand.assign(points.size(),cv::Point(0,0));
   for(uint i=0; i<points.size(); i++){
       CoordTool::RotatePoints(points[i], rot_predict_hand[i], rot_mat);
   }

   // minimum bounding rect of rotated points
   CoordTool::GetMinBoundingRect(rot_predict_hand,rot_minbounding_hand);

   //make adaptive rect
   float width = predict_hand[1].x-predict_hand[0].x;
   float height = predict_hand[1].y-predict_hand[0].y;
   float area = width*height;
   float ratio = 1.6;
   float newWidth = sqrt(area/ratio);
   float newHeight = ratio*newWidth;

   rot_minbounding_hand[0] = cv::Point((center.x-newWidth/2), (center.y-newHeight/2));
   rot_minbounding_hand[1] = cv::Point((center.x+newWidth/2), (center.y+newHeight/2));

   cv::Rect rect;
   CoordTool::PointVec2Rect(rot_minbounding_hand, rect, rot_src.cols, rot_src.rows);
   // crop
   rot_roi = rot_src(rect);

   return (rot_roi.data)?true:false;
}

void ImageProcessor::output2FtJnt(float ftx, float fty, float jntx, float jnty, bool isDirect, bool hasAngle)
{
    if(isDirect && !hasAngle){
        //this branch is for direct using forward result as prediction
        int roi_width = roi.cols, roi_height = roi.rows;
        cv::Point tl(ftx*roi_width, fty*roi_height);
        cv::Point br(jntx*roi_width, jnty*roi_height);
        vector<cv::Point> raw_predict_finger;
        raw_predict_finger.push_back(tl);
        raw_predict_finger.push_back(br);

        predict_finger = raw_predict_finger;
        for(uint i = 0; i < raw_predict_finger.size(); i++){
          predict_finger[i].x+=predict_hand[0].x;
          predict_finger[i].y+=predict_hand[0].y;
        }
    } else if (hasAngle){
        //this branch is for rotation transform of some certain angle
        int rot_roi_width = rot_roi.cols, rot_roi_height = rot_roi.rows;
        cv::Point tl(ftx*rot_roi_width, fty*rot_roi_height);
        cv::Point br(jntx*rot_roi_width, jnty*rot_roi_height);
        vector<cv::Point> rot_raw_predict_finger;
        rot_raw_predict_finger.push_back(tl);
        rot_raw_predict_finger.push_back(br);

        rot_predict_finger = rot_raw_predict_finger;
        for(uint i = 0; i < rot_raw_predict_finger.size(); i++){
            rot_predict_finger[i].x+=rot_minbounding_hand[0].x;
            rot_predict_finger[i].y+=rot_minbounding_hand[0].y;
        }

        predict_finger.assign(2,cv::Point(0,0));
        cv::Mat rot_mat(2, 3, CV_32FC1);  //旋转矩阵
        rot_mat = cv::getRotationMatrix2D(center, predict_angle-90, 1);// reverse angle
        for(uint i = 0; i < rot_predict_finger.size(); i++){
            CoordTool::RotatePoints(rot_predict_finger[i],predict_finger[i],rot_mat);
        }

        vector<cv::Point> points(4);
        points[0] = cv::Point(rot_minbounding_hand[0].x, rot_minbounding_hand[0].y);
        points[1] = cv::Point(rot_minbounding_hand[1].x, rot_minbounding_hand[0].y);
        points[2] = cv::Point(rot_minbounding_hand[1].x, rot_minbounding_hand[1].y);
        points[3] = cv::Point(rot_minbounding_hand[0].x, rot_minbounding_hand[1].y);
        // 4 points in rotated src
        predict_hand_bounding.assign(points.size(),cv::Point(0,0));
        for(uint i=0; i<points.size(); i++){
            CoordTool::RotatePoints(points[i], predict_hand_bounding[i], rot_mat);
        }
    }
}

void ImageProcessor::showPointsOnMat(Writing& writing)
{
    camera_output = camera_input;

    int size = writing.getPointCount();
    vector<cv::Point> points = writing.getPoints();
    for(int i=0; i<size;i++){
        cv::circle(camera_output, points[i], 1, COLOR_RED, 1);
    }
    for(int i=1; i<size;i++){
        cv::line(camera_output, points[i-1], points[i], COLOR_RED, 4);
    }
    if(size>0)
        cv::circle(camera_output, points[size-1], 4, COLOR_YELLOW, 8);
}

void ImageProcessor::addUpRecognized(string str)
{
    recognized+=str;
}

void ImageProcessor::setRecognizedCdd(string str)
{
    recognizedCdd=str;
}

void ImageProcessor::attentionOffset()
{
    CoordTool::offsetPoints(predict_hand, predict_hand, track_center, SRC_SIZE);
    CoordTool::offsetPoints(predict_hand_bounding, predict_hand_bounding, track_center, SRC_SIZE);
    CoordTool::offsetPoints(predict_finger, predict_finger, track_center, SRC_SIZE);
}

void ImageProcessor::updateTracker()
{
    track_center.x = (predict_hand[0].x + predict_hand[1].x)/2;
    track_center.y = (predict_hand[0].y + predict_hand[1].y)/2;
    CoordTool::protectPointFromEdge(track_center, camera_input.cols, camera_input.rows);
}

void ImageProcessor::reInitTrackcenter()
{
    track_center.x = camera_size.width/2;
    track_center.y = camera_size.height/2;
    CoordTool::protectPointFromEdge(track_center,camera_input.cols,camera_input.rows);
}
