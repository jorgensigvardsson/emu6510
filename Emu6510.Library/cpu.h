#pragma once

#include <cstdint>
#include "memory.h"

namespace emu6510 {
	namespace status {
		constexpr uint8_t carry = 1 << 0;
		constexpr uint8_t zero = 1 << 1;
		constexpr uint8_t irq_disable = 1 << 2;
		constexpr uint8_t decimal_mode = 1 << 3;
		constexpr uint8_t brk_command = 1 << 4;
		constexpr uint8_t overflow = 1 << 6;
		constexpr uint8_t negative = 1 << 7;
	}
	
	struct cpu {
		uint8_t sp = 0;
		uint16_t pc = 0;
		uint8_t a = 0;
		uint8_t x = 0;
		uint8_t y = 0;
		uint8_t status = 0;
		int cycle_counter = 0;
	};

	inline uint8_t read_ip_byte(cpu& cpu, const memory& memory) {
		return memory[cpu.pc++];
	}

	inline uint16_t read_ip_word(cpu& cpu, const memory& memory) {
		const auto location = cpu.pc;
		cpu.pc += 2;
		return memory.read_word(location);
	}

	inline void set_status_bit_value(cpu& cpu, uint8_t bit, bool value) {
		cpu.status = value
			? cpu.status | bit
			: cpu.status & ~bit;
	}
}
