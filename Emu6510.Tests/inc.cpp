#include "pch.h"
#include "../Emu6510.Library/inc.h"
#include "../Emu6510.Library/opcodes.h"
#include "setup.h"

using namespace emu6510;

namespace {
	auto zp_addressing_setup = setup_function([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 123;
	});

	auto zp_and_x_addressing_setup([](auto& cpu, auto& memory) {
		cpu.x = 1;

		memory[0x0000] = opcodes::inc_zp_x;
		memory[0x0001] = 0xA0;
		memory[0x00A1] = 123;
	});

	auto abs_addressing_setup([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_abs;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A00] = 123;
	});

	auto abs_and_x_addressing_setup([](auto& cpu, auto& memory) {
		cpu.x = 1;
		memory[0x0000] = opcodes::inc_abs_x;
		memory[0x0001] = 0x00;
		memory[0x0002] = 0x0A;
		memory[0x0A01] = 123;
	});
}

TEST(instruction_inc, zp_addressing_works) {
	const auto result = run_one_instruction(zp_addressing_setup);
	
    EXPECT_EQ(124ui8, result.memory[0x00A0]);
}

TEST(instruction_inc, zp_addressing_decodes_to_string) {
	const auto result = decode_one_instruction(zp_addressing_setup);

	EXPECT_EQ("INC $A0", result);
}

TEST(instruction_inc, zp_and_x_addressing_works) {
	const auto result = run_one_instruction(zp_and_x_addressing_setup);
	
	EXPECT_EQ(124ui8, result.memory[0x00A1]);
}

TEST(instruction_inc, zp_and_x_addressing_decodes_to_string) {
	const auto result = decode_one_instruction(zp_and_x_addressing_setup);

	EXPECT_EQ("INC $A0, X", result);
}

TEST(instruction_inc, abs_addressing_works) {
	const auto result = run_one_instruction(abs_addressing_setup);
	
	EXPECT_EQ(124ui8, result.memory[0x0A00]);
}

TEST(instruction_inc, abs_addressing_decodes_to_string) {
	const auto result = decode_one_instruction(abs_addressing_setup);

	EXPECT_EQ("INC $0A00", result);
}

TEST(instruction_inc, abs_and_x_addressing_works) {
	const auto result = run_one_instruction(abs_and_x_addressing_setup);
	EXPECT_EQ(124ui8, result.memory[0x0A01]);
}

TEST(instruction_inc, abs_and_x_addressing_decodes_to_string) {
	const auto result = decode_one_instruction(abs_and_x_addressing_setup);

	EXPECT_EQ("INC $0A00, X", result);
}

TEST(instruction_inc, zero_flag_is_set_on_zero) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0xFF;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) == emu6510::status::zero);
}

TEST(instruction_inc, zero_flag_is_cleared_on_nonzero) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0x00;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::zero) != emu6510::status::zero);
}

TEST(instruction_inc, negative_flag_is_cleared_on_positive) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0xFF;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) != emu6510::status::negative);
}

TEST(instruction_inc, negative_flag_is_set_on_negative) {
	const auto result = run_one_instruction([](auto& /*cpu*/, auto& memory) {
		memory[0x0000] = opcodes::inc_zp;
		memory[0x0001] = 0xA0;
		memory[0x00A0] = 0x7F;
	});

	EXPECT_TRUE((result.cpu.status & emu6510::status::negative) == emu6510::status::negative);
}