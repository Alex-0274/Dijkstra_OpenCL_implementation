# cmake -S src -B build
# cmake --build build
# ./build/opencl_app

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_C_COMPILER clang)

project(app LANGUAGES C)

find_package(OpenCL REQUIRED)

set(SOURCE
	ar_boruvka.c
	ar_CL_boruvka.c
	ar_CL_.c
	ar_CL_dijkstra.c
	ar_dijkstra.c
	ar_disjoint_set.c
	ar_graph.c
	ar_hf.c
	main.c
)
	
set(HEADERS
	../inc/ar_CL_graph_algorithms.h
	../inc/ar_CL_.h
	../inc/ar_disjoint_set.h
	../inc/ar_graph_algorithms.h
	../inc/ar_graph.h
	../inc/ar_hf.h
)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCL_LIBRARIES} PUBLIC -lm)
