#ifndef COLORMASK_H
#define COLORMASK_H

#include <QDialog>
#include <QEvent>
#include "image_stack.h"
#include "global.h"

namespace Ui {
class colormask;
}

class colormask : public QDialog, public image_stack
{
    Q_OBJECT
    
public:
    explicit colormask(QWidget *parent = 0);
    ~colormask();

private:
    Ui::colormask *ui;

public slots:
    void make_color_mask_action();
    void update_color_mask_parameter();
    void set_color_sliders();
    void set_color_spin_boxes();
    void enable_checkbox_red();
    void enable_checkbox_green();
    void enable_checkbox_blue();
    void close_color_mask_window();



};

#endif // COLORMASK_H
