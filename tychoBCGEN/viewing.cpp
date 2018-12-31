/*!
Zooming and viewing
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QScrollBar>
#include <QScrollArea>


void MainWindow::scale_to_width(){

    ui->graphicsView->fitInView(image.rect(), Qt::KeepAspectRatio);
    ui->graphicsView->setAlignment(Qt::AlignTop);

}

void MainWindow::scale_original(){

    ui->graphicsView->resetTransform();
    ui->graphicsView->setAlignment(Qt::AlignTop);
}


void MainWindow::zoom_in(){

    qreal zoomfactor;

    zoomfactor = (100.0 + ui->zoom_factor->text().toDouble())/100.0;

    if (image.isNull()==false) ui->graphicsView->scale(zoomfactor,zoomfactor);

}


void MainWindow::zoom_out(){

    qreal zoomfactor;

    zoomfactor = (100.0 + ui->zoom_factor->text().toDouble())/100.0;

    zoomfactor = 1.0/zoomfactor;

    if (image.isNull()==false) ui->graphicsView->scale(zoomfactor,zoomfactor);

}

