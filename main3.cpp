
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
using namespace std;
int main()
{
    cv::Mat img=cv::imread("/Users/shenyeqing/Documents/shenyeqing-mini.png",cv::IMREAD_COLOR);
    // cv::Mat img_f;
    // img.convertTo(img_f,cv::CV_32F);
    // img.convertTo(img_f, CV_32F);
    cv::Mat gray;
    gray.create(img.size(),CV_8U);
    for(int i=0;i<img.rows;i++){
        const cv::Vec3b* inData=img.ptr<cv::Vec3b>(i);
        uchar* outData=gray.ptr<uchar>(i); 
        for(int j=0;j<img.cols;j++){
            cv::Vec3b bgr=inData[j];
            outData[j]=(bgr[0]+bgr[1]+bgr[2])/3;
        }
    }
    cv::imshow("BGR",gray);
    cv::waitKey(0);
    return 0;
}
