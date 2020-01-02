// Emu6510.Application.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "../Emu6510.Library/memory.h"
#include "../Emu6510.Library/cpu.h"
#include "../Emu6510.Library/instrfetch.h"
#include "../Emu6510.Library/opcodes.h"

using namespace std;

void load_application(emu6510::memory& memory) {
	memory[0x0800] = emu6510::opcodes::lda_immediate;
	memory[0x0801] = 0x00;
	memory[0x0802] = emu6510::opcodes::beq;
	memory[0x0803] = 0x10;
	memory[0xFFFC] = 0x00;
	memory[0xFFFD] = 0x08;
}

int main()
{
	auto memory = emu6510::memory(64 * 1024);
	load_application(memory);
	
	auto cpu = emu6510::cpu{};
	cpu.status = 0x00;
	cpu.a = 0;
	cpu.x = 1;
	cpu.y = 0;
	cpu.sp = 0xFF;
	cpu.pc = memory.read_word(0xFFFC);
	cpu.cycle_counter = 0;

	try {
		for (;;) {
			auto& instruction = fetch(cpu, memory);
			instruction.execute(cpu, memory);
		}
	} catch(emu6510::bad_instruction& ex) {
		cout << "Bad instruction at " << ex.ptr << endl;
	}
	
	cout << "Hello CMake." << endl;
	return 0;
}
