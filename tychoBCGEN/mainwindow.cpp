#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "global.h"
#include "colormask.h"
#include "ui_colormask.h"
#include <QFileDialog>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QSize>
#include <QColor>
#include <QScrollArea>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <math.h>

QPointF point;
QPointF point_old;
QPointF point_new;

int pick_red;
int pick_green;
int pick_blue;
int colormask_counter;

bool no_image;

bool red_checked;
bool green_checked;
bool blue_checked;

int click = 0;

/*!
  Sets up the Mainwindow object
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTimer *timer = new QTimer(this);

    ui->setupUi(this);

    counter = 0;
    counter_wind_emitter = 0;
    counter_first_emitter = 0;
    red_low = 0;
    red_up = 0;
    green_low = 0;
    green_up = 0;
    blue_low = 0;
    blue_up = 0;
    value = 0;
    colormask_counter = 0;
    alpha = 90;
    alpha_emitter = 200;
    alpha_special_marking = 80;

    red_checked = true;
    green_checked = true;
    blue_checked = true;
    no_image = true;

    toCheck = red_low+red_up+green_low+green_up+blue_low+blue_up;

    final_mark_color.setRgb(Qt::black);
    final_mark_color.setAlpha(alpha);

    emitter_color_x.setRgb(255,0,0,alpha_emitter);
    emitter_color_mx.setRgb(0,0,255,alpha_emitter);
    emitter_color_y.setRgb(0,255,0,alpha_emitter);
    emitter_color_my.setRgb(100,255,200,alpha_emitter);

    //to make changes on the colormask-window received by the mainwindow
    connect(timer, SIGNAL(timeout()), this, SLOT(value_change_int()));
    timer->start(200);

    //menus
    connect(ui->actionQuit_tychoICGEN, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionLoad_Image, SIGNAL(triggered()), this, SLOT(openfile()));
    connect(ui->actionSave_Boundary, SIGNAL(triggered()), this, SLOT(savefile()));
    connect(ui->actionSave_Sound_Emitter, SIGNAL(triggered()), this, SLOT(savefile_soundemitter()));
    connect(ui->actionSave_Wind_Emitter, SIGNAL(triggered()), this, SLOT(save_wind_emitter()));
    connect(ui->actionSave_Masked_Image, SIGNAL(triggered()), this, SLOT(save_masked_image()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(open_about()));
    connect(ui->actionTutorial, SIGNAL(triggered()), this, SLOT(open_tutorial()));

    //buttons
    connect(ui->scale_to_width, SIGNAL(clicked()), this, SLOT(scale_to_width()));
    connect(ui->original, SIGNAL(clicked()), this, SLOT(scale_original()));
    connect(ui->zoom_in, SIGNAL(clicked()), this, SLOT(zoom_in()));
    connect(ui->zoom_out, SIGNAL(clicked()), this, SLOT(zoom_out()));
    connect(ui->ColorMask, SIGNAL(clicked()), this, SLOT(open_color_mask()));
    connect(ui->invertmask, SIGNAL(clicked()), this, SLOT(invert_mask()));
    connect(ui->rotate_by_90, SIGNAL(clicked()), this, SLOT(rotate_by_90()));

    //mask memo, remove and reset
    connect(ui->reset_mask, SIGNAL(clicked()), this, SLOT(reset_mask()));
    connect(ui->memo_mask, SIGNAL(clicked()), this, SLOT(memo_color_mask()));
    connect(ui->remove_mask, SIGNAL(clicked()), this, SLOT(clear_last_color_mask()));

    //windemitter
    connect(ui->windemitter, SIGNAL(clicked(bool)), this, SLOT(wind_emitter_on()));
    connect(ui->windemitter, SIGNAL(toggled(bool)), this, SLOT(wind_emitter_off()));
    connect(ui->resetwindemitter, SIGNAL(clicked()), this, SLOT(reset_wind_emitter()));

    //rescaling of the image
    connect(ui->image_width, SIGNAL(editingFinished()), this, SLOT(scale_image()));
    connect(ui->image_height, SIGNAL(editingFinished()), this, SLOT(scale_image()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
  handles the mouse move event on the image
  */
void myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    int x,y;

    x = floor(event->scenePos().x());
    y = floor(event->scenePos().y());

    point.setX(x);
    point.setY(y);
    point_new = point;
}

/*!
  Changes the size of the viewer at resizing the mainwindiw
  */
void MainWindow::resizeEvent(QResizeEvent *){

    int width = MainWindow::width()-20;
    int heigth = MainWindow::height()-200;

    ui->graphicsView->setGeometry(10,140,width, heigth);

}

/*!
  All the keypress events are defined here
  */
void MainWindow::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_E){
        zoom_in();
    }

    if (event->key() == Qt::Key_W){
        zoom_out();
    }


    if ((event->key() == 16777249)&&(ui->maksmode->isChecked()== true)){

        pick_red = qRed(image_stack::imagestack.at(0).pixel(point.toPoint()));
        pick_green = qGreen(image_stack::imagestack.at(0).pixel(point.toPoint()));
        pick_blue = qBlue(image_stack::imagestack.at(0).pixel(point.toPoint()));

        make_color_mask();

    }

    if ((event->key() == 16777249)&&(ui->clearmode->isChecked() == true)){
        //clear_pixel();
        clear_many_pixel_1();
    }

    if ((event->key() == 16777249)&&(ui->clearpixel->isChecked() == true)){
        clear_individual_pixel();
    }

    if ((event->key() == 16777249)&&(ui->maskpixel->isChecked() == true)){
        mask_invidual_pixel();
    }

    if ((event->key() == 16777249)&&(ui->maskislands->isChecked() == true)){
        mask_many_pixel_1();
    }

    if ((event->key() == 16777249)&&(ui->windemitter->isChecked() == true)){
        insert_wind_emitter();
        counter_first_emitter++;
    }
}

/*!
  checks when the colormask values are changed
  */
void MainWindow::value_change_int(){

    if (value != toCheck){
        toCheck = value;
        make_color_mask();
    }
}

/*!
  resets the mask
  */
void MainWindow::reset_mask(){

    counter = 0;
    counter_first_emitter = 0;
    counter_wind_emitter = 0;

    ui->invertmask->setEnabled(false);

    image_stack::imagestack.clear();
    image.load(file);
    image = image.convertToFormat(QImage::Format_ARGB32,Qt::AutoColor);
    image = image.mirrored(false, true);
    image_stack::imagestack.append(image);

    wind_emitter = image;
    wind_emitter_save = image;

    imagewidth = image.width();
    imageheight = image.height();

    ui->image_width->setText(QString::number(imagewidth));
    ui->image_height->setText(QString::number(imageheight));
    ui->image_depth->setText("0");

    pixmap = QPixmap::fromImage(image_stack::imagestack.at(0));
    pixmapwidth = pixmap.width();
    pixmapheight = pixmap.height();

    scene = new myscene();
    scene->addPixmap(pixmap);
    ui->reset_mask->setEnabled(true);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    ui->graphicsView->setFocus();

}

/*!
  Open the colormask window
  */

void MainWindow::open_color_mask(){

    mycolormask = new colormask;
    mycolormask->show();

}

/*!
  Opens the about window
  */
void MainWindow::open_about(){

    myabout = new about;
    myabout->show();

}

/*!
  Opens the tutorial window
  */
void MainWindow::open_tutorial(){

    mytutorial = new tutorial;
    mytutorial->show();

}


/*!
  Standard quit
  */
void MainWindow::quit()
{
    qApp->exit();
}

/*!
 Rescale the image
 */
void MainWindow::scale_image(){

    int x, y;

    x = ui->image_width->text().toInt();
    y = ui->image_width->text().toInt();

    ui->image_width->setText(QString::number(x));
    ui->image_height->setText(QString::number(y));

    image = image_stack::imagestack.last();
    image = image.scaled(x,y,Qt::KeepAspectRatio,Qt::FastTransformation);
    image_stack::imagestack.append(image);

    wind_emitter = wind_emitter.scaled(x,y,Qt::KeepAspectRatio,Qt::FastTransformation);
    wind_emitter_save = wind_emitter;

    //pixmap = QPixmap::fromImage(image_stack::imagestack.last());
    pixmap = QPixmap::fromImage(wind_emitter);
    pixmapwidth = pixmap.width();
    pixmapheight = pixmap.height();

    scene = new myscene();
    scene->addPixmap(pixmap);
    ui->reset_mask->setEnabled(true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    ui->graphicsView->setFocus();

}

/*!
 *rotate by 90 degree
 */
 void MainWindow::rotate_by_90(){

    ui->graphicsView->rotate(90);


 }
