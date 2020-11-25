/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef TEST_UCUNIT_PUB_TESTUTILS_H_
#define TEST_UCUNIT_PUB_TESTUTILS_H_

/* -- Include files --------------------------------------------------------- */
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/* PRQA S 1534 EOF # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_Init 3469 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_WriteSummary 3469,0752 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_Shutdown 3469 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_TestBegin 0752,3469 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_TestcaseBegin 0752,3469,0431,0311 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_TestcaseEnd 0752,3469 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_ChecklistBegin 3432 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_ChecklistEnd 2880,0752,2996,2992 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_CheckIsEqual 3469,0752,2992,2880,2996 # Existing unit test framework "ucunit" used. */
/* PRQA MS UCUNIT_CheckIsNull 0752 # Existing unit test framework "ucunit" used. */
#include <uCUnit-v1.0.h>
/* PRQA MS UCUNIT_ChecklistBeginWarning 3469,3432,3472 # Existing unit test framework "ucunit" used. */
/* PRQA S 3472 1 # Existing unit test framework "ucunit" used. */
#define UCUNIT_ChecklistBeginWarning() UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING)


/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define DEBUG_INT_BUFFER_SIZE 20

#define UCUNIT_RESULT ucunit_checks_failed

/* PRQA MS UCUNIT_CheckStrEquals 2995 # operation is always 'true': happens when a const str is passed as an argument. */
/* PRQA MS UCUNIT_CheckStrEquals 3415 # right hand side side effect: deliberate shortcut expression. */
/* PRQA MS UCUNIT_CheckStrEquals 0752 # not ptr to const: depends on stdlib. */
#define UCUNIT_CheckStrEquals(expected, actual)                                                                             \
  UCUNIT_Check((((actual) != NULL) && (0 == strcmp((expected), (actual)))), "IsStrEqual",                                   \
               UCUNIT_ArgsToString(expected, actual))

#define UCUNIT_DebugInt(message, intvalue)                                                                                  \
  do                                                                                                                        \
  {                                                                                                                         \
    char buf[DEBUG_INT_BUFFER_SIZE];                                                                                        \
    sprintf_s(buf, sizeof(buf), "%d", intvalue);                                                                            \
    UCUNIT_PassCheck(message, buf);                                                                                         \
  } while (0)

/** Start a numbered test case
 *
 * In case a single test case function contains multiple executions, e.g. because it
 * is parameterized, use this function instead of UCUNIT_TestcaseBegin to append an
 * index to the test case name in order to distinguish specific executions.
 *
 * Implementation Note: Is a macro because it indirectly manipulates static variables.
 *
 * \param[in] the name of the test case
 * \param[in] number the number to be appended to the name
 * \return void
 */
#define UCUNIT_TestcaseBeginNumbered(name, number)                                                                          \
  do                                                                                                                        \
  {                                                                                                                         \
    char buf[128];                                                                                                          \
    sprintf(buf, "%s_%" PRId32, name, (int32_t)(number));                                                                   \
    UCUNIT_TestcaseBegin(buf);                                                                                              \
  } while (0)

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

#endif /* TEST_UCUNIT_PUB_TESTUTILS_H_ */
