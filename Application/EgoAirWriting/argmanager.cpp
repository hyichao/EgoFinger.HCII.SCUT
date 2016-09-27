#include "argmanager.h"

ArgManager::ArgManager()
{

}

ArgManager::~ArgManager()
{

}

void ArgManager::init(int argc, char** argv)
{
    if(!check(argc,argv))
        return;

    if(!hasInit){
        ::google::InitGoogleLogging(argv[0]);
        hasInit=true;
    }
    pretrained_binary_proto_hand = argv[1];
    feature_extraction_proto_hand = argv[2];
    blob_name_hand = argv[3];
    pretrained_binary_proto_finger = argv[4];
    feature_extraction_proto_finger = argv[5];
    blob_name_finger = argv[6];
    device = argv[7];
    device_id = atoi(argv[8]);
    camera_id = atoi(argv[9]);
}

bool ArgManager::check(int argc, char** argv)
{
    const int num_required_args = 1+9;
    qDebug()<<"current argc: "<<argc;
    if (argc != num_required_args) {
      qDebug()<<
      "  Usage: extract_features  \n"
      "  1.pretrained_net_param_hand \n"
      "  2.feature_extraction_proto_file_hand \n"
      "  3.extract_feature_blob_name_hand \n"
      "  4.pretrained_net_param_finger   \n"
      "  5.feature_extraction_proto_file_finger \n"
      "  6.extract_feature_blob_name_finger \n"
      "  7.[CPU/GPU] \n"
      "  8.[DEVICE_ID=0] \n"
      "  9.[CAMERA_ID=0] \n";
      return false;
    }
    return true;
}

//move out from CAFFE
void ArgManager::log_argv()
{
    // log and check
    qDebug() << " pretrained_binary_proto_hand = " + QString::fromStdString(pretrained_binary_proto_hand);
    qDebug() << " feature_extraction_proto_hand = "+ QString::fromStdString(feature_extraction_proto_hand);
    qDebug() << " blob_name_hand = " + QString::fromStdString(blob_name_hand);
    qDebug() << " pretrained_binary_proto_finger = " + QString::fromStdString(pretrained_binary_proto_finger);
    qDebug() << " feature_extraction_proto_finger = " + QString::fromStdString(feature_extraction_proto_finger);
    qDebug() << " blob_name_finger = " + QString::fromStdString(blob_name_finger);
    qDebug() << " device = " + QString::fromStdString(device)+" device_id = " << device_id;
    qDebug() << " camera = " << camera_id;
}

//move out from CAFFE
void ArgManager::set_gpu_device()
{
    if (strcmp(device.c_str(), "GPU") == 0) {
      qDebug()<< "Using GPU";
      CHECK_GE(device_id, 0);
      qDebug() << "Using Device_id=" << device_id;
      Caffe::SetDevice(device_id);
      Caffe::set_mode(Caffe::GPU);
    } else {
      qDebug() << "Using CPU";
      Caffe::set_mode(Caffe::CPU);
    }
}

string ArgManager::get_hand_caffemodel()
{
    return pretrained_binary_proto_hand;
}

string ArgManager::get_hand_proto()
{
    return feature_extraction_proto_hand;
}

string ArgManager::get_hand_blob()
{
    return blob_name_hand;
}

string ArgManager::get_finger_caffemodel()
{
    return pretrained_binary_proto_finger;
}

string ArgManager::get_finger_proto()
{
    return feature_extraction_proto_finger;
}

string ArgManager::get_finger_blob()
{
    return blob_name_finger;
}

int ArgManager::get_camera_id()
{
    return camera_id;
}
