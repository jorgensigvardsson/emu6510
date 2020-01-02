#pragma once
#include "instruction.h"
#include "cpu.h"
#include "bits.h"

namespace emu6510 {
	// INC
	template <typename T, int cycle_count>
	struct inc : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			auto result = ++memory[static_cast<const T*>(this)->ptr(cpu, memory)];
			cpu.cycle_counter += cycle_count;
			if (result & byte_sign_bit)
				cpu.status |= status::negative;
			else
				cpu.status &= ~status::negative;

			if (result == 0)
				cpu.status |= status::zero;
			else
				cpu.status &= ~status::zero;
		}
	};

	struct inc_zp : inc<inc_zp, 5> { uint16_t ptr(cpu& cpu, const memory& memory) const { return read_ip_byte(cpu, memory); } };
	struct inc_zp_x : inc<inc_zp_x, 6> { uint16_t ptr(cpu& cpu, const memory& memory) const { return read_ip_byte(cpu, memory) + cpu.x; } };
	struct inc_abs : inc<inc_abs, 6> { uint16_t ptr(cpu& cpu, const memory& memory) const { return read_ip_word(cpu, memory); } };
	struct inc_abs_x : inc<inc_abs_x, 7> { uint16_t ptr(cpu& cpu, const memory& memory) const { return read_ip_word(cpu, memory) + cpu.x; } };
}
