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

#define OUCHI_CHECK_TRUE(expr) do{              \
try{                                            \
    if (!(expr)) {                              \
        error("assersion \"",                   \
              #expr, "\"failed. (",             \
              __FILE__,":",__LINE__,")"         \
              "\nreason : "                     \
              "evaluated to false.\n\n");       \
    }                                           \
} catch (std::exception& e) {                   \
    error("assertion \"", #expr, "\"failed. (", \
          __FILE__,":",__LINE__,")\n"           \
          "reason : exception thrown. ",        \
          e.what(), "\n\n");                    \
} catch(...){                                   \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : unknown exception thrown.", \
          "\n\n");                              \
}                                               \
} while(false)

#define OUCHI_CHECK_EQUAL(expr, expect) do{     \
try{                                            \
    if ((expr) != (expect)) {                   \
        error("assersion \"",                   \
              #expr, "\"failed. (",             \
              __FILE__,":",__LINE__,")"         \
              "\nreason : "                     \
              "the expression was evaluated to ",\
              (expr), "\n\tbut expected was ",  \
              (expect), ".\n\n");               \
    }                                           \
} catch (std::exception& e) {                   \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : exception thrown. ",        \
          e.what(), "\n\n");                    \
} catch(...){                                   \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : unknown exception thrown.", \
          "\n\n");                              \
}                                               \
} while(false)

#define OUCHI_CHECK_NOTHROW(expr) do{           \
try {                                           \
    (expr);                                     \
} catch (std::exception& e) {                   \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : exception was thrown. ",    \
          e.what(), "\n\n");                    \
} catch(...){                                   \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : unknown exception thrown.", \
          "\n\n");                              \
}                                               \
} while(false)

#define OUCHI_CHECK_THROW(expr, exception_type) \
do{                                             \
try {                                           \
    (expr);                                     \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : no exception thrown.\n\n"); \
} catch (exception_type){}                      \
catch(...) {                                    \
    error("assersion \"",                       \
          #expr, "\"failed. (",                 \
          __FILE__,":",__LINE__,")\n"           \
          "reason : unknown exception thrown.", \
          "\n\n");                              \
}                                               \
} while(false)

#define OUCHI_TEST_MAIN                         \
int main() {                                    \
    ouchi::test::test_base::test_all();         \
}
