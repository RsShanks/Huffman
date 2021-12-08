#include "test_framework.h"

TestResult runTest(char *testName, int *(*testFunction)())
{
  char *errorMessage = testFunction();
  TestResult *testResult = malloc(sizeof(testResult));
  testResult->name = testName;
  if (errorMessage)
  {
    if (testResult)
    {
      testResult->success = 0;
      testResult->errorMessage = errorMessage;
    }
  }
  else
  {
    testResult->success = 1;
    testResult->errorMessage = NULL;
  }
}

int expectInt(const char *variableName, long long actual, long long expected)
{
  if (actual != expected)
  {
    printf("Expected %s = %d - Got %d", variableName, expected, actual);
    return 1;
  }
  return 0;
}

int expectFloat(const char *variableName, float actual, float expected)
{
  if (actual != expected)
  {
    printf("Expected %s = %f - Got %f", variableName, expected, actual);
    return 1;
  }
  return 0;
}

int expectChar(const char *variableName, char actual, char expected)
{
  if (actual != expected)
  {
    printf("Expected %s = %c - Got %c", variableName, expected, actual);
    return 1;
  }
  return 0;
}

int expectStr(const char *variableName, const char *actual, const char *expected)
{
  if (actual != expected)
  {
    printf("Expected %s = %s - Got %s", variableName, expected, actual);
    return 1;
  }
  return 0;
}

int expectPtr(const char *variableName, void *actual, void *expected)
{
  if (actual != expected)
  {
    printf("Expected %s = %d - Got %d", variableName, expected, actual);
    return 1;
  }
  return 0;
}

int expectPtrNotNull(const char *variableName, void *actual)
{
  if (!actual)
  {
    printf("Expected %s not NULL - Got NULL", variableName);
    return 1;
  }
  return 0;
}