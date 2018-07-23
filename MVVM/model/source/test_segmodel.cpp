#ifdef _TEST_
#include "segmodel.h"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
int main() {
	segModel model;
	model.setupModel("./data/test.png");
	std::cout << model.getStatus() << " \n" ;
	getchar(); 
	getchar();  
	model.saveModel("./data/new1.jpg");
	getchar();
	getchar();
	model.gsfilter(10,10);
	model.saveModel("./data/new2.jpg");
	getchar();
	getchar();
	model.gsfilter(100, 20);
	model.saveModel("./data/new3.jpg");
}
#endif
