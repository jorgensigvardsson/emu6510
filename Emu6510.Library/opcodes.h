#pragma once
#include <cstdint>

namespace emu6510 {
	namespace opcodes {
		constexpr uint8_t adc_immediate = 0x69;
		constexpr uint8_t adc_zp = 0x65;
		constexpr uint8_t adc_zp_x = 0x75;
		constexpr uint8_t adc_abs = 0x6D;
		constexpr uint8_t adc_abs_x = 0x7D;
		constexpr uint8_t adc_abs_y = 0x79;
		constexpr uint8_t adc_ind_x = 0x61;
		constexpr uint8_t adc_ind_y = 0x71;
		constexpr uint8_t beq = 0xF0;
		constexpr uint8_t inc_zp = 0xE6;
		constexpr uint8_t inc_zp_x = 0xF6;
		constexpr uint8_t inc_abs = 0xEE;
		constexpr uint8_t inc_abs_x = 0xFE;
		constexpr uint8_t lda_immediate = 0xA9;
		constexpr uint8_t lda_zp = 0xA5;
		constexpr uint8_t lda_zp_x = 0xB5;
		constexpr uint8_t lda_abs = 0xAD;
		constexpr uint8_t lda_abs_x = 0xBD;
		constexpr uint8_t lda_abs_y = 0xB9;
		constexpr uint8_t lda_ind_x = 0xA1;
		constexpr uint8_t lda_ind_y = 0xB1;
		constexpr uint8_t nop = 0xEA;		
	}
}
