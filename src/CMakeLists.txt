cmake_minimum_required(VERSION 2.8)
project(Project1)

# Check compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

  set(CLANG_CXX_FLAGS "-std=c++11 -m64 -O3 -funroll-loops")
  set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-narrowing")
  set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-register")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  
  # UNIX
  if(UNIX)
    set(GCC_CXX_FLAGS "-std=gnu++11 -m64 -O3 -funroll-loops")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -fopenmp")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXi")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXxf86vm")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXinerama") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXcursor") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXfixes") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrandr") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXext")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrender") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lX11")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lpthread") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lxcb") 
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXau") 
  endif(UNIX)

  # Windows
  # if(WIN32)
  #   set(GCC_CXX_FLAGS "-std=gnu++11 -O3 -funroll-loops -fopenmp")
  # endif(WIN32)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")

endif()

# Add modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

# Find dependencies
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(CMU462 REQUIRED)

# Install settings
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../")

# Building on osx 
if(APPLE)
  include_directories( "/System/Library/Frameworks" )
  find_library (COCOA_LIBRARIES Cocoa)
  find_library (IOKIT_LIBRARIES IOkit)
  find_library (COREVIDEO_LIBRARIES CoreVideo)
endif(APPLE)

# Set include directories
include_directories(
    ${FREETYPE_INCLUDE_DIRS}
    ${CMU462_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
)

# Set link directories
link_directories(
    ${FREETYPE_LIBRARY_DIRS}
    ${CMU462_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
    ${GLFW_LIBRARY_DIRS}
)

# Set drawsvg source
set(CMU462_DRAWSVG_SOURCE
    svg.cpp
    png.cpp
    texture.cpp
    viewport.cpp
    triangulation.cpp
#    hardware_renderer.cpp
    software_renderer.cpp
    drawsvg.cpp
    main.cpp
)

# Set drawsvg header
set(CMU462_DRAWSVG_HEADER
    svg.h
    png.h
    texture.h
    viewport.h
    triangulation.h
    hardware_renderer.h
    software_renderer.h
    drawsvg.h
)

# Import hardware renderer
include(hardware/hardware.cmake)

# Import drawsvg reference
include(reference/reference.cmake)

# drawsvg executable
add_executable( drawsvg
    ${CMU462_DRAWSVG_SOURCE}
    ${CMU462_DRAWSVG_HEADER}
)

# Link drawsvg executable (static link reference solution)
target_link_libraries( drawsvg drawsvg_hdwr drawsvg_ref
    ${FREETYPE_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${CMU462_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)

# Frameworks required on osx
if (APPLE)
  target_link_libraries(drawsvg  
    ${COCOA_LIBRARIES}
    ${IOKIT_LIBRARIES}
    ${COREVIDEO_LIBRARIES}
  )
endif(APPLE)

install(TARGETS drawsvg DESTINATION .)
