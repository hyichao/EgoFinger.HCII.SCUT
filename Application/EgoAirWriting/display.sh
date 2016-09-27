#! /usr/bin/env sh 

## $1: camera $2: GPU

CAP_ID=0
GPU_ID=0

if [ $# -ge 1 ]
then
	CAP_ID=$1
fi

if [ $# -ge 2 ] 
then 
	GPU_ID=$2
fi

# get current directory by pwd
CURRENT_DIR=${PWD}
echo "---"
echo "Current directory: ${CURRENT_DIR}"
echo "    ${CURRENT_DIR}"

CAFFE_ROOT=${CURRENT_DIR}/caffe-msra-demo
echo "---"
echo "Therefore the caffe root should be:"
echo "    ${CAFFE_ROOT}"

UI_EXECUTABLE_DIR=${CURRENT_DIR}/build
echo "---"
echo "As for UI, the path is:"
echo "   ${UI_EXECUTABLE_DIR}"

# PARAM=./parameters6-1
PARAM=${CAFFE_ROOT}/examples/deep_airwriting/parameters7-angle

 ${UI_EXECUTABLE_DIR}/EgoAirWriting \
	$PARAM/caffenet_hand.caffemodel \
	$PARAM/deploy_hand.prototxt \
	fc8_all \
	$PARAM/caffenet_finger_200000.caffemodel \
	$PARAM/deploy_finger.prototxt \
	fc8 \
	GPU \
 	$GPU_ID \
 	$CAP_ID   

#for qt creator arguments
# /home/charlie/EgoFinger.HCII.SCUT/Application/caffe-msra-demo/examples/deep_airwriting/parameters7-angle/caffenet_hand.caffemodel /home/charlie/EgoFinger.HCII.SCUT/Application/caffe-msra-demo/examples/deep_airwriting/parameters7-angle/deploy_hand.prototxt fc8_all /home/charlie/EgoFinger.HCII.SCUT/Application/caffe-msra-demo/examples/deep_airwriting/parameters7-angle/caffenet_finger_200000.caffemodel /home/charlie/EgoFinger.HCII.SCUT/Application/caffe-msra-demo/examples/deep_airwriting/parameters7-angle/deploy_finger.prototxt fc8 GPU 0 0   

