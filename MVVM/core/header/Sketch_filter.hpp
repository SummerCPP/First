//
//  Sketch_filter.hpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/19.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#ifndef Sketch_filter_hpp
#define Sketch_filter_hpp

#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
class Sketch_filter{
public:
    Sketch_filter(){};
    ~Sketch_filter(){};
    Mat SketchImage(Mat srcImage);
};
#endif /* Sketch_filter_hpp */
