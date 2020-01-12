#pragma once
#include <ostream>
#include <iomanip>

namespace emu6510::internal {
	inline void hex_number(std::ostream& os, int8_t byte) noexcept {
		os << (byte < 0 ? "-" : "") << "$" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(byte < 0 ? -byte : byte);
	}
	
	inline void hex_number(std::ostream& os, uint8_t byte) noexcept {
		os << "$" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
	}
	
	inline void hex_number(std::ostream& os, uint16_t word) noexcept {
		os << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << static_cast<int>(word);
	}

	inline void imm(std::ostream& os, uint8_t byte) noexcept {
		os << "#";
		hex_number(os, byte);
	}

	inline void zp_addr(std::ostream& os, uint8_t byte) noexcept {
		hex_number(os, byte);
	}
	
	inline void zp_addr_x(std::ostream& os, uint8_t byte) noexcept {
		hex_number(os, byte);
		os << ", X";
	}

	inline void abs_addr(std::ostream& os, uint16_t word) noexcept {
		hex_number(os, word);
	}

	inline void abs_addr_indexed(std::ostream& os, uint16_t word, char index) noexcept {
		hex_number(os, word);
		os << ", " << index;
	}
	
	inline void abs_addr_x(std::ostream& os, uint16_t word) noexcept {
		abs_addr_indexed(os, word, 'X');
	}

	inline void abs_addr_y(std::ostream& os, uint16_t word) noexcept {
		abs_addr_indexed(os, word, 'Y');
	}

	inline void ind_addr_x(std::ostream& os, uint8_t byte) noexcept {
		os << "(";
		hex_number(os, byte);
		os << ", X)";
	}
	
	inline void ind_addr_y(std::ostream& os, uint8_t byte) noexcept {
		os << "(";
		hex_number(os, byte);
		os << "), Y";
	}
}
