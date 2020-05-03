# ![logo](https://github.com/mbh1620/Computing_Project/blob/master/Computing%20project/Images/doxylogo.png)3D Viewer Project. 

![build status](https://travis-ci.com/mbh1620/Computing_Project.svg?token=GqtXXcs7xDsCW7iqqCwg&branch=master)

## To Build the project and create an installer:
```
mkdir ./Computing project/build
```
```
cd ./Computing project/build
```
```
cmake ../
```
```
make 
```
```
macdeployqt 3Dviewer.app
```
```
cmake --build . --target package
```
The installer should then be created.

### Future Update

I have added a simulation tab to the gui, however this is not working yet. This would be a future upgrade for this project to allow the Aerospace company to perform computational fluid dynamic simulations and wind tunnel simulations. To implement this part I would need to add some more classes to the libraries to solve partial differential equations in 3D. 
