project(Converter)
cmake_minimum_required(VERSION 2.8)
find_package(Boost REQUIRED)
aux_source_directory(. SRC_LIST)

set(Converter_VERSION_MAJOR 1)
set(Converter_VERSION_MINOR 0)

#--------------------------------------------------
# add the executable

add_executable(${PROJECT_NAME} ${SRC_LIST})

#--------------------------------------------------
# add the install target

install (TARGETS Converter DESTINATION /usr/bin)
