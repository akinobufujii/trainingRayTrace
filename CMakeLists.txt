cmake_minimum_required(VERSION 3.0.0)
project(trainingRaytrace VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/stb)
include_directories(${PROJECT_SOURCE_DIR}/glm)
add_executable(trainingRaytrace
    main.cpp
    utility/Camera.cpp
    utility/DielectricMaterial.cpp
    utility/HitableList.cpp
    utility/LambertMaterial.cpp
    utility/MetalMaterial.cpp
    utility/Other.cpp
    utility/Ray.cpp
    utility/Sphere.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "-std=c++17")
include(CPack)
