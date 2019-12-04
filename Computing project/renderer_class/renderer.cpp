#include <iostream>
#include "renderer.hpp"

//----------------------------------------------------
//
//						Renderer Class
//	
//----------------------------------------------------



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

	string data = "<html>\n"
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
    "<ul style='list-style-type: none'>\n"
    "<li><input type='color' value='#757575'>Aluminium</li>\n"
    "<li><input type='color' value='#cc9316'>Copper</li>\n"
    "<li><input type='color' value='#bababa'>Steel</li>\n"
    "</ul>\n"
    "<h3>Cells</h3>\n"
    "<h3>Vectors</h3>\n"
    "<ul>\n"
    "<li>\n"
    "</ul>\n"
    "<script src='js/three.js'></script>\n"
    "<script src='js/OrbitControls.js'></script>\n"
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
  outfile << data << endl;
}

void renderer::file_tetrahedrons(){
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

    

    //Extract the information about the tetrahedron cells 


    /* Extract the vertices from the cell
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
        
    /*Extract the material from the cell
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

  data = "function makeInstance(geometry, color, x) {\n"
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
    outfile << "makeInstance(geometry"<< a <<", 0x44FF44, 0),\n" <<endl;
  }

  outfile << "];\n";
  
}

void renderer::file_hexahedrons(){
  //For all the hexahedrons in the model send their information to the render file
}

void renderer::file_pyramids(){
  //For all the pyramids in the model send their information to the render file

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