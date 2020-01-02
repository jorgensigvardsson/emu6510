#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <sstream>
#include <vector>
#include "tests.h"

struct test_root root;

test_group::test_group(const char* name, std::vector<test> tests)
	: name { name }
	, tests { std::move(tests) }
	, next { root.head } {
	root.head = this;
}

int main(int argc, char** argv) {
	auto test_group = root.head;
	while(test_group) {
		std::cout << test_group->name << "\n";
		for(auto& test : test_group->tests) {
			std::cout << "\t" << test.name << ": ";
			try {
				test.run();
				std::cout << "SUCCESS";
			} catch(const assertion_exception& ex) {
				std::cout << "FAIL, " << ex.message;
			} catch(...) {
				std::cout << "FAIL";
			}
			std::cout << std::endl;
		}
		test_group = test_group->next;
	}
	return 0;
}

#define TEST_CONTEXT
#include "../Emu6510.Library/memory.h"
#include "../Emu6510.Library/cpu.h"
#include "../Emu6510.Library/instrfetch.h"
#include "../Emu6510.Library/opcodes.h"
#include "../Emu6510.Library/instructions.h"