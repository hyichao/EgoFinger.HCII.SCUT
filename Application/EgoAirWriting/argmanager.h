#ifndef ARG_MANAGER_H
#define ARG_MANAGER_H

#include "common.h"

class ArgManager
{
public:
    ArgManager();
    ~ArgManager();

    void init(int argc, char** argv);
    bool check(int argc, char** argv);

    void log_argv();
    void set_gpu_device();

    string get_hand_caffemodel();
    string get_hand_proto();
    string get_hand_blob();
    string get_finger_caffemodel();
    string get_finger_proto();
    string get_finger_blob();
    int get_camera_id();

private:
    bool hasInit;

    string pretrained_binary_proto_hand;
    string feature_extraction_proto_hand;
    string blob_name_hand;
    string pretrained_binary_proto_finger;
    string feature_extraction_proto_finger;
    string blob_name_finger;
    string device;
    int device_id;
    int camera_id;
};

#endif // ARG_MANAGER_H
