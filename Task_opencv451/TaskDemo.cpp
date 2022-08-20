#include "function.h"

void my_Susan(cv::Mat src, cv::Mat &dst)
{
	cv::Mat gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	dst = src.clone();
	/*
	由于是类似圆形的模板，
	需要比较当前模板区域内的各个像素与模板核中心灰度值的差距。
	rx,ry,用于遍历圆形区域初始化偏移数组
	*/
	int rx[37] = 
	{
			-1,0,1,
		 -2,-1,0,1,2,
	  -3,-2,-1,0,1,2,3,
	  -3,-2,-1,0,1,2,3,
	  -3,-2,-1,0,1,2,3,
		 -2,-1,0,1,2
			-1,0,1
	};
	int ry[37] = 
	{
		-3,-3,-3,
	 -2,-2,-2,-2,-2,
  -1,-1,-1,-1,-1,-1,-1,
   0, 0, 0, 0, 0, 0, 0,
	 1,1,1,1,1,1,1,
	   2,2,2,2,2,
	     3,3,3,
	};
	cv::Mat gray_padd;
	cv::copyMakeBorder(gray, gray_padd, 3, 3, 3, 3, cv::BORDER_REFLECT);//做对称形状的扩充
	int t = 101;
	int g = 9;
	for (int i = 3; i < gray_padd.rows-3; i++)
	{
		for (int j = 3; j < gray_padd.cols-3; j++)
		{
			int num = 0;//统计个数
			for (int k = 0; k < 37; k++)
			{
				int data_k = gray_padd.at<uchar>(i + rx[k], j + ry[k]);
				int data = gray_padd.at<uchar>(i, j);
				if (abs(data_k - data) <= t) {
					num++;
				}
			}
			if (num < g){
				gray_padd.at<uchar>(i, j) = g - num;
			}
			else {
				gray_padd.at<uchar>(i, j) = 0;
			}
		}
	}
	//对领域内角点做非极大值抑制
	int x[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int y[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	for (int i = 3; i < gray_padd.rows - 3; i++)
	{
		for (int j = 3; j < gray_padd.cols - 3; j++)
		{
			int flag=0;
			for (int k = 0; k < 8; k++){
				if (gray_padd.at<uchar>(i, j) <= gray_padd.at<uchar>(i + x[k], j + y[k])) {
					flag = 1;
					break;
				}
			}

			if (flag==0) {
				//std::cout << "llll" << std::endl;
				cv::circle(dst, cv::Point(j - 3, i - 3), 3, cv::Scalar(255, 128, 225));
			}
			
		}
	}
	
}
void HarrisByNMS(cv::Mat R,cv::Size size,double maxValue)//非极大值抑制
{
	double thresh=0.1*maxValue;
	int n = size.width / 2;
	for (int i = n; i < R.rows - n; i++)
	{
		for (int j = n; j < R.cols - n; j++)
		{
			/*if (R.at<double>(i, j) < 0.1*maxValue)
			{
				R.at<double>(i, j) = 0;
				continue;
			}*/
			for (int k = i-n; k <= i+n; k++)
			{
				for (int l = j-n; l <= j+n; l++)
				{
					//小于中心像素置0
					if ((R.at<double>(k,l) <= R.at<double>(i, j)&&k!=i&&l!=j)||(R.at<double>(k,l)<thresh)) {
						R.at<double>(k, l) = 0;
					}
					
				}
			}
		}
	}
}
void my_Harris(cv::Mat src, cv::Mat &dst, cv::Size size, double k,double thresh)
{
	/*@Sobel函数
	CV_EXPORTS_W void Sobel(InputArray src, OutputArray dst, int ddepth,
		int dx, int dy, int ksize = 3,
		double scale = 1, double delta = 0,
		int borderType = BORDER_DEFAULT);
	*/
	cv::Mat R,A,B,C;
	A.create(src.size(), CV_64FC1);
	B.create(src.size(), CV_64FC1);
	C.create(src.size(), CV_64FC1);
	R.create(src.size(), CV_64FC1);//AC-B^2-k(A+C)^2==[(detM-ktrace(M))]
	cv::Mat gray_src;
	cv::cvtColor(src, gray_src, cv::COLOR_BGR2GRAY);
	dst = src.clone();
	cv::Mat grad_x, grad_y;
	cv::Sobel(gray_src, grad_x, CV_64FC1, 1, 0);//1.计算图像在X,Y方向的梯度。
	cv::Sobel(gray_src, grad_y, CV_64FC1, 0, 1);
	/*cv::imshow("梯度x", grad_x);
	cv::imshow("梯度y", grad_y);*/
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			A.at<double>(i, j) = grad_x.at<double>(i, j)*grad_x.at<double>(i, j);
			B.at<double>(i, j) = grad_x.at<double>(i, j)*grad_y.at<double>(i, j);
			C.at<double>(i, j) = grad_y.at<double>(i, j)*grad_y.at<double>(i, j);
			
		}
	}
	//A = grad_x.mul(grad_x);//2.计算两个方向梯度乘积
	//B = grad_x.mul(grad_y);
	//C = grad_y.mul(grad_y);
	cv::GaussianBlur(A, A, size, 1);
	cv::GaussianBlur(B, B, size, 1);
	cv::GaussianBlur(C, C, size, 1);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			double a = A.at<double>(i, j);
			double b = B.at<double>(i, j);
			double c = C.at<double>(i, j);
			double score = (a*c - b * b) - (k*(a + c)*(a + c));
			if (score <= thresh)
			{
				R.at<double>(i, j) = 0;
			}
			else
			{
				R.at<double>(i, j) = score;
			}
			
			 
		}
	}
	double maxValue;
	cv::minMaxLoc(R, NULL, &maxValue, NULL, NULL);
	HarrisByNMS(R,cv::Size(5,5),maxValue);
	//cv::normalize(R, R, 0, 1, cv::NORM_MINMAX);
	drawHarrisCorner(R, dst);
	R.convertTo(R, CV_8UC1);
	cv::imshow("R", R);
}
void drawHarrisCorner(cv::Mat R, cv::Mat &dst)
{
	for (int i = 0; i < R.rows; i++)
	{
		for (int j = 0; j < R.cols; j++)
		{
			if (R.at<double>(i, j) > 0)
			{
				cv::circle(dst, cv::Point(j,i), 3, cv::Scalar(255,0,0));
			}
		}
	}
}