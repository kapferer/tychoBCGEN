#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myscene.h"
#include "colormask.h"
#include "about.h"
#include "tutorial.h"
#include "image_stack.h"
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public image_stack
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPixmap pixmap;
    QVector<QPoint> emitter_points;
    myscene *scene;
    colormask *mycolormask;
    tutorial *mytutorial;
    about *myabout;
    QString file;
    QString file_save;
    QString file_masked_image_save;
    QPointF point1, point2;
    QColor final_mark_color;
    QColor emitter_color_x;
    QColor emitter_color_mx;
    QColor emitter_color_y;
    QColor emitter_color_my;

    int imagewidth;
    int imageheight;
    int pixmapwidth;
    int pixmapheight;
    int maskwidth;
    int counter;
    int counter_wind_emitter;
    int counter_first_emitter;
    int toCheck;
    int alpha;
    int alpha_special_marking;
    int alpha_emitter;
    bool mousebutton_pressed;

    void mask_pixmap();
    void undo_mask_pixmap();
    void make_color_mask();
    void clear_many_pixel();
    void clear_many_pixel_1();
    void mask_many_pixel();
    void mask_many_pixel_1();
    void clear_individual_pixel();
    void mask_invidual_pixel();
    void insert_wind_emitter();



private:
    Ui::MainWindow *ui;


protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void openfile();
    void scale_to_width();
    void scale_original();
    void zoom_in();
    void zoom_out();
    void memo_color_mask();
    void clear_last_color_mask();
    void open_color_mask();
    void quit();
    void value_change_int();
    void reset_mask();
    void savefile();
    void savefile_soundemitter();
    void save_wind_emitter();
    void save_masked_image();
    void invert_mask();
    void open_about();
    void open_tutorial();
    void wind_emitter_on();
    void wind_emitter_off();
    void reset_wind_emitter();
    void scale_image();
    void rotate_by_90();


};

#endif // MAINWINDOW_H
