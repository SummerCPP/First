#include "segtarget.h"
#include <iostream>

class segTarget {
public:
    static segTarget* generate(const char* filepath, int processmode);

private :
    segTarget();
    ~segTarget();
};
