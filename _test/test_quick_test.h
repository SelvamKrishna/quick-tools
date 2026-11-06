#ifndef TEST_QUICK_TEST_H
#define TEST_QUICK_TEST_H

#include "utility/quick_test.h"

qtest_case(test_addition)
{
    qtest_c(1 + 1 == 2);
    qtest_c(0 + 0 == 0);
    qtest_c(-1 + 1 == 0);
    qtest_c(-5 + -5 == -10);
    qtest_c(100 + 200 == 300);
    qtest_c(2147483640 + 7 == 2147483647);
    qtest_c(2 + 1 == 2); // FAILS
}

qtest_case(test_subtraction)
{
    qtest_c(5 - 3 == 2);
    qtest_c(0 - 5 == -5);
    qtest_c(-5 - -5 == 0);
    qtest_c(100 - 50 == 50);
    qtest_c(50 - 100 == -50);
    qtest_c(2147483647 - 1 == 2147483646);
    qtest_c(10 - 5 == 6); // FAILS
}

qtest_case(test_multiplication)
{
    qtest_c(2 * 3 == 6);
    qtest_c(0 * 100 == 0);
    qtest_c(-2 * 3 == -6);
    qtest_c(-2 * -3 == 6);
    qtest_c(1 * 999 == 999);
    qtest_c(46340 * 46340 >= 0);
}

qtest_case(test_division)
{
    qtest_c(6 / 3 == 2);
    qtest_c(5 / 2 == 2);
    qtest_c(-6 / 3 == -2);
    qtest_c(7 / -2 == -3);
    qtest_c(0 / 5 == 0);
    qtest_c(10 / 3 == 3);
    qtest_c(8 / 4 == 3);  // FAILS
    qtest_c(9 / 4 == 3);  // FAILS
    qtest_c(10 / 4 == 3); // FAILS
}

void quick_test_showcase()
{
    qtest_all("quick_test: showcase");
}

#endif // TEST_QUICK_TEST_H
