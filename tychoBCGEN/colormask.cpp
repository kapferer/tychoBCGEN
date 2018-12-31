/*!
  The colormaks window, which allows you to set the color ranges
  with sliders or in textfields
  */
#include "myscene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colormask.h"
#include "ui_colormask.h"
#include "global.h"
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
#include <QRgb>
#include <QTimer>

int red_low;
int red_up;
int green_low;
int green_up;
int blue_low;
int blue_up;
int value;

colormask::colormask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::colormask)
{
    QTimer *timer = new QTimer(this);
    ui->setupUi(this);

    connect(ui->close, SIGNAL(clicked()), this, SLOT(close_color_mask_window()));
    connect(timer, SIGNAL(timeout()), this, SLOT(make_color_mask_action()));
    timer->start(200);

    //colormask sliders and spinboxes
    connect(ui->red_low, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));
    connect(ui->green_low, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));
    connect(ui->blue_low, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));

    connect(ui->red_low_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));
    connect(ui->green_low_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));
    connect(ui->blue_low_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));

    connect(ui->red_up, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));
    connect(ui->green_up, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));
    connect(ui->blue_up, SIGNAL(valueChanged(int)), this, SLOT(set_color_sliders()));

    connect(ui->red_up_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));
    connect(ui->green_up_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));
    connect(ui->blue_up_2, SIGNAL(valueChanged(int)), this, SLOT(set_color_spin_boxes()));

    connect(ui->red_checkbox, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_red()));
    connect(ui->green_checkbox, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_green()));
    connect(ui->blue_checkbox, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_blue()));

}

colormask::~colormask()
{
    delete ui;
}

void colormask::make_color_mask_action(){

    ui->redvalue->setText(QString::number(pick_red));
    ui->greenvalue->setText(QString::number(pick_green));
    ui->bluevalue->setText(QString::number(pick_blue));

    ui->red_low->setRange(0,pick_red);
    ui->green_low->setRange(0,pick_green);
    ui->blue_low->setRange(0,pick_blue);

    ui->red_up->setRange(0,255-pick_red);
    ui->green_up->setRange(0,255-pick_green);
    ui->blue_up->setRange(0,255-pick_blue);

}

void colormask::update_color_mask_parameter(){

    red_low = ui->red_low->value();
    red_up = ui->red_up->value();
    green_low = ui->green_low->value();
    green_up = ui->green_up->value();
    blue_low = ui->blue_low->value();
    blue_up = ui->blue_up->value();
    value = red_low+red_up+green_low+green_up+blue_low+blue_up;

    colormask_counter++;
}

void colormask::set_color_sliders(){

    ui->red_low_2->setValue(ui->red_low->value());
    ui->green_low_2->setValue(ui->green_low->value());
    ui->blue_low_2->setValue(ui->blue_low->value());

    if (ui->red_checkbox->isChecked()){
        ui->red_up_2->setValue(ui->red_low->value());
        ui->red_up->setDisabled(true);
    }
    else{
        ui->red_up_2->setValue(ui->red_up->value());
        ui->red_up->setEnabled(true);
    }
    if (ui->green_checkbox->isChecked()){
        ui->green_up_2->setValue(ui->green_low->value());
        ui->green_up->setDisabled(true);
    }
    else{
        ui->green_up_2->setValue(ui->green_up->value());
        ui->green_up->setEnabled(true);
    }
    if (ui->blue_checkbox->isChecked()){
        ui->blue_up_2->setValue(ui->blue_low->value());
        ui->blue_up->setDisabled(true);
    }
    else{
        ui->blue_up_2->setValue(ui->blue_up->value());
        ui->blue_up->setEnabled(true);
    }

    update_color_mask_parameter();
}

void colormask::set_color_spin_boxes(){

    ui->red_low->setValue(ui->red_low_2->value());
    ui->green_low->setValue(ui->green_low_2->value());
    ui->blue_low->setValue(ui->blue_low_2->value());


    ui->red_up->setValue(ui->red_up_2->value());
    ui->green_up->setValue(ui->green_up_2->value());
    ui->blue_up->setValue(ui->blue_up_2->value());

    update_color_mask_parameter();
}

void colormask::enable_checkbox_red(){
    if (ui->red_checkbox->isChecked()){
        ui->red_up_2->setValue(ui->red_low->value());
        ui->red_up_2->setDisabled(true);
        ui->red_up->setValue(ui->red_low->value());
        ui->red_up->setDisabled(true);
        red_checked = true;
    }
    else{
        ui->red_up_2->setEnabled(true);
        ui->red_up->setEnabled(true);
        red_checked = false;
    }
    update_color_mask_parameter();
}

void colormask::enable_checkbox_green(){
    if (ui->green_checkbox->isChecked()){
        ui->green_up_2->setValue(ui->green_low->value());
        ui->green_up_2->setDisabled(true);
        ui->green_up->setValue(ui->green_low->value());
        ui->green_up->setDisabled(true);
        green_checked = true;
    }
    else{
        ui->green_up_2->setEnabled(true);
        ui->green_up->setEnabled(true);
        green_checked = false;
    }
    update_color_mask_parameter();
}

void colormask::enable_checkbox_blue(){
    if (ui->blue_checkbox->isChecked()){
        ui->blue_up_2->setValue(ui->blue_low->value());
        ui->blue_up_2->setDisabled(true);
        ui->blue_up->setValue(ui->blue_low->value());
        ui->blue_up->setDisabled(true);
        blue_checked = true;
    }
    else{
        ui->blue_up_2->setEnabled(true);
        ui->blue_up->setEnabled(true);
        blue_checked = false;
    }
    update_color_mask_parameter();
}

void colormask::close_color_mask_window(){
    this->close();
}
