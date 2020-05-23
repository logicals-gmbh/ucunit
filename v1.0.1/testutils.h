/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef TEST_UCUNIT_PUB_TESTUTILS_H_
#define TEST_UCUNIT_PUB_TESTUTILS_H_

/* -- Include files --------------------------------------------------------- */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <uCUnit-v1.0.h>


/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define DEBUG_INT_BUFFER_SIZE 20

#define UCUNIT_RESULT (ucunit_checks_failed > 0)

#define UCUNIT_CheckStrEquals(expected, actual)                                                    \
  UCUNIT_Check(((actual != NULL) && (0 == strcmp(expected, actual))), "IsStrEqual",                \
               UCUNIT_ArgsToString(expected, actual))

#define UCUNIT_DebugInt(message, intvalue)                                                         \
  do                                                                                               \
  {                                                                                                \
    char buf[DEBUG_INT_BUFFER_SIZE];                                                               \
    sprintf_s(buf, sizeof(buf), "%d", intvalue);                                                   \
    UCUNIT_PassCheck(message, buf);                                                                \
  } while (0)

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** Start a numbered test case
 *
 * In case a single test case function contains multiple executions, e.g. because it
 * is parameterized, use this function instead of UCUNIT_TestcaseBegin to append an
 * index to the test case name in order to distinguish specific executions.
 *
 * @param[in] the name of the test case
 * @param[in] number the number to be appended to the name
 * @return void
 */
void UCUNIT_TestcaseBeginNumbered(char* name, int32_t number);

#endif /* TEST_UCUNIT_PUB_TESTUTILS_H_ */
