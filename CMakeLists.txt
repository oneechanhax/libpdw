
# gui mate
cmake_minimum_required (VERSION 2.6)
project (gui-mate)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/gui-mate/*.c*")
add_library(gui-mate STATIC ${sources})


# Example using xoverlay
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(PNG) # We need to link all this again since we prebuilt them staticly
find_package(GLEW)
find_package(OpenGL)
find_package(X11)
find_package(Freetype)
if(PNG_FOUND AND GLEW_FOUND AND OPENGL_FOUND AND X11_FOUND AND FREETYPE_FOUND)
  project (example)

  file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/example-src/*.c*")
  add_executable(example ${sources})

  # is longe
  target_link_libraries(example gui-mate
                        "${CMAKE_CURRENT_SOURCE_DIR}/example-src/lib/libxoverlay.a"
                        "${CMAKE_CURRENT_SOURCE_DIR}/example-src/lib/libglez.a"
                         ${PNG_LIBRARIES} GL GLU GLEW ${FREETYPE_LIBRARIES}
                         ${X11_X11_LIB} ${X11_Xext_LIB} ${X11_Xfixes_LIB})
endif()
# Wow ez
