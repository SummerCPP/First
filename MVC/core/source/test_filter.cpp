# include "../header/segcore.hpp"
# include "opencv2/highgui/highgui.hpp"

int main() {
	cv::Mat mat = imread("F:/test/03.jpg"); 
	Gaussian_filter filter;
	cv::Mat ret =filter.GaussianImage(mat,20,5); 
	imwrite("F:/test/result.png", ret); 
}