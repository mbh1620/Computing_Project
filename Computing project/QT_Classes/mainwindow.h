#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSTLReader.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <deque>

#include <QMainWindow>
namespace Ui { class MainWindow; }
class MainWindow : public QMainWindow {
Q_OBJECT
public:
explicit MainWindow(QWidget * parent = 0, std::string Filename = "Boat.stl"); ~MainWindow();

vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

std::string Filename;

vtkSmartPointer<vtkSTLReader> reader;

vtkSmartPointer<vtkPolyDataMapper> mapper;

vtkSmartPointer<vtkActor> actor;

vtkSmartPointer<vtkRenderer> renderer;

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;

vtkSmartPointer<vtkNamedColors> colors;

vtkNew<vtkPlane> cutPlane; 

std::deque<std::string> models;

bool is_checked;

void openCustomFile(std::string fileName); //Function for opening a proprietry file format and using own classes

public slots:
    void openFile();

    void Cross_Section_Analysis(bool checked);
    void Cross_Section_Analysis_Width(int value);

private:
Ui::MainWindow * ui;
};
#endif // MAINWINDOW_H