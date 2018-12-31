#ifndef IMAGE_STACK_H
#define IMAGE_STACK_H

#include <QImage>

class image_stack{

public:

    QVector<QImage> imagestack;
    QImage image;
    QImage image1;

    QImage wind_emitter;
    QImage wind_emitter_save;

};

#endif // IMAGE_STACK_H
