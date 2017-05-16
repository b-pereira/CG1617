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
                              tinyxml2.cpp
                              tinyxml2.h
                              Group.h  
                              Group.cpp   
                              Point3d.cpp  
                              Point3d.h 
                              Point4d.cpp  
                              Point4d.h 
                              RGBA.cpp 
                              RGBA.h
                              Triangle.h
                              Triangle.cpp
                              Transformation.h 
                              Transformation.cpp 
                              Translation.h  
                              Translation.cpp  
                              Rotation.h
                              Rotation.cpp
                              Scale.h
                              Scale.cpp 
                              AnimatedRotation.h 
                              AnimatedRotation.cpp
                              AnimatedTranslation.h 
                              AnimatedTranslation.cpp  
                              Catmull-Rom.h
                              Catmull-Rom.cpp 
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
                              LightDiffuse.cpp 
                              LightDiffuse.h 
                              LightSpecular.cpp 
                              LightSpecular.h 
                              LightAmbient.cpp 
                              LightAmbient.h
                              LightProperty.cpp 
                              LightProperty.h
                              Light.h 
                              Light.cpp
                              DirectionalLight.h 
                              DirectionalLight.cpp
                              FixedLight.h 
                              FixedLight.cpp
                              Spotlight.h 
                              Spotlight.cpp
                              )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


