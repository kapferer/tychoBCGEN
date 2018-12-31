/*!
Setting up a wind-emitter
*/

#include "myscene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "image_stack.h"
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QRgb>
#include <QColor>

void MainWindow::wind_emitter_on(){

    ui->xdir->setEnabled(true);
    ui->ydir->setEnabled(true);
    ui->mxdir->setEnabled(true);
    ui->mydir->setEnabled(true);

    ui->resetwindemitter->setEnabled(true);

    ui->xdir->setChecked(true);

}

void MainWindow::wind_emitter_off(){

    ui->xdir->setChecked(true);
    ui->mxdir->setChecked(false);
    ui->ydir->setChecked(false);
    ui->mydir->setChecked(false);

    ui->xdir->setDisabled(true);
    ui->ydir->setDisabled(true);
    ui->mxdir->setDisabled(true);
    ui->mydir->setDisabled(true);

    ui->resetwindemitter->setDisabled(true);

}



void MainWindow::insert_wind_emitter(){


    if (no_image == false){

        int i;
        int j;

        i = 0;
        j = 0;

        counter_wind_emitter++;

        if (counter_wind_emitter == 1) point1 = point;
        if (counter_wind_emitter == 2){
            point2 = point;

            if (point1.y() < point2.y()){

                if (ui->xdir->isChecked() == true){


                    for (j = point1.toPoint().y(); j < point2.toPoint().y(); j++){
                        i = point1.toPoint().x();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i+1,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i-1,j) !=final_mark_color.rgba())){
                            wind_emitter.setPixel(i,j, emitter_color_x.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_x.rgba());
                        }
                    }
                }

                if (ui->mxdir->isChecked() == true){


                    for (j = point1.toPoint().y(); j < point2.toPoint().y(); j++){
                        i = point1.toPoint().x();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i+1,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i-1,j) !=final_mark_color.rgba())){
                            wind_emitter.setPixel(i,j, emitter_color_mx.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_mx.rgba());
                        }
                    }
                }
            }
            else{
                if (ui->xdir->isChecked() == true){


                    for (j = point2.toPoint().y(); j < point1.toPoint().y(); j++){
                        i = point2.toPoint().x();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i+1,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i-1,j) !=final_mark_color.rgba())) {
                            wind_emitter.setPixel(i,j, emitter_color_x.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_x.rgba());
                        }
                    }
                }

                if (ui->mxdir->isChecked() == true){


                    for (j = point2.toPoint().y(); j < point1.toPoint().y(); j++){
                        i = point2.toPoint().x();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i+1,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i-1,j) !=final_mark_color.rgba())){
                            wind_emitter.setPixel(i,j, emitter_color_mx.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_mx.rgba());
                        }
                    }
                }


            }

            if (point1.x() < point2.x()){
                if (ui->ydir->isChecked() == true){


                    for (i = point1.toPoint().x(); i < point2.toPoint().x(); i++){
                        j = point1.toPoint().y();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j+1) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j-1) !=final_mark_color.rgba())) {
                            wind_emitter.setPixel(i,j, emitter_color_y.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_y.rgba());
                        }
                    }
                }

                if (ui->mydir->isChecked() == true){


                    for (i = point1.toPoint().x(); i < point2.toPoint().x(); i++){
                        j = point1.toPoint().y();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j+1) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j-1) !=final_mark_color.rgba())){
                            wind_emitter.setPixel(i,j, emitter_color_my.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_my.rgba());
                        }
                    }
                }
            }
            else{
                if (ui->ydir->isChecked() == true){

                    for (i = point2.toPoint().x(); i < point1.toPoint().x(); i++){
                        j = point2.toPoint().y();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j+1) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j-1) !=final_mark_color.rgba())) {
                            wind_emitter.setPixel(i,j, emitter_color_y.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_y.rgba());
                        }
                    }
                }

                if (ui->mydir->isChecked() == true){

                    for (i = point2.toPoint().x(); i < point1.toPoint().x(); i++){
                        j = point2.toPoint().y();
                        if ((wind_emitter.pixel(i,j) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j+1) !=final_mark_color.rgba())&&
                                (wind_emitter.pixel(i,j-1) !=final_mark_color.rgba())) {
                            wind_emitter.setPixel(i,j, emitter_color_my.rgba());
                            wind_emitter_save.setPixel(i,j, emitter_color_my.rgba());
                        }
                    }
                }

            }


            counter_wind_emitter = 0;

        }


        scene->clear();
        pixmap = QPixmap::fromImage(wind_emitter);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();
    }
}




void MainWindow::reset_wind_emitter(){


    if (no_image == false){
        wind_emitter = image;
        wind_emitter_save = image;

        scene->clear();
        pixmap = QPixmap::fromImage(wind_emitter);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();

    }
}




















