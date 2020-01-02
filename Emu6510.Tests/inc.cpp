#include "pch.h"
#include "../Emu6510.Library/inc.h"
#include "../Emu6510.Library/instrfetch.h"
#include "../Emu6510.Library/memory.h"

using namespace emu6510;

TEST(Instruction_INC, ZP_Addressing_Works) {
	auto memory = emu6510::memory(64 * 1024);
	memory[0x0000] = emu6510::opcodes::inc_zp;
	memory[0x0001] = 0xA0;
	memory[0x00A0] = 123;

	auto cpu = emu6510::cpu();
	auto& instruction = fetch(cpu, memory);
	instruction.execute(cpu, memory);

    EXPECT_EQ(124ui8, memory[0x00A0]);
}