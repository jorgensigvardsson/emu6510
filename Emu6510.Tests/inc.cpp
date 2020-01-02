#include "pch.h"
#include "../Emu6510.Library/inc.h"
#include "../Emu6510.Library/instrfetch.h"
#include "../Emu6510.Library/memory.h"

#include "setup.h"

using namespace emu6510;

TEST(Instruction_INC, ZP_Addressing_Works) {
	auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 123;
	});
	
    EXPECT_EQ(124ui8, result.memory[0x00A0]);
}

TEST(Instruction_INC, ZP_And_X_Addressing_Works) {
	auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.x = 1;

		memory[0x0000] = opcodes::inc_zp_x;
		memory[0x0001] = 0xA0;
		memory[0x00A1] = 123;
	});
	EXPECT_EQ(124ui8, result.memory[0x00A1]);
}