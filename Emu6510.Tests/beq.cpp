#include "pch.h"
#include "../Emu6510.Library/beq.h"
#include "../Emu6510.Library/opcodes.h"
#include "setup.h"

using namespace emu6510;

TEST(instruction_beq, zero_flag_set_jump_forward_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.pc = 0x100;
		cpu.status = status::zero;
		memory[0x0100] = opcodes::beq;
		memory[0x0101] = 0x10;
	});

	EXPECT_EQ(0x0112ui16, result.cpu.pc);
}

TEST(instruction_beq, zero_flag_not_set_jump_forward_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.pc = 0x100;
		cpu.status = 0;
		memory[0x0100] = opcodes::beq;
		memory[0x0101] = 0x10;
	});

	EXPECT_EQ(0x0102ui16, result.cpu.pc);
}

TEST(instruction_beq, zero_flag_set_jump_backward_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.pc = 0x100;
		cpu.status = status::zero;
		memory[0x0100] = opcodes::beq;
		memory[0x0101] = 0xF6;
	});

	EXPECT_EQ(0x00F8ui16, result.cpu.pc);
}

TEST(instruction_beq, zero_flag_not_set_jump_backward_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.pc = 0x100;
		cpu.status = 0;
		memory[0x0100] = opcodes::beq;
		memory[0x0101] = 0xF6;
	});

	EXPECT_EQ(0x0102ui16, result.cpu.pc);
}
