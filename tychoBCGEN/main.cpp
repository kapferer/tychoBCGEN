/*!
  This is tychoBCGEN - the Boundary Condition GENerator for TYCHO (TYrolian
  Computational HydrOdynamics). Aim of this program is the generation
  of boundary conditions from pixel images (i.e. jpeg or png files). This is
  done by selecting pixels in the same color-range and exporting the masks as
  solid boundaries.
  This is version 0.3 of tychoBCGEN, which is freely available to everyone.

  You are welcome to download it and do whatever you want with it.
  I would appreciate, however, if you would acknowledge the package in your
  publications/work and if you send me information for what purpose you use the code.

  Developed by Wolfgang Kapferer Mai/June 2012
  */

#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>

/*!
  The Main Routine
  */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
