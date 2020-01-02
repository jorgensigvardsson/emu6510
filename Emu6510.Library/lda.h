#pragma once
#include <utility>
#include "instruction.h"
#include "cpu.h"
#include "bits.h"

namespace emu6510 {
	// LDA
	template <typename T>
	struct lda : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			const auto operand = static_cast<const T*>(this)->read_value(cpu, memory);
			const auto result = operand.first;
			const auto next_zero = result == 0;
			const auto next_negative = (result & byte_sign_bit) != 0;

			set_status_bit_value(cpu, status::zero, next_zero);
			set_status_bit_value(cpu, status::negative, next_negative);

			cpu.cycle_counter += operand.second;
			cpu.a = result;
		}
	};

	struct lda_immediate : lda<lda_immediate> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			return std::make_pair(read_ip_byte(cpu, memory), 2);
		}
	};

	struct lda_zp : lda<lda_zp> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_byte(cpu, memory);
			return std::make_pair(memory[ptr], 3);
		}
	};

	struct lda_zp_x : lda<lda_zp_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_byte(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4);
		}
	};

	struct lda_abs : lda<lda_abs> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr], 4);
		}
	};

	struct lda_abs_x : lda<lda_abs_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr + cpu.x], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}
	};

	struct lda_abs_y : lda<lda_abs_y> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto ptr = read_ip_word(cpu, memory);
			return std::make_pair(memory[ptr + cpu.y], 4 + (ptr & UINT8_MAX) == UINT8_MAX ? 1 : 0);
		}
	};

	struct lda_ind_x : lda<lda_ind_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = read_ip_byte(cpu, memory) + cpu.x;
			const auto effective_ptr = memory.read_word(zp_ptr);
			return std::make_pair(memory[effective_ptr], 6);
		}
	};

	struct lda_ind_y : lda<lda_ind_y> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			const auto zp_ptr = read_ip_byte(cpu, memory);
			const auto effective_ptr = memory.read_word(zp_ptr) + cpu.y;
			return std::make_pair(memory[effective_ptr], 5);
		}
	};

}
