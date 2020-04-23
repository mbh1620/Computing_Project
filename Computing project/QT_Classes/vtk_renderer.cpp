#include <QApplication>
    #include <QSurfaceFormat>
    #include <QVTKOpenGLWidget.h>
#include "mainwindow.h"
int main( int argc, char** argv )
{
// needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );
    QApplication a( argc, argv );
    MainWindow example;
    example.show();
return a.exec(); 

}