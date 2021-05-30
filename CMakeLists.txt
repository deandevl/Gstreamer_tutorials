cmake_minimum_required(VERSION 3.19)
project(Gstreamer_tutorials)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    F:/gstreamer/1.0/msvc_x86_64/include/gstreamer-1.0
    F:/gstreamer/1.0/msvc_x86_64/include/glib-2.0
    F:/gstreamer/1.0/msvc_x86_64/lib/glib-2.0/include
    F:/gstreamer/1.0/msvc_x86_64/lib/gstreamer-1.0/include
)

link_libraries(
    F:/gstreamer/1.0/msvc_x86_64/lib/gstreamer-1.0.lib
    F:/gstreamer/1.0/msvc_x86_64/lib/gobject-2.0.lib
    F:/gstreamer/1.0/msvc_x86_64/lib/glib-2.0.lib
)

add_executable(get_version src/get_version.cpp)
add_executable(auto_pipeline src/auto_pipeline.cpp)
add_executable(manual_pipeline src/manual_pipeline.cpp)
add_executable(dynamic_pipeline src/dynamic_pipeline.cpp)
# add_executable(dynamic_pipeline_2 src/dynamic_pipeline_2.cpp)
add_executable(dynamic_pipeline_3 src/dynamic_pipeline_3.cpp)

message("Starting to build Gstreamer_tutorials")