cmake_minimum_required(VERSION 3.0.2)
project(image_estimate)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)


# add your opencvlib path here !
Set(OpenCV_DIR "/home/dango/dango/lib/opencv/opencv_lib/opencv3/share/OpenCV") # important find opencv version
Set(OpenCV_INCLUDE_DIRS "/home/dango/dango/lib/opencv/opencv_lib/opencv3/include")
Set(OpenCV_LIBRARIES "/home/dango/dango/lib/opencv/opencv_lib/opencv3/lib")

find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES image_estimate
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(image_estimate_node
    src/image_estimate_node.cpp
    src/ImageAssessMetric.cpp
    )

target_link_libraries(image_estimate_node ${catkin_LIBRARIES} ${OpenCV_LIBS} ) 


