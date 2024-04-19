# CMakeList.txt : CMake project for CMakeProjekt3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeProjekt3")

#add_subdirectory(pybind11)
#pybind11_add_module(cmake_example src/main.cpp)

# Add source to this project's executable.
add_executable (CMakeProjekt3 "CMakeProjekt3.cpp" "CMakeProjekt3.h")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProjekt3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
