#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <string>
#include <vtkRenderer.h>
#include <vtkTransform.h>

#include <vtkDataSetMapper.h>

#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkNew.h>
#include <../renderer_class/renderer.hpp>

#include <vtkMassProperties.h>
#include <vtkTriangleFilter.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkGeometryFilter.h>


#include <vtkDistanceRepresentation.h>
#include <vtkDistanceWidget.h>

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
#include <QStringListModel>
#include <QStringList>
#include <vtkUnstructuredGrid.h>
#include <iostream>
#include <vtkAppendFilter.h>


MainWindow::MainWindow(QWidget *parent, std::string Filename) : QMainWindow(parent), ui(new Ui::MainWindow) {

  //iniatialize the actor array to null

  //Set item_length
 


    // standard call to setup Qt UI (same as previously)
ui->setupUi( this );
        // Now need to create a VTK render window and link it to the QtVTK widget

        
// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt // creator
  
std::string inputFilename = Filename;

QString file_name = QString::fromStdString(inputFilename);

this->on_file_add(file_name);

models.push_back(Filename);

reader = vtkSmartPointer<vtkSTLReader>::New();
reader->SetFileName(inputFilename.c_str());
reader->Update();

  // Visualize
mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputConnection(reader->GetOutputPort());

actor.push_back(vtkSmartPointer<vtkActor>::New());
actor.back()->SetMapper(mapper);

renderer = vtkSmartPointer<vtkRenderer>::New();
renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
ui->qvtkWidget->SetRenderWindow( renderWindow );
ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
//renderWindowInteractor->SetRenderWindow(ui->qvtkWidget->GetRenderWindow());

renderer->AddActor(actor.back());
renderer->SetBackground(.3, .6, .3); // Background color green

colors = vtkSmartPointer<vtkNamedColors>::New();
actor.back()->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );

renderWindow->Render();
renderWindowInteractor->Start();
renderer->AddActor(actor.back());
renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
// Setup the renderers's camera
renderer->ResetCamera();
renderer->GetActiveCamera()->Azimuth(30);
renderer->GetActiveCamera()->Elevation(30);
renderer->ResetCameraClippingRange();



//renderWindowInteractor->SetRenderWindow (renderWindow);
renderWindow->Render();

vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
  
renderWindowInteractor->SetInteractorStyle( style );


//Fill Background Color Combo Box:

ui->comboBox->addItem("Silver");
ui->comboBox->addItem("Red");
ui->comboBox->addItem("White");
ui->comboBox->addItem("Yellow");
ui->comboBox->addItem("Green");
ui->comboBox->addItem("Blue");



ui->comboBox_2->addItem("Silver");
ui->comboBox_2->addItem("Red");
ui->comboBox_2->addItem("White");
ui->comboBox_2->addItem("Yellow");
ui->comboBox_2->addItem("Green");
ui->comboBox_2->addItem("Blue");


        //Set spin boxes to the values of the camera

        /* Camera Position:
        
        x = spinBox
        y = spinBox_2
        z = spinBox_3

        camera rotation

        x = spinBox_4
        y = spinBox_5
        z = spinBox_6

        */

//Camera position
ui->spinBox->setValue(renderer->GetActiveCamera()->GetPosition()[0]);
ui->spinBox_2->setValue(renderer->GetActiveCamera()->GetPosition()[1]);
ui->spinBox_3->setValue(renderer->GetActiveCamera()->GetPosition()[2]);
//Camera angle 



//Connecting SLOTS

connect(this->ui->actionLoad, SIGNAL(triggered()), this, SLOT(openFile()));
connect(this->ui->cross_section_box, SIGNAL(clicked(bool)), this, SLOT(Cross_Section_Analysis(bool)));
connect(this->ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(Cross_Section_Analysis_Width(int)));
connect(this->ui->pushButton, SIGNAL(released()), this, SLOT(openFile()));
connect(this->ui->pushButton_2, SIGNAL(released()), this, SLOT(delete_model()));
connect(this->ui->pushButton_3, SIGNAL(released()), this, SLOT(transform()));

connect(this->ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(model_details()));

connect(this->ui->checkBox_3, SIGNAL(clicked(bool)), this, SLOT(enable_distance_widget(bool)));


//Slots for camera control

connect(this->ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));
connect(this->ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));
connect(this->ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));
connect(this->ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));
connect(this->ui->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));
connect(this->ui->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(changeCamera()));

//Slot for colour combo box

connect(this->ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(set_bg_colour()));

connect(this->ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(Set_Model_Color()));

connect(this->ui->pushButton_5, SIGNAL(released()), this, SLOT(Reset_Camera()));
        


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

         this->on_file_add(fileName);



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

  

  actor.push_back(vtkSmartPointer<vtkActor>::New());
  actor.back()->SetMapper(mapper);

  renderer = vtkSmartPointer<vtkRenderer>::New();
   //
  renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  colors = vtkSmartPointer<vtkNamedColors>::New();
  actor.back()->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );
  
ui->qvtkWidget->SetRenderWindow( renderWindow );
ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
  renderer->AddActor(actor.back());
  //renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  // renderWindowInteractor->Start();

  //Add all actors
  for(int i = 0; i < actor.size(); i++){
    renderer->AddActor(actor[i]);
  }

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

  vtkSmartPointer<vtkGeometryFilter> geometryfilter = vtkSmartPointer<vtkGeometryFilter>::New();

  geometryfilter->SetInputData(combined);

  geometryfilter->Update();

  vtkPolyData* polyData = geometryfilter->GetOutput();

  mapper->SetInputData(polyData);  

  actor.push_back(vtkSmartPointer<vtkActor>::New());
  actor.back()->SetMapper(mapper);
  actor.back()->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  

  //Create a renderer, render window and interactor

  renderer = vtkSmartPointer<vtkRenderer>::New();
  

  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
  ui->qvtkWidget->SetRenderWindow( renderWindow );
  ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
  
  //Add all actors
  for(int i = 0; i < actor.size(); i++){
    renderer->AddActor(actor[i]);
  }

  

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
        
        for(int i = 0; i < actor.size(); i++){
          renderer->AddActor(actor[i]);
        }
        

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
        
void MainWindow::on_file_add(QString filename)
{
	std::string fileName = filename.toStdString();
	int pos;
	pos = fileName.find_last_of("/");
	fileName = fileName.substr(pos+1);
	filename = QString::fromStdString(fileName);
	ui->listWidget->addItem(filename);



}

void MainWindow::delete_model()
{
  
  int number = ui->listWidget->currentRow();
  
	qDeleteAll(ui->listWidget->selectedItems());
  renderer->RemoveActor(actor[number]);

  actor.erase(actor.begin()+number);
  
  ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::transform()
{

  //Get the actor of the object which is currently highlighted in the listView

  int number = ui->listWidget->currentRow();

  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  transform->PostMultiply();
     //lineEdit_6
  QString x_trans = ui->lineEdit->text();//lineEdit
  QString y_trans = ui->lineEdit_2->text();//lineEdit_2
  QString z_trans = ui->lineEdit_3->text();//lineEdit_3
  double x_trans_double = x_trans.toDouble();
  double y_trans_double = y_trans.toDouble();
  double z_trans_double = z_trans.toDouble();



  QString x_rot = ui->lineEdit_4->text();
  QString y_rot = ui->lineEdit_5->text();
  QString z_rot = ui->lineEdit_6->text();
  double x_rot_double = x_rot.toDouble();
  double y_rot_double = y_rot.toDouble();
  double z_rot_double = z_rot.toDouble();

  transform->RotateX(x_rot_double);   //lineEdit_4
  transform->RotateY(y_rot_double);   //lineEdit_5
  transform->RotateZ(z_rot_double);

  transform->Translate(x_trans_double, y_trans_double, z_trans_double);

  actor[number]->SetUserTransform(transform);
  ui->qvtkWidget->GetRenderWindow()->Render();


}

void MainWindow::model_details(){

  //Get the model number which was clicked 

  int number = ui -> listWidget -> currentRow();

  //If .STL file is used

  //Turn actor to polydata

  vtkSmartPointer<vtkPolyData> polyData = vtkPolyData::SafeDownCast(actor[number]->GetMapper()->GetInputAsDataSet());

  //Set up fillholesfilter, trianglefilters.

  vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter = vtkSmartPointer<vtkFillHolesFilter>::New();

  fillHolesFilter->SetInputData(polyData);

  fillHolesFilter->SetHoleSize(1000.0);


  vtkSmartPointer<vtkTriangleFilter> triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();

  triangleFilter->SetInputConnection(fillHolesFilter->GetOutputPort());

  vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();

  normals->SetInputConnection(triangleFilter->GetOutputPort());

  normals->ConsistencyOn();

  normals->SplittingOff();

  //Create Mass properties 

  vtkSmartPointer<vtkMassProperties> massProperties = vtkSmartPointer<vtkMassProperties>::New();
  massProperties->SetInputConnection(normals->GetOutputPort());
  massProperties->Update();

  //Mass     label_18
  //Material label_19
  //Volume   label_20
  //Density  label_21

  //Calculate the models volume and change volume label
  //Update the label with volume 

  float volume = massProperties->GetVolume();
  QString Qvolume = QString::number(volume);
  ui->label_20->setText(Qvolume);

  
  //Calculate the models weight

  float weight = massProperties->GetKz();
  QString Qweight = QString::number(weight);
  ui->label_18->setText(Qweight);

  //Calculate the models Surface Area

  float SurfaceArea = massProperties->GetSurfaceArea();
  QString QSurfaceArea = QString::number(SurfaceArea);
  ui->label_21->setText(QSurfaceArea);

  //Find the models colour and update the comboBox_2 with models colour

  //Find color of actor[number]

  /*List of Colors and names:

    0Silver -          0.752941 0.752941  0.752941
    1Red(tomato) -     1        0.3882350 0.278431
    2White -           1        1         1
    3Yellow -          1        1         0
    4Green -           0        0.5019610 0
    5Blue -            0        0         1


  */

  const vtkStdString colorName;

  double *color = actor[number]->GetProperty()->GetColor();

  cout << color[0] << color[1] << color[2] << "\n";

  int index; 

  if(color[0] == 0.752941 && color[1] == 0.752941 && color[2] == 0.752941){
    index = 0;
  }
  else if ( color[0] == 1 && color[1] == 0.3882350 && color[2] == 0.278431){
    index = 1;
  }
  else if ( color[0] == 1 && color[1] == 1 && color[2] == 1){
    index = 2;
  }
  else if ( color[0] == 1 && color[1] == 1 && color[2] == 0){
    index = 3;
  }
  else if ( color[0] == 0 && color[1] == 0.5019610 && color[2] == 0){
    index = 4;
  }
  else if ( color[0] == 0 && color[1] == 0 && color[2] == 1){
    index = 5;
  }


  ui->comboBox_2->setCurrentIndex(index);

}


void MainWindow::changeCamera(){

  //Function called when the spin boxes are changed

  //Get all spin box values

  int cam_x = ui->spinBox->value();
  int cam_y = ui->spinBox_2->value();
  int cam_z = ui->spinBox_3->value();

  int cam_x_rot = ui->spinBox_4->value();
  int cam_y_rot = ui->spinBox_5->value();
  int cam_z_rot = ui->spinBox_6->value();

  //Turn into doubles

  double cam_x_double = (double) cam_x;
  double cam_y_double = (double) cam_y;
  double cam_z_double = (double) cam_z;


  double cam_x_rot_double = (double) cam_x;
  double cam_y_rot_double = (double) cam_x;
  double cam_z_rot_double = (double) cam_x;


  renderer->GetActiveCamera()->SetPosition(cam_x_double, cam_y_double, cam_z_double);
  renderer->GetActiveCamera()->Yaw(cam_z_rot_double);
  renderer->GetActiveCamera()->Elevation(cam_x_rot_double);
  renderer->GetActiveCamera()->Pitch(cam_y_rot_double);




  ui->qvtkWidget->GetRenderWindow()->Render();


}

void MainWindow::Reset_Camera(){

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  ui->qvtkWidget->GetRenderWindow()->Render();

}

void MainWindow::enable_distance_widget(bool checked){

  cout << "enable_distance_widget \n";

  if(checked){

  renderWindowInteractor->SetRenderWindow (renderWindow);

  distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();

  distanceWidget->SetInteractor(renderWindowInteractor);
  distanceWidget->CreateDefaultRepresentation();
  static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())->SetLabelFormat("%-#6.3g mm");

  distanceWidget->On();
  
  

  renderWindow->Render();

  ui->qvtkWidget->GetRenderWindow()->Render();

  

  renderWindowInteractor->Start();
  
}else if(!checked){
  this->disable_distance_widget();
}
  
}

void MainWindow::disable_distance_widget(){

  renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow (renderWindow);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
  
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindowInteractor->Start();


  distanceWidget->Off();

};

void MainWindow::set_bg_colour(){

int color = ui->comboBox->currentIndex();

/* Colour list:


	0: Silver 
	1: Red
	2: White
	3: Yellow 
	4: Green 
	5: Blue

*/

string the_colour;


switch (color){
	case 0:
		the_colour = "silver";
		break;

	case 1:
		the_colour = "tomato";
		break;

	case 2:
		the_colour = "white";
		break;

	case 3:
		the_colour = "yellow";
		break;

	case 4:
		the_colour = "green";
		break;

	case 5:
		the_colour = "blue";
		break;
}


renderer->SetBackground( colors->GetColor3d(the_colour).GetData() );

ui->qvtkWidget->GetRenderWindow()->Render();

}


void MainWindow::Set_Model_Color(){

  int number = ui -> listWidget -> currentRow();

  int color = ui->comboBox_2->currentIndex();

  string the_colour;


switch (color){
  case 0:
    the_colour = "silver";
    break;

  case 1:
    the_colour = "tomato";
    break;

  case 2:
    the_colour = "white";
    break;

  case 3:
    the_colour = "yellow";
    break;

  case 4:
    the_colour = "green";
    break;

  case 5:
    the_colour = "blue";
    break;
}
  actor[number]->GetProperty()->SetColor(colors->GetColor3d(the_colour).GetData());
  ui->qvtkWidget->GetRenderWindow()->Render();
}


void MainWindow::Save_As_STL_File(){


}









