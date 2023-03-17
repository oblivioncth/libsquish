#include <iostream>

// Test debug helpers
namespace LSTest
{
    template<typename T>
    inline std::string toString(T t) { return "[NO_TO_STRING_OVERLOAD FOR TYPE]"; }

    template<typename X, typename Y>
    inline bool compare(const X& x, const Y& y, const char* actual, const char* expected,
                        const char* file, int line)
    {
        bool success = (x == y);
        if(!success)
        {
            std::cout << "FAIL! : Actual value '" << actual
                      << "' is not equal to expected value '" << expected << "'" << std::endl;
            std::cout << "Actual:\n" << toString(x) << std::endl << std::endl;
            std::cout << "Expected:\n" << toString(y) << std::endl << std::endl;
            std::cout << "Failure Location: " << file << '(' << line << ')' << std::endl;
        }
        return success;
    }

    inline bool verify(bool res, const char* statement, const char* file, int line)
    {
        if(!res)
        {
            std::cout << "FAIL! : Statement evaluated to false: " << statement;
            std::cout << "Failure Location: " << file << '(' << line << ')' << std::endl;
        }
        return res;
    }
}

#define __LS_FAIL_CHECK(func_call) \
do { \
    if (!func_call) \
    { \
        std::cerr << "TEST FAILED!" << std::endl; \
        return -1; \
    } \
} while (false)

#define LS_COMPARE(actual, expected) \
__LS_FAIL_CHECK(LSTest::compare(actual, expected, #actual, #expected, __FILE__, __LINE__))

#define LS_VERIFY(statement) \
__LS_FAIL_CHECK(LSTest::verify(static_cast<bool>(statement), #statement, __FILE__, __LINE__))

#define LS_START(test) \
std::cout << "START: " << test << std::endl;

#define LS_END() \
std::cout << "PASS!" << std::endl; \
return 0;
