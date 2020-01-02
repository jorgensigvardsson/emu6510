#include "pch.h"
#include "../Emu6510.Library/nop.h"
#include "../Emu6510.Library/opcodes.h"
#include "setup.h"

using namespace emu6510;

TEST(instruction_nop, immediate_addressing_works) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::nop;
	});

	EXPECT_EQ(0, result.cpu.a);
	EXPECT_EQ(0, result.cpu.x);
	EXPECT_EQ(0, result.cpu.y);
	EXPECT_EQ(0, result.cpu.status);
	EXPECT_EQ(opcodes::nop, result.memory[0x0000]);

	const auto zeroVector = std::vector<uint8_t>(memory_size - 1, 0);
	const auto restOfMemory = std::vector<uint8_t>(std::begin(result.memory) + 1, std::end(result.memory));
	EXPECT_EQ(zeroVector, restOfMemory);
}
