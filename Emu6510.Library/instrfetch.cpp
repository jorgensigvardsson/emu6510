#include "pch.h"
#include "instrfetch.h"
#include "memory.h"
#include "instructions.h"
#include "cpu.h"
#include "opcodes.h"
#include "invalid_op.h"

namespace {
	using namespace emu6510;

#define OP_IMMEDIATE(name) name##_immediate name##_immediate_instance
#define OP_ZP(name) name##_zp name##_zp_instance
#define OP_ZP_X(name) name##_zp_x name##_zp_x_instance
#define OP_ABS(name) name##_abs name##_abs_instance
#define OP_ABS_X(name) name##_abs_x name##_abs_x_instance
#define OP_ABS_Y(name) name##_abs_y name##_abs_y_instance
#define OP_IND_X(name) name##_ind_x name##_ind_x_instance
#define OP_IND_Y(name) name##_ind_y name##_ind_y_instance


	OP_IMMEDIATE(adc);
	OP_ZP(adc);
	OP_ZP_X(adc);
	OP_ABS(adc);
	OP_ABS_X(adc);
	OP_ABS_Y(adc);
	OP_IND_X(adc);
	OP_IND_Y(adc);
	beq beq_instance;
	OP_ABS(inc);
	OP_ABS_X(inc);
	OP_ZP(inc);
	OP_ZP_X(inc);
	nop nop_instance;
	OP_IMMEDIATE(lda);
	OP_ZP(lda);
	OP_ZP_X(lda);
	OP_ABS(lda);
	OP_ABS_X(lda);
	OP_ABS_Y(lda);
	OP_IND_X(lda);
	OP_IND_Y(lda);
	invalid_op invalid_op_instance;
}

namespace emu6510 {
	instruction& fetch(cpu& cpu, memory& memory, uint16_t* addr_start, uint16_t* addr_len) noexcept {
		const auto start = cpu.pc;
		auto& instruction = fetch(cpu, memory);

		if (addr_start)
			*addr_start = start;

		if (addr_len)
			*addr_len = cpu.pc - start;

		return instruction;
	}
	
#define CASE_OP_CODE(opcode) case opcodes::opcode: \
	return opcode##_instance
		
	instruction& fetch(cpu& cpu, memory& memory) noexcept {
		const auto opcode = read_ip_byte(cpu, memory);
		switch (opcode) {
			CASE_OP_CODE(adc_immediate);
			CASE_OP_CODE(adc_zp);
			CASE_OP_CODE(adc_zp_x);
			CASE_OP_CODE(adc_abs_x);
			CASE_OP_CODE(adc_abs_y);
			CASE_OP_CODE(adc_abs);
			CASE_OP_CODE(adc_ind_x);
			CASE_OP_CODE(adc_ind_y);
			CASE_OP_CODE(beq);
			CASE_OP_CODE(inc_abs);
			CASE_OP_CODE(inc_abs_x);
			CASE_OP_CODE(inc_zp);
			CASE_OP_CODE(inc_zp_x);
			CASE_OP_CODE(nop);
			CASE_OP_CODE(lda_immediate);
			CASE_OP_CODE(lda_zp);
			CASE_OP_CODE(lda_zp_x);
			CASE_OP_CODE(lda_abs_x);
			CASE_OP_CODE(lda_abs_y);
			CASE_OP_CODE(lda_abs);
			CASE_OP_CODE(lda_ind_x);
			CASE_OP_CODE(lda_ind_y);
		default:
			return invalid_op_instance;
		}
	}

	bool is_valid(const instruction& instruction) noexcept {
		if (&instruction == &invalid_op_instance)
			return false;
		
		return dynamic_cast<const invalid_op*>(&instruction) == nullptr;
	}

}
