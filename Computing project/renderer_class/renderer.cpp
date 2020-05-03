#include <iostream>
#include "renderer.hpp"

//----------------------------------------------------
//
//						      Renderer Class
//	
//----------------------------------------------------

// author Matt Haywood 



renderer::renderer(model _the_model){
	the_model = _the_model;
	filename = "render.html";
}

renderer::~renderer(){

}

renderer::renderer(const renderer& a){

}

renderer& renderer:: operator=(const renderer& a){
	return *this;
}

model& renderer::get_model(){
  return the_model;
}

void renderer::open_file(){
  outfile.open(filename);
}

void renderer::close_file(){
  outfile.close();
}

void renderer::file_start(){

	outfile << "<html>\n"
	"<head>\n"
    "<title>3D Model Viewer</title>\n"
    "<link rel='stylesheet' href='style.css'>\n"
	"</head>\n"
	"<body>\n"
   	"\n"
    "<h1 style='font-family: helvetica'>3D Model Viewer</h1>\n"
    "\n"
	"<canvas id='c' style='height:600;width:auto'></canvas>\n"
  	"</br>\n"
    "<label style='font-family: helvetica'>Choose file to upload</label>\n"
    "<input type='file'>\n"
    "<h3>Materials</h3>\n"
    "<ul style='list-style-type: none'>\n";

    for(int i = 0; i < the_model.get_list_of_materials().size(); i++){
      outfile << "<li><input type='color' value='#"<<the_model.get_list_of_materials()[i].getColour() << "'>"<< the_model.get_list_of_materials()[i].getName() << "</li>\n";
    }

    outfile <<"</ul>\n"
    "<h3>Cells</h3>\n"
    "<h3>Vectors</h3>\n"
    "<ul>\n"
    "<li>\n"
    "</ul>\n"
    "<script src='https://cdnjs.cloudflare.com/ajax/libs/three.js/110/three.js'></script>\n"
    "<script src='https://cdn.jsdelivr.net/npm/three-orbitcontrols@2.110.3/OrbitControls.min.js'></script>\n"
    "\n"
	"<script>\n"
	"function main() {\n"
  "const canvas = document.querySelector('#c');\n"
  "const renderer = new THREE.WebGLRenderer({canvas});\n"
  "const fov = 75;\n"
  "const aspect = 2;  // the canvas default\n"
  "const near = 0.1;\n"
  "const far = 100;\n"
  "const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);\n"
  "camera.position.z = 5;\n"
  
  "const scene = new THREE.Scene();\n"
  "var controls = new THREE.OrbitControls(camera, renderer.domElement);\n"
  "meshfloor = new THREE.Mesh(\n"
    "new THREE.PlaneGeometry(20,20,10,10),\n"
    "new THREE.MeshBasicMaterial({color:0xFFFFFF, wireframe:true})\n"
    ")\n"
"meshfloor.rotation.x += Math.PI / 2;\n"
  "scene.add(meshfloor);\n"
  "{\n"
    "const color = 0xFFFFFF;\n"
    "const intensity = 1;\n"
    "const light = new THREE.DirectionalLight(color, intensity);\n"
    "light.position.set(-1, 2, 4);\n"
    "scene.add(light);\n"
  "}\n";
}

void renderer::file_tetrahedrons(){

  /*! For all the tetrahedrons in the model, send their information to the render file.*/
  string data;
  //For all the tetrahedrons in the model send their information to the render file
  //Create a list of tetrahedrons in the model 
  deque<cell> list_of_tetrahedrons;
  for(int i = 0; i < the_model.get_list_of_cells().size(); i++){
    if(the_model.get_list_of_cells()[i].get_shape() == 't'){
      list_of_tetrahedrons.push_back(the_model.get_list_of_cells()[i]);
    }
  }

  

  for(int i = 0; i < list_of_tetrahedrons.size(); i++){

    outfile << "const geometry" << i <<" = new THREE.Geometry();\n"
  "geometry" << i <<".vertices.push(\n";

    

    ///Extract the information about the tetrahedron cells 


    /*! Extract the vertices from the cell
      - Extract the 'x' coordinate from each vertex
      - Extract the 'y' coordinate from each vertex
      - Extract the 'z' coordinate from each vertex
      - Extract the 'id' from each vertex
    */
    deque<Vector> vertices_from_tetrahedron;

    vertices_from_tetrahedron = list_of_tetrahedrons[i].get_vertices();

    for(int z = 0; z < vertices_from_tetrahedron.size(); z++){
      outfile << "new THREE.Vector3("<< vertices_from_tetrahedron[z].get('x') <<","<< vertices_from_tetrahedron[z].get('y') << "," << vertices_from_tetrahedron[z].get('z') << "),  // 0\n";
    
    }

    data = ");\n";

    outfile << data << endl;
        
    /*! Extract the material from the cell
      - Extract the colour of material from material.
    */

    outfile << "geometry"<<i<<".faces.push(\n"
     "new THREE.Face3(0, 3, 1),\n"
     "new THREE.Face3(1, 2, 3),\n"
     "new THREE.Face3(1, 3, 2),\n"
     "new THREE.Face3(0, 2, 3),\n"
     "new THREE.Face3(0, 1, 2),\n"
    ");\n";

  }

  data = "function makeInstancet(geometry, color, x) {\n"
    "const material = new THREE.MeshBasicMaterial({color});\n"

    "const tetra = new THREE.Mesh(geometry, material);\n"
    "scene.add(tetra);\n"

    "tetra.position.x = x;\n"
    "return tetra;\n"
  "}\n"
  "\n"
  "\n"
  "const tetras = [\n";

  outfile << data << endl;

  for( int a = 0; a < list_of_tetrahedrons.size(); a++){
    outfile << "makeInstancet(geometry"<< a <<", 0x"<< list_of_tetrahedrons[a].get_material().getColour() << ", 0),\n" <<endl;
  }

  outfile << "];\n";
  
}

void renderer::file_hexahedrons(){

  /*! For all the hexahedrons in the model send their information to the renderer file.*/

  string data;
  //For all the tetrahedrons in the model send their information to the render file
  //Create a list of tetrahedrons in the model 
  deque<cell> list_of_hexahedrons;
  for(int i = 0; i < the_model.get_list_of_cells().size(); i++){
    if(the_model.get_list_of_cells()[i].get_shape() == 'h'){
      list_of_hexahedrons.push_back(the_model.get_list_of_cells()[i]);
    }
  }



  for(int i = 0; i < list_of_hexahedrons.size(); i++){

    outfile << "const geometry_h" << i <<" = new THREE.Geometry();\n"
  "geometry_h" << i <<".vertices.push(\n";

  //Extract the information about the hexahedrons

  /*! Extract the vertices from the hexahedrons */

  deque<Vector> vertices_from_hexahedron;



    vertices_from_hexahedron = list_of_hexahedrons[i].get_vertices();

    for(int z = 0; z < vertices_from_hexahedron.size(); z++){
      outfile << "new THREE.Vector3("<< vertices_from_hexahedron[z].get('x') <<","<< vertices_from_hexahedron[z].get('y') << "," << vertices_from_hexahedron[z].get('z') << "),  // 0\n";
    
    }

    data = ");\n";

    outfile << data << endl;

    outfile << "geometry_h"<<i<<".faces.push(\n"
     "// front\n"
     "new THREE.Face3(0, 3, 2),\n"
     "new THREE.Face3(0, 1, 3),\n"
     "// right\n"
     "new THREE.Face3(1, 7, 3),\n"
     "new THREE.Face3(1, 5, 7),\n"
     "// back\n"
     "new THREE.Face3(5, 6, 7),\n"
     "new THREE.Face3(5, 4, 6),\n"
     "// left\n"
     "new THREE.Face3(4, 2, 6),\n"
     "new THREE.Face3(4, 0, 2),\n"
     "// top\n"
     "new THREE.Face3(2, 7, 6),\n"
     "new THREE.Face3(2, 3, 7),\n"
     "// back\n"
     "new THREE.Face3(4, 1, 0),\n"
     "new THREE.Face3(4, 5, 1),\n"
    ");\n";
  }

  data = "function makeInstanceh(geometry, color, x) {\n"
    "const material = new THREE.MeshBasicMaterial({color});\n"

    "const hexa = new THREE.Mesh(geometry, material);\n"
    "scene.add(hexa);\n"

    "hexa.position.x = x;\n"
    "return hexa;\n"
  "}\n"
  "\n"
  "\n"
  "const hexas = [\n";

  outfile << data << endl;

  for( int a = 0; a < list_of_hexahedrons.size(); a++){
    outfile << "makeInstanceh(geometry_h"<< a <<", 0x" << list_of_hexahedrons[a].get_material().getColour() << ", 0),\n" <<endl;
  }

  outfile << "];\n";


}

void renderer::file_pyramids(){
  /*! For all the pyramids in the model send their information to the render file */
  string data;

  //For all the pyramids in the model send their information to the render file
  //Create a list of pyramids in the model 
  deque<cell> list_of_pyramids;
  for(int i = 0; i < the_model.get_list_of_cells().size(); i++){
    if(the_model.get_list_of_cells()[i].get_shape() == 'p'){
      list_of_pyramids.push_back(the_model.get_list_of_cells()[i]);
    }
  }


  for(int i = 0; i < list_of_pyramids.size(); i++){

    outfile << "const geometry_p" << i <<" = new THREE.Geometry();\n"
  "geometry_p" << i <<".vertices.push(\n";

  //Extract the information about the hexahedrons

  /*! Extract the vertices from the hexahedrons */

  deque<Vector> vertices_from_pyramids;

  vertices_from_pyramids = list_of_pyramids[i].get_vertices();

    for(int z = 0; z < vertices_from_pyramids.size(); z++){
      outfile << "new THREE.Vector3("<< vertices_from_pyramids[z].get('x') <<","<< vertices_from_pyramids[z].get('y') << "," << vertices_from_pyramids[z].get('z') << "),  // 0\n";
    
    }

    data = ");\n";

    outfile << data << endl;

    outfile << "geometry_p"<<i<<".faces.push(\n"
     "// front\n"
     "new THREE.Face3(0, 1, 3),\n"
     "// right\n"
     "new THREE.Face3(1, 2, 3),\n"
     "// back\n"
     "new THREE.Face3(2, 3, 4),\n"
     "// left\n"
     "new THREE.Face3(4, 0, 3),\n"
     "// bottom\n"
     "new THREE.Face3(0, 1, 2),\n"
     "new THREE.Face3(2, 0, 4),\n"
    ");\n";
  }

  data = "function makeInstancep(geometry, color, x) {\n"
    "const material = new THREE.MeshBasicMaterial({color});\n"

    "const pyra = new THREE.Mesh(geometry, material);\n"
    "scene.add(pyra);\n"

    "pyra.position.x = x;\n"
    "return pyra;\n"
  "}\n"
  "\n"
  "\n"
  "const pyramids = [\n";

  outfile << data << endl;

  for( int a = 0; a < list_of_pyramids.size(); a++){
    outfile << "makeInstancep(geometry_p"<< a <<", 0x" << list_of_pyramids[a].get_material().getColour() << ", 0),\n" <<endl;
  }

  outfile << "];\n";

}

void renderer::file_end(){
 outfile << "function resizeRendererToDisplaySize(renderer) {\n"
    "const canvas = renderer.domElement;\n"
    "const width = canvas.clientWidth;\n"
    "const height = canvas.clientHeight;\n"
    "const needResize = canvas.width !== width || canvas.height !== height;\n"
    "if (needResize) {\n"
    "  renderer.setSize(width, height, false);\n"
    "}\n"
    "return needResize;\n"
  "}\n"
  "function render(time) {\n"
    "time *= 0.001;\n"
    "if (resizeRendererToDisplaySize(renderer)) {\n"
      "const canvas = renderer.domElement;\n"
      "camera.aspect = canvas.clientWidth / canvas.clientHeight;\n"
      "camera.updateProjectionMatrix();\n"
    "}\n"
    "tetras.forEach((tetra, ndx) => {\n"
      "const speed = 1 + ndx * .1;\n"
      "const rot = time * speed;\n"
      "tetra.rotation.x = 0;\n"
      "tetra.rotation.y = 0;\n"
    "});\n"
    "hexas.forEach((hexa, ndx) => {\n"
      "const speed = 1 + ndx * .1;\n"
      "const rot = time * speed;\n"
      "hexa.rotation.x = 0;\n"
      "hexa.rotation.y = 0;\n"
    "});\n"
    "renderer.render(scene, camera);\n"
    "requestAnimationFrame(render);\n"
  "}\n"
  "requestAnimationFrame(render);\n"
"}\n"
"main();\n"
"</script>\n"
  "</body>\n"
  "</html>\n";
}