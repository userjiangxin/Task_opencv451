#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/core.hpp>

void my_Susan(cv::Mat src, cv::Mat &dst);//自己实现的SUSAN角点检测
void HarrisByNMS(cv::Mat R,cv::Size size,double maxValue);//harris极大值抑制
void my_Harris(cv::Mat src,cv::Mat &dst,cv::Size size,double k,double thresh);//自己实现的Harris角点检测
void drawHarrisCorner(cv::Mat R, cv::Mat &dst);//绘制Harris角点



