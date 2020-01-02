#include "pch.h"
#include "../Emu6510.Library/adc.h"
#include "../Emu6510.Library/opcodes.h"
#include "setup.h"

using namespace emu6510;

TEST(instruction_adc, immediate_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, zp_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		memory[0x0000] = opcodes::adc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, zp_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		cpu.x = 1;
		memory[0x0000] = opcodes::adc_zp_x;
		memory[0x0001] = 0xA0;
		memory[0x00A1] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, abs_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		memory[0x0000] = opcodes::adc_abs;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A00] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, abs_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		cpu.x = 1;
		memory[0x0000] = opcodes::adc_abs_x;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A01] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, abs_and_y_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		cpu.y = 1;
		memory[0x0000] = opcodes::adc_abs_y;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A01] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, indirect_and_x_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		cpu.x = 4;
		memory[0x0000] = opcodes::adc_ind_x;
		memory[0x0001] = 0x02;
		memory[0x0006] = 0x00;
		memory[0x0007] = 0x80;
		memory[0x8000] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, indirect_and_y_addressing_works) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 1;
		cpu.y = 4;
		memory[0x0000] = opcodes::adc_ind_y;
		memory[0x0001] = 0x10;
		memory[0x0010] = 0x00;
		memory[0x0011] = 0x80;
		memory[0x8004] = 0x12;
	});

	EXPECT_EQ(0x13ui8, result.cpu.a);
}

TEST(instruction_adc, zero_flag_is_set_on_zero) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0xFF;

		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x01;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) == emu6510::status::zero);
}

TEST(instruction_adc, zero_flag_is_cleared_on_nonzero) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0;
		cpu.status = status::zero;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x01;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) != emu6510::status::zero);
}

TEST(instruction_adc, negative_flag_is_cleared_on_positive) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0xFF;
		cpu.status = status::negative;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x01;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) != emu6510::status::negative);
}

TEST(instruction_adc, negative_flag_is_set_on_negative) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0x7F;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x1;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) == emu6510::status::negative);
}

TEST(instruction_adc, carry_flag_is_set_when_carry) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0xFF;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x1;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::carry) == emu6510::status::carry);
}

TEST(instruction_adc, carry_flag_is_cleared_when_no_carry) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0x00;
		cpu.status = status::carry;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x1;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::carry) != emu6510::status::carry);
}

TEST(instruction_adc, overflow_flag_is_set_when_overflow_positive) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0x7F;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x1;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::overflow) == emu6510::status::overflow);
}

TEST(instruction_adc, overflow_flag_is_cleared_when_no_overflow) {
	const auto result = run_one_instruction([](auto& cpu, auto& memory) {
		cpu.a = 0x00;
		cpu.status = status::overflow;
		memory[0x0000] = opcodes::adc_immediate;
		memory[0x0001] = 0x1;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::overflow) != emu6510::status::overflow);
}