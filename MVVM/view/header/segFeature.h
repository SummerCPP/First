//用于封装图像统计特征的模型
#ifndef VIEW_GSFILTER_H
#define VIEW_GSFILTER_H

#include <QWidget>

class segFeature: public QWidget
{
    Q_OBJECT
public:
    segFeature();
    segFeature(const segFeature&);
    ~segFeature();
};

#endif // GSFILTER_H
