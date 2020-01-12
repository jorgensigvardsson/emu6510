#pragma once
#include <utility>
#include "instruction.h"
#include "cpu.h"
#include "bits.h"
#include "decode_internal.h"
#include <sstream>

namespace emu6510 {
	// ADC
	constexpr const char* adc_mnemonic = "ADC";
	
	template <typename T>
	struct adc : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			const auto operand = static_cast<const T*>(this)->read_operand(cpu, memory);
			const auto result = cpu.a + operand.first + (cpu.status & status::carry ? 1 : 0);
			const auto next_zero = (result & UINT8_MAX) == 0;
			const auto next_carry = result > UINT8_MAX;
			const auto next_overflow = cpu.a <= INT8_MAX && result > INT8_MAX;
			const auto next_negative = (result & byte_sign_bit) != 0;

			set_status_bit_value(cpu, status::carry, next_carry);
			set_status_bit_value(cpu, status::overflow, next_overflow);
			set_status_bit_value(cpu, status::negative, next_negative);
			set_status_bit_value(cpu, status::zero, next_zero);

			cpu.cycle_counter += operand.second;
			cpu.a = static_cast<uint8_t>(result);
		}

		std::string decode(cpu& cpu, const memory& memory) const noexcept override {
			std::stringstream ss;
			ss << adc_mnemonic << " ";
			static_cast<const T*>(this)->decode_args(ss, cpu, memory);
			return ss.str();
		}
	};

	struct adc_immediate : adc<adc_immediate> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			return std::make_pair(first_arg(cpu, memory), 2);
		}

		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::imm(os, first_arg(cpu, memory));
		}
	};

	struct adc_zp : adc<adc_zp> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = first_arg(cpu, memory);
			return std::make_pair(memory[ptr], 3);
		}

		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::zp_addr(os, first_arg(cpu, memory));
		}
	};

	struct adc_zp_x : adc<adc_zp_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = first_arg(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4);
		}
		
		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::zp_addr_x(os, first_arg(cpu, memory));
		}
	};

	struct adc_abs : adc<adc_abs> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = first_arg(cpu, memory);
			return std::make_pair(memory[ptr], 4);
		}

		uint16_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_word(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::abs_addr(os, first_arg(cpu, memory));
		}
	};

	struct adc_abs_x : adc<adc_abs_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = first_arg(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}

		uint16_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_word(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::abs_addr_x(os, first_arg(cpu, memory));
		}
	};

	struct adc_abs_y : adc<adc_abs_y> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto ptr = first_arg(cpu, memory);
			return std::make_pair(memory[ptr + cpu.y], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}

		uint16_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_word(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::abs_addr_y(os, first_arg(cpu, memory));
		}
	};

	struct adc_ind_x : adc<adc_ind_x> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = static_cast<uint16_t>(first_arg(cpu, memory) + cpu.x);
			const auto effective_ptr = memory.read_word(zp_ptr);
			return std::make_pair(memory[effective_ptr], 6);
		}
		
		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::ind_addr_x(os, first_arg(cpu, memory));
		}
	};

	struct adc_ind_y : adc<adc_ind_y> {
		std::pair<uint8_t, int> read_operand(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = first_arg(cpu, memory);
			const auto effective_ptr = memory.read_word(zp_ptr) + cpu.y;
			return std::make_pair(memory[effective_ptr], 5);
		}
		
		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::ind_addr_y(os, first_arg(cpu, memory));
		}
	};
}
