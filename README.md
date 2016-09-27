# EgoFinger

This repo is about a dataset called EgoFinger, which is maintained by Yichao Huang in SCUT HCII Lab. 

### Description

SCUT-Ego-Finger Dataset is for research on egocentric vision hand detection and fingertip detection. It includes 93729 frames from 24 videos captured and labeled by 24 volunteers. Detail scenes include: Avenue (4058), Basketball Field (2894), Chinese Book (3001), Classroom (4868), Computer Screen (5088), East Canteen (3738), East Lake (4151), Football Field (4145), Fountain (4158), Lcy-Lab (4084), Liwu Building (5488), NO.1 North Dorm (4281), NO3. North Dorm (4679), North Canteen (4314), North Lake (3419), North Library (2495), Renwen Building (3611), Supermarket (1682), Teaching Building (4368), Tennis Field (5124), West Canteen (4185), Wyx-Lab (3222), Yifu Building 1st Floor (3806), Yifu Building 2nd Floor (2870).

The dataset is collected for solving problem of ego-vision fingertip detection and hand detection, which may conduct challenges such as background complexity, Illumination change, hand shape and hand color diversity, motion blur, so on and forth. Therefore the dataset deliberately covers different type of frames. It is feasible to applied Deep Learning on the dataset. For further evaluation of the dataset, please visit use a tool in this repo named Performer, or contact hyichao@foxmail.com

In the repo there are three folders. The one named Collector is the tool for data labeling, executed on Windows in convienience, which is written by Qt framework with OpenCV. The one named Performer is for data evaluation, simply like spacial distribution of hand, color distribution and so on. The Application folder contains personal used demo codes #(FYI, the demo video is uploaded to Youtube<https://www.youtube.com/watch?v=PeSrRxKghv8>, please click the link or search ###Egocentric Air Writing### in Youtube#), and due to some stupid policy I have to keep the models myself and therefore the Application codes cannot run directly until caffemodels are filled.

### Install
In this repo we build the UI mainly by Qt environment and OpenCV library. So,

1. Intall OpenCV 
The easiest way might be

```
sudo apt-get install libopencv-dev python-opencv
```

2. Install Qt
Go to Qt download page<https://www.qt.io/download/> and download the ##.run## file the follow the instruction

3. Clone the repo
Using git the clone the repo

Then you may do whatever you want...except runing them :( Again, sorry for not providing caffemodel... However, hope this will help for somebody and I will be glad.

### Publication

It't not a revolutional work, though, we are proud that we do something on this topic and push the area further a little bit. 

> Y. Huang, et al. "DeepFinger: A Cascade Convolutional Neuron Network Approach to Finger Key Point Detection in Egocentric Vision with Mobile Camera." Systems, Man, and Cybernetics (SMC), 2015 IEEE International Conference on. IEEE, 2015.

----

> Y. Huang. et al. "A Pointing Gesture Based Egocentric Interaction System: Dataset, Approach and Application." Computer Vision and Pattern Recognition (CVPR) Workshop, 2016 IEEE Internaional Conference on. IEEE, 2015.
 
----

### Link
The dataset is availble in the following link (which is the data page of our lab)

<http://www.hcii-lab.net/data/SCUTEgoFinger/index.htm>

By using the dataset, we establish a demo application named Ego-Air-Writing, and the video has been uploaded to Youtube

<!--<iframe width="560" height="315" src="https://www.youtube.com/embed/PeSrRxKghv8" frameborder="0" allowfullscreen></iframe>-->
<https://www.youtube.com/embed/PeSrRxKghv8>

If you are one of the researchers interested in hand or egocentric vision, please read our paper, which will provide a straight-forward illustration of dataset, approach, and application. Or, if you need further information, please feel free to contact 


Yichao Huang:  <hyichao@foxmail.com>
