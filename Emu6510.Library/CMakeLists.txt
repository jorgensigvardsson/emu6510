cmake_minimum_required (VERSION 3.8)

add_library(Emu6510.Library SHARED
    # Hardware emulation abstractions
	"memory.h" 
	"memory.cpp" 
	"instrfetch.h" 
	"instrfetch.cpp"
	"cpu.h"
	"instruction.h"
	"instruction.cpp"
	"opcodes.h"
	"instructions.h"
	"bits.h"

	# instructions
	"adc.h"
	"beq.h"
	"inc.h"
	"lda.h"
	"nop.h"
)