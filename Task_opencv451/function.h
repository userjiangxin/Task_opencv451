#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/core.hpp>

void my_Susan(cv::Mat src, cv::Mat &dst);//�Լ�ʵ�ֵ�SUSAN�ǵ���
void HarrisByNMS(cv::Mat R,cv::Size size,double maxValue);//harris����ֵ����
void my_Harris(cv::Mat src,cv::Mat &dst,cv::Size size,double k,double thresh);//�Լ�ʵ�ֵ�Harris�ǵ���
void drawHarrisCorner(cv::Mat R, cv::Mat &dst);//����Harris�ǵ�



