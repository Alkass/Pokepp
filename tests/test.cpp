#include "../poke/poke.h"

TestCaseStatus testCase(Logger* l) {
  return PASSED; // other valid values are FAILUED and UNKNOWN
}

int main() {
  TestCaseInterface tci;

  TestCase* on_success = new TestCase(
    "on_success Test Case",
    "No Criteria",
    [](Logger* logger) -> TestCaseStatus {
      return PASSED;
    }
  );

  TestCase* on_failure = new TestCase(
    "on_failure Test Case",
    "No Criteria",
    [](Logger* logger) -> TestCaseStatus {
      return PASSED;
    }
  );

  tci.registerNewTest(new TestCase("Test Case 1", "Test Case Criteria", testCase, on_success, on_failure));

  tci.startTests();
}
