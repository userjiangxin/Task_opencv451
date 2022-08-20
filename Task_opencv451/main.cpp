#include "function.h"


int main()
{
	cv::Mat src = cv::imread("D:/opencv/pictures/tangle.tif");
	cv::Mat gray;
	//cv::Mat t = cv::imread("D:/opencv/pictures/shuiyin.jpg");
	//src.convertTo(src, CV_32FC1);
	//cv::Mat imageROI;
	/*imageROI = src(cv::Rect(10, 10, t.cols, t.rows));
	for (int i = 0; i < t.rows; i++)
	{
		for (int j = 0; j < t.cols; j++)
		{
			imageROI.at<cv::Vec3b>(i, j) = imageROI.at<cv::Vec3b>(i, j)/4 + t.at<cv::Vec3b>(i, j)/64;
		}
	}*/
	//cv::dct(src,imageROI);
	//cv::Mat res = src - src1;
	//t.copyTo(imageROI);
	//cv::namedWindow("result");
	//cv::imshow("result",imageROI);
	//cv::imshow("res", res);
	/*if (src.empty())
	{
		std::cout << "cannot load image" << std::endl;
	}*/
	cv::Mat dst;
	//cv::imshow("res", res);
	my_Susan(src, dst);
	imshow("dst", dst);
	//my_Harris(src, dst,cv::Size(3,3),0.04,0.1);
	//imshow("dst", dst);
	
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}