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
