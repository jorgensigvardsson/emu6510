# CMakeList.txt : CMake project for Emu6510.Application, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Emu6510.Application 
	# Application files
	"application.cpp" 
	"application.h"	
)

# Uncomment to get assembly code: set_target_properties(Emu6510.Application PROPERTIES COMPILE_FLAGS "/Fa /FAs")

target_link_libraries(Emu6510.Application Emu6510.Library)
