#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <string>
#include <vtkRenderer.h>

#include <vtkNew.h>
#include <../renderer_class/renderer.hpp>

#include <vtkPyramid.h>
#include <vtkTetra.h>
#include <vtkHexahedron.h>
#include <vtkCellArray.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkMassProperties.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <vtkUnstructuredGrid.h>
#include <iostream>
#include <vtkAppendFilter.h>

MainWindow::MainWindow(QWidget *parent, std::string Filename) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // standard call to setup Qt UI (same as previously)
ui->setupUi( this );
        // Now need to create a VTK render window and link it to the QtVTK widget

        
// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt // creator
  
std::string inputFilename = Filename;

models.push_back(Filename);

reader =
    vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Visualize
  mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer =
    vtkSmartPointer<vtkRenderer>::New();
   //
  renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
ui->qvtkWidget->SetRenderWindow( renderWindow );
ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  colors =
                            vtkSmartPointer<vtkNamedColors>::New();
        actor->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );

  renderWindow->Render();
  renderWindowInteractor->Start();
  renderer->AddActor(actor);
        renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
        // Setup the renderers's camera
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Azimuth(30);
        renderer->GetActiveCamera()->Elevation(30);
        renderer->ResetCameraClippingRange();

        connect(this->ui->actionLoad, SIGNAL(triggered()), this, SLOT(openFile()));
        connect(this->ui->cross_section_box, SIGNAL(clicked(bool)), this, SLOT(Cross_Section_Analysis(bool)));
        connect(this->ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(Cross_Section_Analysis_Width(int)));
}

MainWindow::~MainWindow()
    {
delete ui; }

void MainWindow::openFile() 
{ 

         QString fileName = QFileDialog::getOpenFileName(this, 
         tr("Open  file with model/mesh"), "", 
         tr("files (*.stl);;All Files (*)")); 

         //Find filetype 

         



         std::string stdfiletype = fileName.toStdString();

         int num = stdfiletype.length()-3;

         std::cout<<num;

         std::string stdfiletypenew = stdfiletype.substr(num, stdfiletype.length());

         std::cout << "TYPE  " << stdfiletypenew << " FILETYPE!!! <<------- " << stdfiletypenew << "txt \n";

         
     
        if(stdfiletypenew.compare("txt") == 0){
        //Execute function for custom file type
        std::cout << "OPENING CUSTOM FILE\n";
        this -> openCustomFile(stdfiletype);

      }
     else if(stdfiletypenew != "txt")
     { 

         QFile file(fileName); 

         if (!file.open(QIODevice::ReadOnly)) { 
             QMessageBox::information(this, tr("Unable to open file"), 
                 file.errorString()); 
             return; 
         } 

        QDataStream in(&file); 
        in.setVersion(QDataStream::Qt_4_5); 


              std::string s = fileName.toStdString();

                const char* filename = s.c_str();
 
            reader =
    vtkSmartPointer<vtkSTLReader>::New();
        reader->SetFileName(filename); 
        reader->Update(); 

                

  mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer = vtkSmartPointer<vtkRenderer>::New();
   //
  renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  colors = vtkSmartPointer<vtkNamedColors>::New();
  actor->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );
  
ui->qvtkWidget->SetRenderWindow( renderWindow );
ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
  renderer->AddActor(actor);
  //renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  // renderWindowInteractor->Start();
  renderer->AddActor(actor);
        renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
        // Setup the renderers's camera
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Azimuth(30);
        renderer->GetActiveCamera()->Elevation(30);
        renderer->ResetCameraClippingRange();

                //reader->Delete(); 
} 
}

void MainWindow::openCustomFile(std::string fileName){

	//Custom code goes here!
	cout << "Opened Custom file\n ";

	//Get infomation from the renderer class about the tetrahedrons, pyramids and hexahedrons
  model model1 = model();

  std::string filename = fileName;

  model1.readInFile(filename);

	//Set up arrays to hold vtk objects 

  vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
  

  
  //For each tetrahedron: draw in VTK.


  for(int i = 0; i < model1.get_list_of_cells().size(); i++){
     /* For each cell in the file check whether its a pyramid,
       tetrahedron or hexahedron and then create the corresponding
       VTK shape+ */ 

    if(model1.get_list_of_cells()[i].get_shape() == 'p'){
      //Create a VTKpyramid and then add it to vtk list of pyramids
      vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
      vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();

      float p0[3] = {model1.get_list_of_cells()[i].get_vertices()[0].get('x'),model1.get_list_of_cells()[i].get_vertices()[0].get('y'),model1.get_list_of_cells()[i].get_vertices()[0].get('z')};
      float p1[3] = {model1.get_list_of_cells()[i].get_vertices()[1].get('x'),model1.get_list_of_cells()[i].get_vertices()[1].get('y'),model1.get_list_of_cells()[i].get_vertices()[1].get('z')};
      float p2[3] = {model1.get_list_of_cells()[i].get_vertices()[2].get('x'),model1.get_list_of_cells()[i].get_vertices()[2].get('y'),model1.get_list_of_cells()[i].get_vertices()[2].get('z')};
      float p3[3] = {model1.get_list_of_cells()[i].get_vertices()[3].get('x'),model1.get_list_of_cells()[i].get_vertices()[3].get('y'),model1.get_list_of_cells()[i].get_vertices()[3].get('z')};
      float p4[3] = {model1.get_list_of_cells()[i].get_vertices()[4].get('x'),model1.get_list_of_cells()[i].get_vertices()[4].get('y'),model1.get_list_of_cells()[i].get_vertices()[4].get('z')};

      points->InsertNextPoint(p0);
      points->InsertNextPoint(p1);
      points->InsertNextPoint(p2);
      points->InsertNextPoint(p3);
      points->InsertNextPoint(p4);

      vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();

      pyramid->GetPointIds()->SetId(0,0);
      pyramid->GetPointIds()->SetId(1,1);
      pyramid->GetPointIds()->SetId(2,2);
      pyramid->GetPointIds()->SetId(3,3);
      pyramid->GetPointIds()->SetId(4,4);

      cells->InsertNextCell(pyramid);
      

      ug->SetPoints(points);
      ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());

      appendFilter->AddInputData(ug);
      appendFilter->Update();


    } else if(model1.get_list_of_cells()[i].get_shape() == 't'){
      //Create a VTKtetrahedron and then add it to the vyk list of tetrahedrons
      vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
      vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();

      float p0[3] = {model1.get_list_of_cells()[i].get_vertices()[0].get('x'),model1.get_list_of_cells()[i].get_vertices()[0].get('y'),model1.get_list_of_cells()[i].get_vertices()[0].get('z')};
      float p1[3] = {model1.get_list_of_cells()[i].get_vertices()[1].get('x'),model1.get_list_of_cells()[i].get_vertices()[1].get('y'),model1.get_list_of_cells()[i].get_vertices()[1].get('z')};
      float p2[3] = {model1.get_list_of_cells()[i].get_vertices()[2].get('x'),model1.get_list_of_cells()[i].get_vertices()[2].get('y'),model1.get_list_of_cells()[i].get_vertices()[2].get('z')};
      float p3[3] = {model1.get_list_of_cells()[i].get_vertices()[3].get('x'),model1.get_list_of_cells()[i].get_vertices()[3].get('y'),model1.get_list_of_cells()[i].get_vertices()[3].get('z')};

      points->InsertNextPoint(p0);
      points->InsertNextPoint(p1);
      points->InsertNextPoint(p2);
      points->InsertNextPoint(p3);

      vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();

      tetra -> GetPointIds()->SetId(0,0);
      tetra -> GetPointIds()->SetId(1,1);
      tetra -> GetPointIds()->SetId(2,2);
      tetra -> GetPointIds()->SetId(3,3);

      cells->InsertNextCell(tetra);

      ug->SetPoints(points);
      ug->InsertNextCell(tetra->GetCellType(),tetra->GetPointIds());

      appendFilter->AddInputData(ug);
      appendFilter->Update();

      
    } else if(model1.get_list_of_cells()[i].get_shape() == 'h'){
      //Create a VTKhexahedron and then add it to the vtk list of hexahedrons
      vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
      vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();

      float p0[3] = {model1.get_list_of_cells()[i].get_vertices()[0].get('x'),model1.get_list_of_cells()[i].get_vertices()[0].get('y'),model1.get_list_of_cells()[i].get_vertices()[0].get('z')};
      float p1[3] = {model1.get_list_of_cells()[i].get_vertices()[1].get('x'),model1.get_list_of_cells()[i].get_vertices()[1].get('y'),model1.get_list_of_cells()[i].get_vertices()[1].get('z')};
      float p2[3] = {model1.get_list_of_cells()[i].get_vertices()[2].get('x'),model1.get_list_of_cells()[i].get_vertices()[2].get('y'),model1.get_list_of_cells()[i].get_vertices()[2].get('z')};
      float p3[3] = {model1.get_list_of_cells()[i].get_vertices()[3].get('x'),model1.get_list_of_cells()[i].get_vertices()[3].get('y'),model1.get_list_of_cells()[i].get_vertices()[3].get('z')};
      float p4[3] = {model1.get_list_of_cells()[i].get_vertices()[4].get('x'),model1.get_list_of_cells()[i].get_vertices()[4].get('y'),model1.get_list_of_cells()[i].get_vertices()[4].get('z')};
      float p5[3] = {model1.get_list_of_cells()[i].get_vertices()[5].get('x'),model1.get_list_of_cells()[i].get_vertices()[5].get('y'),model1.get_list_of_cells()[i].get_vertices()[5].get('z')};
      float p6[3] = {model1.get_list_of_cells()[i].get_vertices()[6].get('x'),model1.get_list_of_cells()[i].get_vertices()[6].get('y'),model1.get_list_of_cells()[i].get_vertices()[6].get('z')};
      float p7[3] = {model1.get_list_of_cells()[i].get_vertices()[7].get('x'),model1.get_list_of_cells()[i].get_vertices()[7].get('y'),model1.get_list_of_cells()[i].get_vertices()[7].get('z')};

      points -> InsertNextPoint(p0);
      points -> InsertNextPoint(p1);
      points -> InsertNextPoint(p2);
      points -> InsertNextPoint(p3);
      points -> InsertNextPoint(p4);
      points -> InsertNextPoint(p5);
      points -> InsertNextPoint(p6);
      points -> InsertNextPoint(p7);

      vtkSmartPointer<vtkHexahedron> hexa = vtkSmartPointer<vtkHexahedron>::New();

      hexa -> GetPointIds()->SetId(0,0);
      hexa -> GetPointIds()->SetId(1,1);
      hexa -> GetPointIds()->SetId(2,2);
      hexa -> GetPointIds()->SetId(3,3);
      hexa -> GetPointIds()->SetId(4,4);
      hexa -> GetPointIds()->SetId(5,5);
      hexa -> GetPointIds()->SetId(6,6);
      hexa -> GetPointIds()->SetId(7,7);

      cells->InsertNextCell(hexa);
      ug->SetPoints(points);
      ug->InsertNextCell(hexa->GetCellType(),hexa->GetPointIds());

      appendFilter->AddInputData(ug);
      appendFilter->Update();

    }
  }

  vtkSmartPointer<vtkUnstructuredGrid> combined = appendFilter->GetOutput();

  //Create an actor and mapper 
  vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();

  mapper->SetInputData(combined);

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  

  //Create a renderer, render window and interactor

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  

  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
  ui->qvtkWidget->SetRenderWindow( renderWindow );
  ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
  
  renderer->AddActor(actor);

  //Create a view

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(180);
  renderer->GetActiveCamera()->Elevation(-20);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();
	
}

void MainWindow::Cross_Section_Analysis(bool checked){

  
  
if (checked){
  is_checked = checked;
        cutPlane->SetOrigin( 
                this->renderer->GetActiveCamera()->GetFocalPoint()); 
        cutPlane->SetNormal( 
                this->renderer->GetActiveCamera()->GetViewPlaneNormal()); 

        // setup cutter and attach cutplane 
        vtkNew<vtkCutter> cutter; 
        cutter->SetCutFunction(cutPlane); 
        cutter->SetInputConnection(reader->GetOutputPort()); 
        cutter->Update(); 

        // crossection mapper 
        vtkNew<vtkPolyDataMapper> cutterMapper; 
        cutterMapper->SetInputConnection(cutter->GetOutputPort()); 

        // actor for displaying the extracted cross-section from the sphere 
        vtkNew<vtkActor> cutterActor; 
        cutterActor->SetMapper(cutterMapper); 
        cutterActor->GetProperty()->SetDiffuseColor(0.2, .49, 1); 
        cutterActor->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData() ); 
        cutterActor->GetProperty()->SetLineWidth(1.0f); 
        cutterActor->GetProperty()->SetOpacity(1.0); 
        
        // add all actors to the Renderers
        renderer->RemoveAllViewProps(); 
        renderer->AddActor(cutterActor);  

        cutterActor->GetProperty()->LightingOff(); 
        cutterActor->GetProperty()->SetAmbient(1.0); 

        ui->horizontalSlider->setValue(0);

        ui->qvtkWidget->GetRenderWindow()->Render();



      } else {
        renderer->RemoveAllViewProps();
        renderer->AddActor(actor);
        is_checked = checked;
        ui->horizontalSlider->setValue(0);
        ui->qvtkWidget->GetRenderWindow()->Render();
}

} 

void MainWindow::Cross_Section_Analysis_Width(int value){
  if(is_checked){
    
    double* focal = this->cutPlane->GetOrigin();

    double* Norm = this->cutPlane->GetNormal();



  focal[1] = value;


  vtkNew<vtkPlane> cutPlane2; 
        cutPlane2->SetOrigin(focal); 
        cutPlane2->SetNormal(Norm);
        // setup cutter and attach cutplane 
        vtkNew<vtkCutter> cutter; 
        cutter->SetCutFunction(cutPlane2); 
        cutter->SetInputConnection(reader->GetOutputPort()); 
        cutter->Update(); 

        // crossection mapper 
        vtkNew<vtkPolyDataMapper> cutterMapper; 
        cutterMapper->SetInputConnection(cutter->GetOutputPort()); 

        // actor for displaying the extracted cross-section from the sphere 
        vtkNew<vtkActor> cutterActor; 
        cutterActor->SetMapper(cutterMapper); 
        cutterActor->GetProperty()->SetDiffuseColor(0.2, .49, 1); 
        cutterActor->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData() ); 
        cutterActor->GetProperty()->SetLineWidth(1.0f); 
        cutterActor->GetProperty()->SetOpacity(1.0); 
        
        // add all actors to the Renderers
        renderer->RemoveAllViewProps(); 
        renderer->AddActor(cutterActor);


        cutterActor->GetProperty()->LightingOff(); 
        cutterActor->GetProperty()->SetAmbient(1.0); 

        ui->qvtkWidget->GetRenderWindow()->Render();
  } else {
        
  }


}
        





