
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
int main()
{
    cv::VideoCapture capVideo;
    cv::Mat frame;
    capVideo.open("/Users/shenyeqing/Documents/file/video/北大交流剪辑/syq.mp4");
    if(!capVideo.isOpened()){
        std::cout<<"not open"<<endl;
        return -1;
    }
    while (true){
        capVideo>>frame;
        if (!frame.empty()){
            imshow("CarsDrivingUnderBridge", frame);
        }
        else{
            break;
        }
        if (char(cv::waitKey(1)) == 'q'){
            break;
        }
    }
    capVideo.release();
    return 0;


}
