#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QGraphicsView>
#include <QEvent>
#include <QGraphicsScene>


namespace Ui {
class tutorial;
}

class tutorial : public QDialog
{
    Q_OBJECT
    
public:
    explicit tutorial(QWidget *parent = 0);


    ~tutorial();
    
private:
    Ui::tutorial *ui;
    QImage image_tutorial;
    QPixmap pixmap_tutorial;
    QGraphicsScene *scene_tutorial;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // TUTORIAL_H
