#pragma once
#include <utility>
#include "instruction.h"
#include "cpu.h"

namespace emu6510 {
	// ADC
	template <typename T>
	struct adc : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			const auto operand = static_cast<const T*>(this)->read_operand(cpu, memory);
			const auto result = cpu.a + operand.first + (cpu.status & status::carry ? 1 : 0);
			const auto next_zero = result == 0;

			if (next_zero) {
				set_status_bit_value(cpu, status::zero, true);
				set_status_bit_value(cpu, status::carry, false);
				set_status_bit_value(cpu, status::overflow, false);
				set_status_bit_value(cpu, status::negative, false);
			} else {
				const auto next_carry = result > UINT8_MAX;
				const auto next_overflow = cpu.a <= INT8_MAX && result > INT8_MAX;
				const auto next_negative = (result & byte_sign_bit) != 0;

				set_status_bit_value(cpu, status::carry, next_carry);
				set_status_bit_value(cpu, status::overflow, next_overflow);
				set_status_bit_value(cpu, status::negative, next_negative);
				set_status_bit_value(cpu, status::zero, false);
			}

			cpu.cycle_counter += operand.second;
			cpu.a = result;
		}
	};

	struct adc_immediate : adc<adc_immediate> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			return std::make_pair(read_ip_byte(cpu, memory), 2);
		}
	};

	struct adc_zp : adc<adc_zp> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_byte(cpu, memory);
			return std::make_pair(memory[ptr], 3);
		}
	};

	struct adc_zp_x : adc<adc_zp_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_byte(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4);
		}
	};

	struct adc_abs : adc<adc_abs> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr], 4);
		}
	};

	struct adc_abs_x : adc<adc_abs_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}
	};

	struct adc_abs_y : adc<adc_abs_y> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr + cpu.y], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}
	};

	struct adc_ind_x : adc<adc_ind_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = read_ip_byte(cpu, memory) + cpu.x;
			const auto effective_ptr = memory.read_word(zp_ptr);
			return std::make_pair(memory[effective_ptr], 6);
		}
	};

	struct adc_ind_y : adc<adc_ind_y> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = read_ip_byte(cpu, memory);
			const auto effective_ptr = memory.read_word(zp_ptr) + cpu.y;
			return std::make_pair(memory[effective_ptr], 5);
		}
	};
}
