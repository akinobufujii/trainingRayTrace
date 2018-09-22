cmake_minimum_required(VERSION 3.0.0)
project(trainingRaytrace VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(./stb)
include_directories(./glm)
add_executable(trainingRaytrace
    main.cpp
    utility/HitableList.cpp
    utility/Ray.cpp
    utility/Sphere.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
