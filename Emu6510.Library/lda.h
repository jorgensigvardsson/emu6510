#pragma once
#include <utility>
#include "instruction.h"
#include "cpu.h"
#include "bits.h"
#include "decode_internal.h"
#include <sstream>

namespace emu6510 {
	// LDA
	constexpr const char* lda_mnemonic = "LDA";

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

		std::string decode(cpu& cpu, const memory& memory) const noexcept override {
			std::stringstream ss;
			ss << lda_mnemonic << " ";
			static_cast<const T*>(this)->decode_args(ss, cpu, memory);
			return ss.str();
		}
	};

	struct lda_immediate : lda<lda_immediate> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
			return std::make_pair(first_arg(cpu, memory), 2);
		}

		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::imm(os, first_arg(cpu, memory));
		}
	};

	struct lda_zp : lda<lda_zp> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_zp_x : lda<lda_zp_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_abs : lda<lda_abs> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_abs_x : lda<lda_abs_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_abs_y : lda<lda_abs_y> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_ind_x : lda<lda_ind_x> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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

	struct lda_ind_y : lda<lda_ind_y> {
		std::pair<uint8_t, int> read_value(cpu& cpu, const memory& memory) const {
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
