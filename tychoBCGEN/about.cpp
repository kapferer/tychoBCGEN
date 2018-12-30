/*!
This is tychoBCGEN version 0.3 (TYCHO Boundary Condition GENerator).
Aim of the program is the generation of 2D  boundary-conditions for
TYCHO (TYrolian Computational HydrOdynamics -www.tycho-cfd.at) out of
drawings or even photos. In addition wind-emitters like ventilators can be
included.

The software comes without any guarantee and is freely available to everyone.

Author is Wolfgang Kapferer.
  */

#include "about.h"
#include "global.h"
#include "ui_about.h"

int counter_about;

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    connect(ui->close, SIGNAL(clicked()), this, SLOT(close()));
}

about::~about()
{
    delete ui;
}
