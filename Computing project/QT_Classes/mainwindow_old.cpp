
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // standard call to setup Qt UI (same as previously)
ui->setupUi( this );
        // Now need to create a VTK render window and link it to the QtVTK widget
        vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt // creator
ui->qvtkWidget->SetRenderWindow( renderWindow );
        // Now use the VTK libraries to render something. To start with you can
        // copy-paste the cube example code, there are comments to show where the
        // code must be modified.
        // Create a cube using a vtkCubeSource
        vtkSmartPointer<vtkCubeSource> cubeSource =
                        vtkSmartPointer<vtkCubeSource>::New();
// Create a mapper that will hold the cube's geometry in a format // suitable for rendering
vtkSmartPointer<vtkDataSetMapper> mapper =
                        vtkSmartPointer<vtkDataSetMapper>::New();

                        mapper->SetInputConnection( cubeSource->GetOutputPort() );
// Create an actor that is used to set the cube's properties for rendering // and place it in the window
vtkSmartPointer<vtkActor> actor =
                        vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->EdgeVisibilityOn();
        vtkSmartPointer<vtkNamedColors> colors =
                            vtkSmartPointer<vtkNamedColors>::New();
        actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );
        // Create a renderer, and render window
        vtkSmartPointer<vtkRenderer> renderer =
                            vtkSmartPointer<vtkRenderer>::New();
        // ###### We've already created the renderWindow this time as a qt
        // widget ######
        //vtkSmartPointer<vtkRenderWindow> renderWindow =
        //                  vtkSmartPointer<vtkRenderWindow>::New();
ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer ); //
        // Link a renderWindowInteractor to the renderer (this allows you to
        // capture mouse movements etc)  ###### Not needed with Qt ######
        //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        //                  vtkSmartPointer<vtkRenderWindowInteractor>::New();
        //
        //renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );
        // Add the actor to the scene
        renderer->AddActor(actor);
        renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
        // Setup the renderers's camera
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Azimuth(30);
        renderer->GetActiveCamera()->Elevation(30);
        renderer->ResetCameraClippingRange();
        // Render and interact
        //renderWindow->Render();
        //renderWindowInteractor->Start();// ###### Not needed with Qt ######
}
    MainWindow::~MainWindow()
    {
delete ui; }