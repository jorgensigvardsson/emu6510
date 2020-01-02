#include "pch.h"
#include "../Emu6510.Library/lda.h"
#include "../Emu6510.Library/opcodes.h"
#include "setup.h"

using namespace emu6510;

TEST(instruction_lda, immediate_addressing_works) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_immediate;
		memory[0x0001] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, zp_addressing_works) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, zp_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.x = 1;
		memory[0x0000] = opcodes::lda_zp_x;
		memory[0x0001] = 0xA0;
		memory[0x00A1] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, abs_addressing_works) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_abs;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A00] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, abs_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.x = 1;
		memory[0x0000] = opcodes::lda_abs_x;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A01] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, abs_and_y_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.y = 1;
		memory[0x0000] = opcodes::lda_abs_y;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A01] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, indirect_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.x = 4;
		memory[0x0000] = opcodes::lda_ind_x;
		memory[0x0001] = 0x02;
		memory[0x0006] = 0x00;
		memory[0x0007] = 0x80;
		memory[0x8000] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, indirect_and_y_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.y = 4;
		memory[0x0000] = opcodes::lda_ind_y;
		memory[0x0001] = 0x10;
		memory[0x0010] = 0x00;
		memory[0x0011] = 0x80;
		memory[0x8004] = 0x12;
	});

	EXPECT_EQ(0x12ui8, result.cpu.a);
}

TEST(instruction_lda, zero_flag_is_set_on_zero) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_immediate;
		memory[0x0001] = 0x00;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) == emu6510::status::zero);
}

TEST(instruction_lda, zero_flag_is_cleared_on_nonzero) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_immediate;
		memory[0x0001] = 0x01;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) != emu6510::status::zero);
}

TEST(instruction_lda, negative_flag_is_cleared_on_positive) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_immediate;
		memory[0x0001] = 0x01;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) != emu6510::status::negative);
}

TEST(instruction_lda, negative_flag_is_set_on_negative) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::lda_immediate;
		memory[0x0001] = 0x80;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) == emu6510::status::negative);
}