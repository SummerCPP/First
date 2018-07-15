#include "../core/core.h"

#include <iostream>

int target::target::getStatus() {
	return this.status; 
}
int target::target::processs() {
	if (this.task == null) {
		std::cout << "the targaet is associated with an empty task, aborted! System error !";
		return -1; 
	}
	return this.task.process();
	
}

int target::task::process() {
	// play with core and update data  
}