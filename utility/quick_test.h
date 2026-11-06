#ifndef QUICK_TEST_H
#define QUICK_TEST_H

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

// --- internal decl ---

typedef struct q_test_s {
    const char* NAME;
    void (*func)(void);
    struct q_test_s* link;
} q_test_t;

void q_test_case_add(q_test_t*);
void q_test_all(const char* const);
void q_test_pass(void);
void q_test_fail(const char* const, const char*, size_t);

// --- public API --

#define qtest_case(title) \
    static void title(void); \
    static q_test_t _q_test_##title = {#title, title, NULL}; \
    static void __attribute__((constructor)) _q_test_reg_##title(void) \
    { \
        q_test_case_add(&_q_test_##title); \
    } \
    static void title(void) \

#define qtest_all(suite_str) \
    do { q_test_all(suite_str); } while (0)

#define qtest_c(cnd) \
    do { (cnd) ? q_test_pass() : q_test_fail(#cnd, __FILE__, __LINE__); } while (0)

// --- logic impl ---

#ifdef QUICK_TEST_IMPL

#include "utility/quick_ansi.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    q_test_t* head;
    bool brk_flag;
    size_t failed;
    size_t passed;
} q_test_reg_t;

static q_test_reg_t s_qt_reg = {NULL, false, 0, 0};

void q_test_case_add(q_test_t* test)
{
    test->link = s_qt_reg.head;
    s_qt_reg.head = test;
}

void q_test_all(const char* const suite_str)
{
    printf(
        qansi_wrap(34, "TESTING {")
        "%s"
        qansi_wrap(34, "} :")
        , suite_str ? suite_str : "ALL"
    );

    size_t prev_fails = s_qt_reg.failed;

    for (
        q_test_t* it = s_qt_reg.head;
        it && !s_qt_reg.brk_flag;
        it = it->link
    ) {
        printf("\n    "qansi_wrap(33, "%s")" : ", it->NAME);
        fflush(stdout);
        it->func();

        if (prev_fails != s_qt_reg.failed)
        {
            prev_fails = s_qt_reg.failed;
            continue;
        }

        printf(qansi_wrap(32, "OK"));
    }

    printf("\n\n");
    printf("%s = %zu\n", qansi_wrap(32, "SUCCESS"), s_qt_reg.passed);
    printf("%s = %zu\n", qansi_wrap(31, "FAILURE"), s_qt_reg.failed);
}

void q_test_pass(void) { s_qt_reg.passed ++; }

void q_test_fail(const char* const desc, const char* file, size_t line)
{
    s_qt_reg.failed ++;
    printf("\n        "qansi_wrap(31, "FAIL")" : ");
    printf(qansi_wrap(2, "[%s:%zu]")" %s", file, line, desc);
}

#endif // QUICK_TEST_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_TEST_H
