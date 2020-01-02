cmake_minimum_required (VERSION 3.8)

add_executable(Emu6510.Tests
	"tests.h"
	"tests.cpp"
)

target_link_libraries(Emu6510.Tests Emu6510.Library)

add_test(NAME Emu6510.Tests COMMAND $<TARGET_FILE:Emu6510.Tests>)
add_test(NAME Emu6510.Tests2 COMMAND $<TARGET_FILE:Emu6510.Tests>)
