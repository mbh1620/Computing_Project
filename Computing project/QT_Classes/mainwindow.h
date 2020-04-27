#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkSTLReader.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <deque>
#include <vtkDistanceWidget.h>

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

vtkSmartPointer<vtkDataSetMapper> mapper2;

std::deque<vtkSmartPointer<vtkActor>> actor;

vtkSmartPointer<vtkRenderer> renderer;

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;

vtkSmartPointer<vtkNamedColors> colors;

vtkNew<vtkPlane> cutPlane; 

vtkSmartPointer<vtkDistanceWidget> distanceWidget;

std::deque<std::string> models;

bool is_checked;

void openCustomFile(std::string fileName); //Function for opening a proprietry file format and using own classes

int item_length = 0;

int check_item_array_length();

void disable_distance_widget();

public slots:
    void openFile();

    void on_file_add(QString filename);

    void Cross_Section_Analysis(bool checked);

    void enable_distance_widget(bool checked);
    
    void Cross_Section_Analysis_Width(int value);

    void transform();

    void delete_model();

    void model_details();

    void changeCamera();

    void set_bg_colour();

    void Set_Model_Color();

    void Reset_Camera();

    void Set_Opacity();

    void show_COG(bool checked);

    void Save_As_STL_File();

private:
Ui::MainWindow * ui;
};
#endif // MAINWINDOW_H