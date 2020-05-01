cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
foreach(p
CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files 
)
if(POLICY ${p}) 
cmake_policy(SET ${p} NEW)
endif() 
endforeach()
PROJECT( 3DViewer )

set(CPACK_GENERATOR "DragNDrop")

include(CPack)

include(CTest)

# The CMake build process might generate some new files in the current # directory. This makes sure they can be found.

set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc # if it is needed. moc.exe can be found in Qt's bin directory. # We'll look at what moc does later.

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# Find the Qt widgets package. This locates the relevant include and # lib directories, and the necessary static libraries for linking.


 
find_package( Qt5Widgets )

get_target_property(QtWidgets_location Qt5::Widgets LOCATION)



set( UIS mainwindow.ui ) 
qt5_wrap_ui( UI_Srcs ${UIS} )

# Also link to VTK

set(MACOSX_BUNDLE_ICON_FILE logo.icns)

set(3DViewer_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Images/logo.icns)

set_source_files_properties(${3DViewer_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )




add_library( 3d_viewer_libs ./cell_class/cell.cpp 
			    ./material_class/material.cpp
			    ./model_class/model.cpp
			    ./vector_class/vector.cpp
			    ./renderer_class/renderer.cpp)


#Add tests and test executables here



target_link_libraries(test1 3d_viewer_libs)
target_link_libraries(test2 3d_viewer_libs)
target_link_libraries(test4 3d_viewer_libs)

add_executable(test1 ./Computing\ project/Test\ Mains/cell_test.cpp)
add_executable(test2 ./Computing\ project/Test\ Mains/material_test.cpp)

add_executable(test4 ./Computing\ project/Test\ Mains/Vector_test.cpp)

add_test(test1 test1)
add_test(test2 test2)
add_test(test4 test4)


# Define the executable output and its sources
add_executable( 3DViewer MACOSX_BUNDLE ${3DViewer_ICON} QT_Classes/vtk_renderer.cpp 
QT_Classes/mainwindow.cpp
                    QT_Classes/mainwindow.h
                    QT_Classes/mainwindow.ui
                    ${UI_Srcs}
                    ${QRC_Srcs}
                    )



                    
    # Tell CMake that the executable depends on the Qt::Widget libraries.

target_link_libraries( 3DViewer Qt5::Widgets)


    # Tell CMake that the executable depends on the VTK libraries

target_link_libraries( 3DViewer ${VTK_LIBRARIES} )
target_link_libraries( 3DViewer 3d_viewer_libs)



install(TARGETS 3DViewer 3d_viewer_libs
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ./3DViewer.app/lib
    ARCHIVE DESTINATION ./3DViewer.app/lib/static
    BUNDLE DESTINATION ./
    )

INSTALL(DIRECTORY ./Test\ Objects DESTINATION ./3DViewer.app)
INSTALL(DIRECTORY ./Test\ Objects DESTINATION ./)



set_target_properties(3DViewer 
PROPERTIES
MACOSX_BUNDLE_BUNDLE_NAME "3DViewer"
)

include(BundleUtilities)
include(InstallRequiredSystemLibraries)
include(DeployQt5.cmake)

get_filename_component(qt_dlls_dir "${QtWidgets_location}" PATH)
get_filename_component(qt_dlls_dir "${qt_dlls_dir}" PATH)
get_filename_component(vtk_dlls_dir "${vtk_location}" PATH)

set(dirs2 "${vtk_dlls_dir}")

set(dirs "${qt_dlls_dir}")

install_qt5_executable("3DViewer.app" "" "" "${dirs}" "" "")


