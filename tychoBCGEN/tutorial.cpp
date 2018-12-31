/*!
The tutorial window
*/

#include "tutorial.h"
#include "global.h"
#include "ui_tutorial.h"


tutorial::tutorial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tutorial)
{
    ui->setupUi(this);

    QString file("./images/workflow.png");

    connect(ui->close, SIGNAL(clicked()), this, SLOT(close()));

    image_tutorial.load(file);
    pixmap_tutorial = QPixmap::fromImage(image_tutorial);
    if (image_tutorial.width() > 0){
        scene_tutorial = new QGraphicsScene;
        scene_tutorial->addPixmap(pixmap_tutorial);
        ui->graphicsView->setScene(scene_tutorial);
        ui->graphicsView->setDragMode(ui->graphicsView->ScrollHandDrag);
    }

}

tutorial::~tutorial()
{
    delete ui;
}


void tutorial::resizeEvent(QResizeEvent *){

    int width = tutorial::width();
    int heigth = tutorial::height();

    ui->close->setGeometry(width-100, heigth-50, 86, 25);

    ui->textBrowser->setGeometry(10, 10, width/2-200, heigth-75);
    ui->graphicsView->setGeometry(width/2-180,10, width/2+170, heigth-75);

}
