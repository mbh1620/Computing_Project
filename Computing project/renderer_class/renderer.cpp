#include <iostream>
#include "renderer.hpp"

//----------------------------------------------------
//
//						Renderer Class
//	
//----------------------------------------------------



renderer::renderer(model& _the_model){
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

void renderer::open_file(){

}

void renderer::close_file(){

}

void renderer::file_start(){
	ofstream outfile;
	outfile.open(filename);

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
  //For all the tetrahedrons in the model send their information to the render file
  
}

void renderer::file_hexahedrons(){
  //For all the hexahedrons in the model send their information to the render file
}

void renderer::file_pyramids(){
  //For all the pyramids in the model send their information to the render file

}

void renderer::file_end(){

}