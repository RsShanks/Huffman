#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

typedef struct TestResult_
{
  char *name;
  char success;
  char *errorMessage;
} TestResult;

TestResult runTest(char *testName, int *(*testFunction)());

int expectInt(const char *variableName, long long actual, long long expected);
int expectFloat(const char *variableName, float actual, float expected);
int expectChar(const char *variableName, char actual, char expected);
int expectStr(const char *variableName, const char *actual, const char *expected);
int expectPtr(const char *variableName, void *actual, void *expected);
int expectPtrNotNull(const char *variableName, void *actual);
#endif