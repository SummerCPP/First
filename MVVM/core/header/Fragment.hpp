//
//  Fragment_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/20.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Fragment_filter_hpp
#define Fragment_filter_hpp

#include <stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;
enum{ Up, Down, Right, Left }Direction;

class Fragment_filter{
public:
    Fragment_filter(){}
    ~Fragment_filter(){}
    Mat FragmentImage( Mat imge ,   int Offset );
    Mat shift( Mat imge , int dir , int offset );
};
#endif /* Fragment_filter_hpp */
