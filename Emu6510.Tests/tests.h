#pragma once

struct test {
	const char* name;
	std::function<void()> run;
};

struct test_group {
	const char* const name;
	std::vector<test> tests;

	explicit test_group(const char* name, std::vector<test> tests);

	test_group* next;
};

struct assertion_exception {
	const std::string message;
	assertion_exception(std::string message) : message { std::move(message) } {}
};

struct test_root {
	struct test_group* head;

	test_root() : head { nullptr } {}
};

template <typename T>
std::string str(T value) {
	static_assert(false, "Please specialize this function");
}

template <>
std::string str<uint8_t>(uint8_t value) {
	return std::to_string(value);
}

template <typename T>
void assert_eq(T expected, T actual) {
	if (expected != actual) {
		std::stringstream ss;
		ss << "expected the value " << str(expected) << " but got " << str(actual);
		throw assertion_exception(ss.str());
	}
}
