cmake_minimum_required(VERSION 3.17)
project(Console)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp code/Interfaces/Render.cpp 
code/Objects/Object.cpp code/Objects/Entity/Colliders/Collider.cpp
code/Objects/Entity/Entity.cpp code/Objects/Entity/Player.cpp
code/Interfaces/World.cpp code/Interfaces/Input.cpp
code/Interfaces/SMath.cpp code/Interfaces/Settings.cpp
code/Objects/Blocks/Block.cpp code/Objects/Blocks/Wall.cpp
code/Objects/Entity/Enemies/Enemy.cpp code/Visual/Shape.cpp
code/Interfaces/ForSFML.cpp code/Visual/VisualStructs.cpp
code/Objects/Camers/Camera2D.cpp code/Objects/Camers/Camera.cpp
code/Global.cpp code/Objects/Camers/CameraR3D.cpp
code/Interfaces/Loger.cpp code/Algoritms/GeometryAlgoritms.cpp
code/Objects/Entity/Colliders/ColliderPolygon.cpp 
code/Objects/Entity/Colliders/BVH.cpp code/Objects/Entity/Colliders/ColliderRect.cpp
code/Primitives/Primitives2D.cpp code/Objects/Entity/Colliders/ColliderCircle.cpp
code/Objects/Entity/Colliders/ColliderLine.cpp)

include_directories(c:/SFML-2.6.2/include)

set(SFML_ROOT c:/SFML-2.6.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    
endif()