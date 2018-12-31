#ifndef GLOBAL_H
#define GLOBAL_H
#include <QPoint>

extern QPointF point;
extern QPointF point_old;
extern QPointF point_new;
extern int pick_red;
extern int pick_green;
extern int pick_blue;
extern int colormask_counter;
extern int red_low;
extern int red_up;
extern int green_low;
extern int green_up;
extern int blue_low;
extern int blue_up;
extern int value;

extern bool red_checked;
extern bool green_checked;
extern bool blue_checked;
extern bool no_image;

#endif // GLOBAL_H
