/*!
  Open / Save files
  */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>

/*!
Opens an Image
*/
void MainWindow::openfile()
{
    file = QFileDialog::getOpenFileName(this, tr("Open File"),"/home/kapf/tmp",tr("Images (*.jpeg *.jpg *.png *.bmp *.gif *.tif)"));

    image_stack::imagestack.clear();

    image.load(file);

    image = image.convertToFormat(QImage::Format_ARGB32,Qt::AutoColor);
    image = image.mirrored(false, true);
    wind_emitter = image;
    wind_emitter_save = image;
    wind_emitter_save.fill(Qt::white);

    imagewidth = image.width();
    imageheight = image.height();

    image_stack::imagestack.append(image);

    ui->image_width->setText(QString::number(imagewidth));
    ui->image_height->setText(QString::number(imageheight));

    pixmap = QPixmap::fromImage(image_stack::imagestack.at(0));
    pixmapwidth = pixmap.width();
    pixmapheight = pixmap.height();

    scene = new myscene();
    scene->addPixmap(pixmap);
    ui->reset_mask->setEnabled(true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->rotate(180);
    ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    ui->graphicsView->setFocus();

    no_image = false;

    //now we activate the high, width and depth fields
    ui->image_width->setEnabled(true);
    ui->image_height->setEnabled(true);
    ui->image_depth->setEnabled(true);
}

/*!
saves a masked image for further masking action
*/
void MainWindow::save_masked_image(){

    if (no_image == false){

        file_masked_image_save = QFileDialog::getSaveFileName(this, tr("Save Masked Image"),"/home/kapf/tmp",tr("Images (*.png)"));

        QFileInfo file(file_masked_image_save);
        if(file.suffix().isEmpty()) file_masked_image_save += ".png";

        image.save(file_masked_image_save);
    }

}

/*!
Saves a TYCHO boundary file
*/
void MainWindow::savefile()
{
    if(no_image == false){
        FILE *fd;
        QString filename;
        QColor tmp1;
        int tmp;

        image = image_stack::imagestack.last();

        file_save = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/kapf/tmp",tr("tycho IC (*.tyc)"));

        QFileInfo file(file_save);
        if(file.suffix().isEmpty()) file_save += ".tyc";

        if ((file_save != NULL)&&(no_image == false)){
            filename = file_save;

            fd = fopen(filename.toUtf8(), "w");
            fprintf(fd,"This is a TYCHO boundary condition file.\n");
            fprintf(fd,"X %i\n", image.width());
            fprintf(fd,"Y %i\n", image.height());
            fprintf(fd,"Z %i\n", ui->image_depth->text().toInt());
            fseek(fd, 200, SEEK_SET);
            for (int j = 0; j < image.width(); j++) {
                for (int k = 0; k < image.height(); k++) {

                    tmp1 = image.pixel(j,k);
                    if (tmp1 == final_mark_color.rgba()) {
                        tmp=1;
                        for (int i = 0; i < ui->image_depth->text().toInt(); i++) if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;
                    }
                    else{
                        tmp=0;
                        for (int i = 0; i < ui->image_depth->text().toInt(); i++) if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;

                    }
                }
            }


            fclose(fd);
        }
    }

}

/*!
Saves a TYCHO soundemitter file
*/
void MainWindow::savefile_soundemitter()
{
    if(no_image == false){
        FILE *fd;
        QString filename;
        QColor tmp1;
        int tmp;

        image = image_stack::imagestack.last();

        file_save = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/kapf/tmp",tr("tycho IC (*.tyc)"));

        QFileInfo file(file_save);
        if(file.suffix().isEmpty()) file_save += ".tyc";

        if ((file_save != NULL)&&(no_image == false)){
            filename = file_save;

            fd = fopen(filename.toUtf8(), "w");
            fprintf(fd,"This is a TYCHO soundemitter file.\n");
            fprintf(fd,"X %i\n", image.width());
            fprintf(fd,"Y %i\n", image.height());
            fprintf(fd,"Z %i\n", ui->image_depth->text().toInt());
            fseek(fd, 200, SEEK_SET);
            for (int j = 0; j < image.width(); j++) {
                for (int k = 0; k < image.height(); k++) {

                    tmp1 = image.pixel(j,k);
                    if (tmp1 == final_mark_color.rgba()) {
                        tmp=1;
                        for (int i = 0; i < ui->image_depth->text().toInt(); i++) if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;
                    }
                    else{
                        tmp=0;
                        for (int i = 0; i < ui->image_depth->text().toInt(); i++) if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;

                    }
                }
            }


            fclose(fd);
        }
    }

}

/*!
Saves a TYCHO Wind-Emitter file
*/
void MainWindow::save_wind_emitter(){

    if(no_image == false){
        FILE *fd;
        QString filename;
        QColor tmp1;
        int tmp;

        file_save = QFileDialog::getSaveFileName(this, tr("Save Wind - Emitter"),"/home/kapf/tmp",tr("tycho IC (*.tyc)"));

        QFileInfo file(file_save);
        if(file.suffix().isEmpty()) file_save += ".tyc";

        if ((file_save != NULL)&&(no_image == false)){
            filename = file_save;

            fd = fopen(filename.toUtf8(), "w");
            fprintf(fd,"This is a TYCHO wind-emitter file.\n");
            fprintf(fd,"X %i\n", image.width());
            fprintf(fd,"Y %i\n", image.height());
            fprintf(fd,"Y %i\n", ui->image_depth->text().toInt());
            fseek(fd, 200, SEEK_SET);
            for (int j = 0; j < image.width(); j++) {
                for (int k = 0; k < image.height(); k++) {
                    for (int i = 0; i < ui->image_depth->text().toInt(); i++) {
                        tmp1 = wind_emitter_save.pixel(j,k);
                        if (tmp1 == emitter_color_x.rgba()) {
                            tmp=2;
                            if (!fwrite(&tmp, 1, sizeof (int), fd)) break;
                        }
                        else if (tmp1 == emitter_color_mx.rgba()) {
                            tmp=3;
                            if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;
                        }
                        else if (tmp1 == emitter_color_y.rgba()) {
                            tmp=4;
                            if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;
                        }
                        else if (tmp1 == emitter_color_my.rgba()) {
                            tmp=5;
                            if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;
                        }
                        else{
                            tmp=0;
                            if (!fwrite(&tmp, 1, sizeof (int), fd)) break;;

                        }
                    }
                }
            }

            fclose(fd);
        }
    }

}
