// mini_test.hpp - a tiny test helper, so you need nothing but a C++17 compiler.
//
//   TEST_CASE(name_that_describes_the_behavior) { ... }
//   CHECK(condition);            // passes when condition is true
//   CHECK_EQ(actual, expected);  // passes when actual == expected
//
// You do not need to change this file.
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mini_test {

struct TestCase {
    const char* name;
    void (*body)();
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

inline int& failedChecks() {
    static int count = 0;
    return count;
}

struct Registrar {
    Registrar(const char* name, void (*body)()) { registry().push_back({name, body}); }
};

inline void reportFailure(const char* file, int line, const std::string& expression,
                          const std::string& detail) {
    ++failedChecks();
    std::cout << "    CHECK FAILED at " << file << ":" << line << "\n"
              << "      " << expression << "\n";
    if (!detail.empty()) {
        std::cout << "      " << detail << "\n";
    }
}

inline int runAll() {
    int passed = 0;
    int failed = 0;
    for (const TestCase& test : registry()) {
        const int before = failedChecks();
        test.body();
        if (failedChecks() == before) {
            ++passed;
            std::cout << "[PASS] " << test.name << "\n";
        } else {
            ++failed;
            std::cout << "[FAIL] " << test.name << "\n";
        }
    }
    std::cout << "\n" << registry().size() << " tests, " << passed << " passed, " << failed
              << " failed\n";
    return failed == 0 ? 0 : 1;
}

}  // namespace mini_test

#define TEST_CASE(name)                                                   \
    static void name();                                                   \
    static const mini_test::Registrar name##_registrar(#name, &name);     \
    static void name()

#define CHECK(condition)                                                  \
    do {                                                                  \
        if (!(condition)) {                                               \
            mini_test::reportFailure(__FILE__, __LINE__, #condition, ""); \
        }                                                                 \
    } while (0)

#define CHECK_EQ(actual, expected)                                                         \
    do {                                                                                   \
        const auto& actual_value_ = (actual);                                              \
        const auto& expected_value_ = (expected);                                          \
        if (!(actual_value_ == expected_value_)) {                                         \
            std::ostringstream detail_;                                                    \
            detail_ << "expected: " << expected_value_ << "   actual: " << actual_value_;  \
            mini_test::reportFailure(__FILE__, __LINE__, #actual " == " #expected,         \
                                     detail_.str());                                       \
        }                                                                                  \
    } while (0)
