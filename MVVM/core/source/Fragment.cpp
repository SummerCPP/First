//
//  Fragment_filter.cpp
//  ProjectOpenCV
//
//  Created by Jeanne Mystery on 2018/7/20.
//  Copyright © 2018年 Jeanne Mystery. All rights reserved.
//

#include "Fragment.hpp"
#include<opencv2/opencv.hpp>

Mat Fragment_filter::FragmentImage( Mat imge , int Offset ){
    Mat imgeW = shift(imge,Up,Offset);
    Mat imgeS = shift(imge,Down,Offset);
    Mat imgeA = shift(imge,Left,Offset);
    Mat imgeD = shift(imge,Right,Offset);
    Mat finalImage = (imgeW + imgeA + imgeD + imgeS) / 4;
    return finalImage;
}

Mat Fragment_filter::shift( Mat imge , int dir , int offset ){
    Mat finalImage;
    const int rows = imge.rows;
    const int cols = imge.cols;
    finalImage.create(rows, cols, imge.type());
    
    Vec3b *p;
    for ( int i = 0 ; i < rows ; i ++ ){
        p = finalImage.ptr<Vec3b>(i);
        for( int j = 0 ; j < cols ; j ++ ){
            int x = j;
            int y = i;
            switch(dir){
                case Up:
                    y += offset;
                    break;
                case Down:
                    y -= offset;
                    break;
                case Left:
                    x -= offset;
                    break;
                case Right:
                    x += offset;
                    break;
                default:
                    break;
            }
            if( x >= 0 && y >= 0 && x < cols && y < rows ){
                p[j] = imge.ptr<Vec3b>(y)[x];
            }
        }
    }
    return finalImage;
}
