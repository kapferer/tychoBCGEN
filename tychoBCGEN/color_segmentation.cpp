/*!
  This is tychoICGEN - color segmentation file.
  The core is a maksing of pixels in the same
  color-range.
  */
#include "myscene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "image_stack.h"
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
#include <QRgb>
#include <math.h>

/*!
  Masks the pixels in the given color range.
  */
void MainWindow::make_color_mask(){

    if (no_image == false){

        image = image_stack::imagestack.last();

        for (int i = 0; i < image.width(); i++){
            for (int j = 0; j < image.height(); j++){

                if ((qRed(image_stack::imagestack.at(0).pixel(i,j)) >= pick_red - red_low)&&(qRed(image_stack::imagestack.at(0).pixel(i,j)) <= pick_red + red_up)
                        &&(qGreen(image_stack::imagestack.at(0).pixel(i,j)) >= pick_green - green_low)&&(qGreen(image_stack::imagestack.at(0).pixel(i,j)) <= pick_green + green_up)
                        &&(qBlue(image_stack::imagestack.at(0).pixel(i,j)) >= pick_blue - blue_low)&&(qBlue(image_stack::imagestack.at(0).pixel(i,j)) <= pick_blue + blue_up)){

                    image.setPixel(i,j,final_mark_color.rgba());
                }
            }
        }

        image_stack::imagestack.append(image);

        wind_emitter = image;

        scene->clear();
        pixmap = QPixmap::fromImage(image_stack::imagestack.last());
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();
    }
}

/*!
  A maks is put on the mask-stack
  */
void MainWindow::memo_color_mask(){

    image_stack::imagestack.append(image);

    scene->clear();
    pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    ui->graphicsView->setFocus();

    //now we can enable mask inverter
    ui->invertmask->setEnabled(true);

    counter++;

}

/*!
  Deletes the last image in the stack
  */
void MainWindow::clear_last_color_mask(){

    if (image_stack::imagestack.size() > 1){
        image = image_stack::imagestack.at(image_stack::imagestack.size()-2);
        wind_emitter = image;
        image_stack::imagestack.pop_back();
        scene->clear();
        pixmap = QPixmap::fromImage(image);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();
    }
}

/*!
  Clears indiviudal pixels
  */
void MainWindow::clear_individual_pixel(){

    if (no_image == false){
        QColor tmp;
        tmp = image_stack::imagestack.at(0).pixel(point.toPoint());
        image.setPixel(point.toPoint(), tmp.rgba());

        scene->clear();
        pixmap = QPixmap::fromImage(image);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();
    }
}
/*!
  Clears islands in the mask
  */
void MainWindow::clear_many_pixel_1(){

    int boundarypixel[6];
    QImage image_tmp_clear;
    QColor special_color_for_marking;
    bool stop;
    bool stop_inner_while;
    bool on;
    int i;
    int n;
    int x;
    int y;
    int k;
    int start_x;
    int start_y;
    int zero_decision;
    int row_counter;
    int break_condition;

    stop = false;
    stop_inner_while = false;
    on = false;
    i = 0;
    n = 0;
    x = 0;
    y = 0;
    k = 0;
    start_x = 1;
    start_y = 0;
    zero_decision = 0;
    row_counter = 0;
    break_condition = 0;

    for (n = 0; n < 6; n++) boundarypixel[n] = 0;

    special_color_for_marking.setAlpha(alpha_special_marking);
    image_tmp_clear = image;

    if ((point.toPoint().x() >= 0)&&(point.toPoint().x()<image.width())
            &&(point.toPoint().y() >= 0)
            &&(point.toPoint().y()<image.height())
            && (qAlpha(image.pixel(point.toPoint().x(),point.toPoint().y()))) ==  alpha){

        while (stop == false){
            //first we go out of the whole in the mask
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y())) ==  alpha) {
                if (point.toPoint().x() + i < image.width() - 1){
                    i++;
                }
                else{
                    //This is no island in the mask, we stop this procedure here
                    stop = true;
                    break;
                }
            }
            else
            {
                //The first pixel in the boundary is found.
                //If boundary is not a mask point the vluse 1 in the vector at the highlighted place
                //| |2| |
                //|1|x|3|
                //| |4| |
                //1 - boundarypixel[2]
                //2 - boundarypixel[3]
                //3 - boundarypixel[4]
                //4 - boundarypixel[5]

                x = point.toPoint().x() + i;
                y = point.toPoint().y();

                start_x = x;
                start_y = y;

                //now lets walk counter-clockwise in the domain along the boundary
                while (stop_inner_while == false){

                    if (qAlpha(image.pixel(x - 1, y + 0)) == alpha){
                        boundarypixel[2] = 1;
                    }
                    else{
                        boundarypixel[2] = 0;
                    }
                    if (qAlpha(image.pixel(x + 0, y + 1)) == alpha){
                        boundarypixel[3] = 1;
                    }
                    else{
                        boundarypixel[3] = 0;
                    }
                    if (qAlpha(image.pixel(x + 1, y - 0)) == alpha){
                        boundarypixel[4] = 1;
                    }
                    else{
                        boundarypixel[4] = 0;
                    }
                    if (qAlpha(image.pixel(x + 0, y - 1)) == alpha){
                        boundarypixel[5] = 1;
                    }
                    else{
                        boundarypixel[5] = 0;
                    }
                    //now lets decide the next point
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        if (zero_decision == 2) x--;
                        if (zero_decision == 3) y++;
                        if (zero_decision == 4) x++;
                        if (zero_decision == 5) y--;
                        if (zero_decision == 6) x--;
                        if (zero_decision == 7) x--;
                        if (zero_decision == 8) y--;
                        if (zero_decision == 9) y++;
                        if (zero_decision == 10) y++;
                        if (zero_decision == 11) x++;
                        if (zero_decision == 12) x--;
                        if (zero_decision == 13) y--;
                        if (zero_decision == 14) x++;
                        if (zero_decision == 15) y++;

                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 2;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        x--;
                        zero_decision = 3;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y++;
                        zero_decision = 4;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 5;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 6;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 7;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 8;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        x--;
                        zero_decision = 9;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x--;
                        zero_decision = 10;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        y++;
                        zero_decision = 11;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 12;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 13;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        y++;
                        zero_decision = 14;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        x--;
                        zero_decision = 15;
                    }

                    for (n = 0; n < 6; n++) boundarypixel[n] = 0;

                    if ((x<0)||(y>image.width())) break;

                    break_condition++;

                    image_tmp_clear.setPixel(x,y,special_color_for_marking.rgba());

                    if (break_condition == image.width()*image.height()) stop_inner_while = true;
                    if ((x == start_x)&&(y == start_y)) stop_inner_while = true;

                }
                stop = true;
            }
        }
    }


    if ((x == start_x)&&(y == start_y)){
        //Now we make a first check through the image to search for the numbers of the special_mark_color in a row
        //for a further changes
        for (n = 0; n < image.height(); n++){

            for (k = 0; k < image.width(); k++){
                if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()){
                    row_counter++;
                }

            }
            //Now change the marking starting and stopping at the special_mark_color
            on = false;

            if (row_counter > 1){
                for (k = 0; k < image.width(); k++){

                    if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()) row_counter--;

                    if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()) on = false;

                    if ((image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba())&&
                            (image_tmp_clear.pixel(k+1,n) != special_color_for_marking.rgba()))
                    {
                        if (on == false){
                            on = true;
                        }
                        else{
                            on = false;
                        }
                    }
                    if (row_counter == 0) on = false;
                    if (on == true) image.setPixel(k+1,n,image_stack::imagestack.at(0).pixel(k+1,n));
                }
            }
            //reset the row_counter
            row_counter = 0;
        }
    }
    else{

        //first get rid of artefacts of the more intelligent try
        for (n = 0; n < image.height(); n++){
            for (k = 0; k < image.width(); k++){
                if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba())
                    image.setPixel(k,n,image_stack::imagestack.at(0).pixel(k,n));
            }
        }
        clear_many_pixel();
    }

    wind_emitter = image;

    scene->clear();
    pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    ui->graphicsView->setFocus();
}

/*!
  Clears many pixels until a mask is found
  */
void MainWindow::clear_many_pixel(){

    QColor tmp;

    int i;
    int j;

    if (qAlpha(image.pixel(point.toPoint())) ==  alpha){

        for (j = 0; j < image.height() - point.toPoint().y(); j++){
            i = 0;
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) !=  alpha) break;
            while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) ==  alpha){
                tmp = image_stack::imagestack.at(0).pixel(point.toPoint().x() + i, point.toPoint().y() + j);
                image.setPixel(point.toPoint().x() + i, point.toPoint().y() + j, tmp.rgba());
                if (point.toPoint().x() + i < image.width() - 1){
                    i++;
                }
                else{
                    break;
                }
            }
        }

        for (j = 0; j < image.height() - point.toPoint().y(); j++){
            i = -1;
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) !=  alpha) break;
            while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) ==  alpha){
                tmp = image_stack::imagestack.at(0).pixel(point.toPoint().x() + i, point.toPoint().y() + j);
                image.setPixel(point.toPoint().x() + i, point.toPoint().y() + j, tmp.rgba());
                if (point.toPoint().x() + i > - 1){
                    i--;
                }
                else{
                    break;
                }
            }
        }

        for (j = 1; j < point.toPoint().y() + 1; j++){
            i = 0;
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) !=  alpha) break;
            while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) ==  alpha){
                tmp = image_stack::imagestack.at(0).pixel(point.toPoint().x() + i, point.toPoint().y() - j);
                image.setPixel(point.toPoint().x() + i, point.toPoint().y() - j, tmp.rgba());
                if (point.toPoint().x() + i < image.width()-1){
                    i++;
                }
                else{
                    break;
                }
            }
        }

        for (j = 1; j < point.toPoint().y()+1; j++){
            i = -1;
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) !=  alpha) break;
            while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) ==  alpha){
                tmp = image_stack::imagestack.at(0).pixel(point.toPoint().x() + i, point.toPoint().y() - j);
                image.setPixel(point.toPoint().x() + i, point.toPoint().y() - j, tmp.rgba());
                if (point.toPoint().x() + i > 0){
                    i--;
                }
                else{
                    break;
                }
            }
        }
    }

}

/*!
  Masks many pixels, good to mask islands in the mask
  */
void MainWindow::mask_many_pixel_1(){

    int boundarypixel[6];
    QImage image_tmp_clear;
    QColor special_color_for_marking;
    bool stop;
    bool stop_inner_while;
    bool on;
    int i;
    int n;
    int x;
    int y;
    int k;
    int start_x;
    int start_y;
    int zero_decision;
    int row_counter;
    int break_condition;

    stop = false;
    stop_inner_while = false;
    on = false;
    i = 0;
    n = 0;
    x = 0;
    y = 0;
    k = 0;
    start_x = 1;
    start_y = 0;
    zero_decision = 0;
    row_counter = 0;
    break_condition = 0;

    for (n = 0; n < 6; n++) boundarypixel[n] = 0;

    special_color_for_marking.setAlpha(alpha_special_marking);
    image_tmp_clear = image;

    if ((point.toPoint().x() >= 0)&&(point.toPoint().x()<image.width())
            &&(point.toPoint().y() >= 0)
            &&(point.toPoint().y()<image.height())
            && (qAlpha(image.pixel(point.toPoint().x(),point.toPoint().y()))) !=  alpha){

        while (stop == false){
            //first we go out of the whole in the mask
            if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y())) !=  alpha) {
                if (point.toPoint().x() + i < image.width() - 1){
                    i++;
                }
                else{
                    //This is no island in the mask, we stop this procedure here
                    stop = true;
                    break;
                }
            }
            else
            {
                //The first pixel in the boundary is found.
                //If boundary is not a mask point the vluse 1 in the vector at the highlighted place
                //| |2| |
                //|1|x|3|
                //| |4| |
                //1 - boundarypixel[2]
                //2 - boundarypixel[3]
                //3 - boundarypixel[4]
                //4 - boundarypixel[5]

                x = point.toPoint().x() + i;
                y = point.toPoint().y();

                start_x = x;
                start_y = y;

                //now lets walk counter-clockwise in the domain along the boundary
                while (stop_inner_while == false){

                    if (qAlpha(image.pixel(x - 1, y + 0)) != alpha){
                        boundarypixel[2] = 1;
                    }
                    else{
                        boundarypixel[2] = 0;
                    }
                    if (qAlpha(image.pixel(x + 0, y + 1)) != alpha){
                        boundarypixel[3] = 1;
                    }
                    else{
                        boundarypixel[3] = 0;
                    }
                    if (qAlpha(image.pixel(x + 1, y - 0)) != alpha){
                        boundarypixel[4] = 1;
                    }
                    else{
                        boundarypixel[4] = 0;
                    }
                    if (qAlpha(image.pixel(x + 0, y - 1)) != alpha){
                        boundarypixel[5] = 1;
                    }
                    else{
                        boundarypixel[5] = 0;
                    }
                    //now lets decide the next point
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        if (zero_decision == 2) x--;
                        if (zero_decision == 3) y++;
                        if (zero_decision == 4) x++;
                        if (zero_decision == 5) y--;
                        if (zero_decision == 6) x--;
                        if (zero_decision == 7) x--;
                        if (zero_decision == 8) y--;
                        if (zero_decision == 9) y++;
                        if (zero_decision == 10) y++;
                        if (zero_decision == 11) x++;
                        if (zero_decision == 12) x--;
                        if (zero_decision == 13) y--;
                        if (zero_decision == 14) x++;
                        if (zero_decision == 15) y++;

                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 2;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        x--;
                        zero_decision = 3;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y++;
                        zero_decision = 4;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 5;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 6;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 7;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 8;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        x--;
                        zero_decision = 9;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x--;
                        zero_decision = 10;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        y++;
                        zero_decision = 11;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 0)){
                        y--;
                        zero_decision = 12;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 0)&&(boundarypixel[5] == 1)){
                        x++;
                        zero_decision = 13;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 0)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        y++;
                        zero_decision = 14;
                    }
                    if ((boundarypixel[2] == 0)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        x--;
                        zero_decision = 15;
                    }
                    if ((boundarypixel[2] == 1)&&(boundarypixel[3] == 1)&&(boundarypixel[4] == 1)&&(boundarypixel[5] == 1)){
                        break;
                    }

                    for (n = 0; n < 6; n++) boundarypixel[n] = 0;

                    if ((x<0)||(y>image.width())) break;

                    break_condition++;

                    image_tmp_clear.setPixel(x,y,special_color_for_marking.rgba());

                    if (break_condition == image.width()*image.height()) stop_inner_while = true;
                    if ((x == start_x)&&(y == start_y)) stop_inner_while = true;

                }
                stop = true;
            }
        }
    }


    if ((x == start_x)&&(y == start_y)){
        //Now we make a first check through the image to search for the numbers of the special_mark_color in a row
        //for a further changes
        for (n = 0; n < image.height(); n++){

            for (k = 0; k < image.width(); k++){
                if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()){
                    row_counter++;
                }

            }
            //Now change the marking starting and stopping at the special_mark_color
            on = false;

            if (row_counter > 1){
                for (k = 0; k < image.width(); k++){

                    if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()) row_counter--;

                    if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba()) on = false;

                    if ((image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba())&&
                            (image_tmp_clear.pixel(k+1,n) != special_color_for_marking.rgba()))
                    {
                        if (on == false){
                            on = true;
                        }
                        else{
                            on = false;
                        }
                    }
                    if (row_counter == 0) on = false;
                    if (on == true) image.setPixel(k+1,n,final_mark_color.rgba());//image_stack::imagestack.at(0).pixel(k+1,n));
                }
            }
            //reset the row_counter
            row_counter = 0;
        }
    }
    else{

        //first get rid of artefacts of the more intelligent try
        for (n = 0; n < image.height(); n++){
            for (k = 0; k < image.width(); k++){
                if (image_tmp_clear.pixel(k,n) == special_color_for_marking.rgba())
                    image.setPixel(k,n,image_stack::imagestack.at(0).pixel(k,n));
            }
        }
        mask_many_pixel();
    }

    wind_emitter = image;

    scene->clear();
    pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    ui->graphicsView->setFocus();
}

/*!
  Masks many pixels until a mask pixel is found
  */
void MainWindow::mask_many_pixel(){

    int i;
    int j;

    if ((point.toPoint().x() >= 0)&&(point.toPoint().x()<image.width())&&(point.toPoint().y() >= 0)
            &&(point.toPoint().y()<image.height())){

        if (qAlpha(image.pixel(point.toPoint())) !=  alpha){

            for (j = 0; j < image.height() - point.toPoint().y(); j++){
                i = 0;
                if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) ==  alpha) break;
                while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) !=  alpha){
                    image.setPixel(point.toPoint().x() + i, point.toPoint().y() + j, final_mark_color.rgba());
                    if (point.toPoint().x() + i < image.width()-1){
                        i++;
                    }
                    else{
                        break;
                    }
                }
            }

            for (j = 0; j < image.height() - point.toPoint().y(); j++){
                i = -1;
                if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) ==  alpha) break;
                while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() + j)) !=  alpha){
                    image.setPixel(point.toPoint().x() + i, point.toPoint().y() + j, final_mark_color.rgba());
                    if (point.toPoint().x() + i > 0){
                        i--;
                    }
                    else{
                        break;
                    }
                }
            }

            for (j = 1; j < point.toPoint().y()+1; j++){
                i = 0;
                if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) ==  alpha) break;
                while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) !=  alpha){
                    image.setPixel(point.toPoint().x() + i, point.toPoint().y() - j, final_mark_color.rgba());
                    if (point.toPoint().x() + i < image.width()-1){
                        i++;
                    }
                    else{
                        break;
                    }
                }
            }

            for (j = 1; j < point.toPoint().y()+1; j++){
                i = -1;
                if (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) ==  alpha) break;
                while (qAlpha(image.pixel(point.toPoint().x() + i, point.toPoint().y() - j)) !=  alpha){
                    image.setPixel(point.toPoint().x() + i, point.toPoint().y() - j, final_mark_color.rgba());
                    if (point.toPoint().x() + i > 0){
                        i--;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}

/*!
  Masks individual pixels
  */
void MainWindow::mask_invidual_pixel(){

    if (no_image == false){
        image.setPixel(point.toPoint(), final_mark_color.rgba());

        scene->clear();
        pixmap = QPixmap::fromImage(image);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
        ui->graphicsView->setFocus();
    }
}

/*!
  Invert the mask
  */
void MainWindow::invert_mask(){

    for (int i = 0; i < image.width(); i++){
        for (int j = 0; j < image.height(); j++){
            if (image.pixel(i,j) == final_mark_color.rgba()){
                image.setPixel(i,j,image_stack::imagestack.at(0).pixel(i,j));
            }
            else{
                image.setPixel(i,j,final_mark_color.rgba());
            }
        }
    }

    wind_emitter = image;

    image_stack::imagestack.append(image);

    scene->clear();
    pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    ui->graphicsView->setFocus();



}
