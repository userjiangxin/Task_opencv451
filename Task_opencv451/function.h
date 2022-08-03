#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/core.hpp>

void my_Susan(cv::Mat src, cv::Mat &dst);
void HarrisByNMS(cv::Mat R,cv::Size size,double maxValue);//极大值抑制
void my_Harris(cv::Mat src,cv::Mat &dst,cv::Size size,double k,double thresh);
void drawHarrisCorner(cv::Mat R, cv::Mat &dst);



