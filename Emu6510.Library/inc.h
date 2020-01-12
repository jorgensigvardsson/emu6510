#pragma once
#include "instruction.h"
#include "cpu.h"
#include "bits.h"
#include "decode_internal.h"
#include <sstream>

namespace emu6510 {
	// INC
	constexpr const char* inc_mnemonic = "INC";

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

		std::string decode(cpu& cpu, const memory& memory) const noexcept override {
			std::stringstream ss;
			ss << inc_mnemonic << " ";
			static_cast<const T*>(this)->decode_args(ss, cpu, memory);
			return ss.str();
		}
	};

	struct inc_zp : inc<inc_zp, 5> {
		uint16_t ptr(cpu& cpu, const memory& memory) const { return first_arg(cpu, memory); }

		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::zp_addr(os, first_arg(cpu, memory));
		}
	};
	
	struct inc_zp_x : inc<inc_zp_x, 6> {
		uint16_t ptr(cpu& cpu, const memory& memory) const { return first_arg(cpu, memory) + cpu.x; }
		
		uint8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_byte(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::zp_addr_x(os, first_arg(cpu, memory));
		}
	};
	
	struct inc_abs : inc<inc_abs, 6> {
		uint16_t ptr(cpu& cpu, const memory& memory) const { return first_arg(cpu, memory); }

		uint16_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_word(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::abs_addr(os, first_arg(cpu, memory));
		}
	};
	
	struct inc_abs_x : inc<inc_abs_x, 7> {
		uint16_t ptr(cpu& cpu, const memory& memory) const { return first_arg(cpu, memory) + cpu.x; }
		
		uint16_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return read_ip_word(cpu, memory);
		}

		void decode_args(std::ostream& os, cpu& cpu, const memory& memory) const noexcept {
			internal::abs_addr_x(os, first_arg(cpu, memory));
		}
	};
}
