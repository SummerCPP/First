#include <iostream>
#include "target.h"

#define TASK_GAUSSIAN_FILTER 1; 
#define TASK_OTHERS 2 ;

class target {

public:
	static const int TARGET_STATUS_DONE = 1; 
	static const int TARGET_STATUS_NOT_DONE = 2; 

	task task_info; 

    target(string io_info, int task_code) {
		std::cout << "target initiailization" << std::endl; 
		this.task_info.setIOinfo(); 
		this.task_info.setIOinfo();
	}

	/*interface, for view and controller */
private :
	int target_status = TARGET_STATUS_NOT_DONE;
	
	/*function part*/
	int process(); 
	int getStatus(); 
};


class IOinfo {
public : 
	string file_path; 
	IOinfo(string path) {
		file_path = path;
	}
};

class task {
public :
	string description;
	IOinfo *io_info; 
	int task_code; 
	task(int code , string io_) {
		std::cout << "task initialization! " << std::endl;
		task_code = code;
		io_info = new IOinfo(io_); 
	}
	
	int process() noexcept;
};

class data {
public :
	//data communicated <model, view>
};

int main() {
	puts("unit test : target");
}
