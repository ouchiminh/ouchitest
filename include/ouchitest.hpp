#pragma once
#include <exception>
#include "test_base.hpp"

#define OUCHI_TEST_CASE(test_name)              \
class test_name                                 \
    : public ouchi::test::test_base {           \
public:                                         \
    test_name()                                 \
        : test_base(#test_name)                 \
    {                                           \
        test_cases.push_back(this);             \
    }                                           \
    void test() override final;                 \
private:                                        \
} test_name##_instance;                         \
void test_name::test()

#define FAIL_LOG(expr, ...) do                  \
{                                               \
error("\nassertion \"", #expr, "\" failed.");   \
log("(", __FILE__,":",__LINE__,")\n");          \
log("reason : ", __VA_ARGS__, "\n\n");          \
} while(false);

#define UNKNOWN_EXCEPTION(expr)                 \
catch(...){                                     \
    FAIL_LOG(expr,                              \
             "an unknown exception was thrown");\
}

#define STD_EXCEPTION(expr)                     \
catch(std::exception& e){                       \
    FAIL_LOG(expr, "an exception thrown. ",     \
             e.what());                         \
}

#define OUCHI_CHECK_TRUE(expr) do{              \
try{                                            \
    if (!(expr)) {                              \
        FAIL_LOG(expr, "\""                     \
                 #expr "\" evaluated to false");\
    }                                           \
}                                               \
STD_EXCEPTION(expr)                             \
UNKNOWN_EXCEPTION(expr)                         \
} while(false)

#define OUCHI_REQUIRE_TRUE(expr) do{            \
if (!(expr)) {                                  \
    FAIL_LOG(expr, "\""                         \
             #expr "\" evaluated to false");    \
    return;                                     \
}                                               \
} while(false)

#define OUCHI_CHECK_EQUAL(expr, expect) do{     \
try{                                            \
    auto result = (expr);                       \
    auto ex = (expect);                         \
    if ((result) != (ex)) {                     \
        FAIL_LOG(expr, "\n\texpected value is ", ex,   \
                 "\n\tactual value is   ", (result))   \
    }                                           \
}                                               \
STD_EXCEPTION(expr)                             \
UNKNOWN_EXCEPTION(expr)                         \
} while(false)

#define OUCHI_REQUIRE_EQUAL(expr, expect) do{   \
auto result = (expr);                           \
auto ex = (expect);                             \
if ((result) != (ex)) {                         \
    FAIL_LOG(expr, "\n\texpected value is ", ex,\
             "\n\tactual value is   ", (result))\
    return;                                     \
}                                               \
} while(false)

#define OUCHI_CHECK_NOTHROW(expr) do{           \
try {                                           \
    (expr);                                     \
}                                               \
STD_EXCEPTION(expr)                             \
UNKNOWN_EXCEPTION(expr)                         \
} while(false)

#define OUCHI_CHECK_THROW(expr, exception_type) \
do{                                             \
try {                                           \
    (expr);                                     \
    FAIL_LOG(expr, #exception_type,             \
    " was expected. but no exception was thrown.");\
} catch (exception_type){}                      \
UNKNOWN_EXCEPTION(expr)                         \
} while(false)

#define OUCHI_TEST_MAIN                         \
int main() {                                    \
    ouchi::test::test_base::test_all();         \
}
