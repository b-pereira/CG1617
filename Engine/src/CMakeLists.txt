cmake_minimum_required(VERSION 2.8)

# Project Name
PROJECT(Engine)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES} )
include_directories(${IL_INCLUDE_DIR})



set (CMAKE_CXX_STANDARD 11)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(${PROJECT_NAME} main.cpp 
                              Group.h   
                              Point3d.cpp  
                              Rotation.cpp
	                          Scale.cpp  
	                          tinyxml2.cpp  
	                          Transformation.cpp  
	                          Translation.cpp  
	                          Translation.h  
	                          Triangle.h
                              Group.cpp  
                              Point3d.h    
                              Rotation.h    
                              Scale.h    
                              tinyxml2.h    
                              Transformation.h    
                              Triangle.cpp
                              AnimatedRotation.h 
                              AnimatedRotation.cpp 
                              AnimatedTranslation.cpp  
                              AnimatedTranslation.h 
                              Catmull-Rom.cpp 
                              Catmull-Rom.h 
                              MatDiffuse.cpp 
                              MatDiffuse.h 
                              MatSpecular.cpp 
                              MatSpecular.h 
                              MatEmissive.cpp 
                              MatEmissive.h 
                              MatAmbient.cpp 
                              MatAmbient.h 
                              Materials.cpp 
                              Materials.h 
                              RGBA.cpp 
                              RGBA.h
                              )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


