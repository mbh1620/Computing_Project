#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject.h>
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
#include <../renderer_class/renderer.hpp>
#include <QMainWindow>
namespace Ui { class MainWindow; }


/// The MainWindow class is used for the QT user interface. This is where all of the functionalilty for the buttons, sliders and the functions for VKT are contained.

/** 
* The MainWindow class is used for the QT user interface. This is where all of the functionality for the buttons, sliders, and the VTKwidget are contained.
*/


class MainWindow : public QMainWindow {
Q_OBJECT
public:
explicit MainWindow(QWidget * parent = 0, std::string Filename = "Boat.stl"); ~MainWindow();

vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;                                              ///< The vtkGenericOpenGLRenderWindow object for VTK.

std::string Filename;                                                                           ///< a string to contain a Filename.

vtkSmartPointer<vtkSTLReader> reader;                                                           ///< A vtkSTLReader object for reading in .STL files

vtkSmartPointer<vtkPolyDataMapper> mapper;                                                      ///< The vtkPolyData mapper for mapping Poly Data.

vtkSmartPointer<vtkDataSetMapper> mapper2;                                                      ///< The vtkDataSetMapper for mapping a Data set. 

std::deque<vtkSmartPointer<vtkActor>> actor;                                                    ///< A Deque to hold all the actors for when multiple models have been loaded into the same window.

vtkSmartPointer<vtkRenderer> renderer;                                                          ///< A vtkRenderer used to render the window.

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;                              ///< A window interactor which is used for moving model with mouse.

vtkSmartPointer<vtkNamedColors> colors;                                                         ///< vtk named colors for choosing different colours for model.

vtkNew<vtkPlane> cutPlane;                                                                      ///< a vtk plane for slicing the model and producing the cross section.

vtkSmartPointer<vtkDistanceWidget> distanceWidget;                                              ///< A distance widget used in the measurement tool.

std::deque<std::string> models;                                                                 ///< A deque to hold the names of the models.

model model1;

bool is_checked;                                                                                ///< A bool flag to see if a checkbox is checked.

void openCustomFile(std::string fileName);                                                      ///< Function for opening a proprietry file format and using own classes 

int item_length = 0;                                                                            

int check_item_array_length();                                  

void disable_distance_widget();

public slots:
    void openFile();                                                                            ///< The openFile slot is used to trigger the QFileDialog to see whether to open a proprietry or STL file type.

    void on_file_add(QString filename);                                                         ///< The on_file_add() slot is used to trigger the STL file reader.

    void Cross_Section_Analysis(bool checked);                                                  ///< This is the function for creating a cross section of the model.

    void enable_distance_widget(bool checked);                                                  ///< This is the function to enable the distance widget.
    
    void Cross_Section_Analysis_Width(int value);                                               ///< This function changes the width of the cross section.

    void transform();                                                                           ///< This is used for translating and rotating models.

    void delete_model();                                                                        ///< This is used to delete a model from the screen.

    void model_details();                                                                       ///< This is called to update a models details such as the weight, volume and various other properties about a model.

    void changeCamera();                                                                        ///< This is used to change the position of the active camera.

    void set_bg_colour();                                                                       ///< This sets the bg colour.

    void Set_Model_Color();                                                                     ///< This sets the model color.

    void Reset_Camera();                                                                        ///< Resets the camera position so its close to the model.

    void Set_Opacity();                                                                         ///< Sets the model opacity.

    void show_COG(bool checked);                                                                ///< Shows an arrow indicating the models centre of gravity.

    void Save_As_STL_File();                                                                    ///< This saves all the models on screen as a .STL file.

    void On_component_click();                                                                  ///< This updates component lists on the component tab.

private:
Ui::MainWindow * ui;
};
#endif // MAINWINDOW_H