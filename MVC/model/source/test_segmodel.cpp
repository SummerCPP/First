#include "../header/segmodel.h"
#include "opencv2/highgui.hpp"

#include <iostream>
int main() {
	segManager *seg0 = segManager::generate("F:/test/02.jpg", ALGO_GAUSSIAN_FILTER); 

	if (!seg0) {
		std::cout << "can not open file "; 
		getchar();
		return 0;
	}
	seg0->updateProcessMode(ALGO_GAUSSIAN_FILTER);
	seg0->process(); 
	cv::Mat mat = seg0->getLatestData();
	std::cout << " Hello, world !" << std::endl;
	int c; 
	cv::imwrite("F:/test/copy.jpg", mat); 

}