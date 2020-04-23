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
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // standard call to setup Qt UI (same as previously)
ui->setupUi( this );
        // Now need to create a VTK render window and link it to the QtVTK widget

        vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt // creator

       


std::string inputFilename = "Boat.STL";

vtkSmartPointer<vtkSTLReader> reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer ); //
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
ui->qvtkWidget->SetRenderWindow( renderWindow );
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  vtkSmartPointer<vtkNamedColors> colors =
                            vtkSmartPointer<vtkNamedColors>::New();
        actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );

  renderWindow->Render();
  renderWindowInteractor->Start();
  renderer->AddActor(actor);
        renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
        // Setup the renderers's camera
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Azimuth(30);
        renderer->GetActiveCamera()->Elevation(30);
        renderer->ResetCameraClippingRange();

}

MainWindow::~MainWindow()
    {
delete ui; }