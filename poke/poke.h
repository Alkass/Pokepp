#include <iostream>
#include <string>
#include <vector>
#include "../logger/logger.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

__attribute__((constructor)) void init_poke();
__attribute__((destructor)) void kill_poke();

typedef enum {
  UNKNOWN = 0,
  PASSED,
  FAILED
} TestCaseStatus;

class TestCase {
public:
  string title;
  string criteria;
  TestCaseStatus (*test)(Logger*);
  TestCase* on_success;
  TestCase* on_failure;
  TestCase(string, string, TestCaseStatus (*test)(Logger*), TestCase* = NULL, TestCase* = NULL);
  void setTitle(string);
  void setCriteria(string);
  void setTest(TestCaseStatus (*test)(Logger*));
  void setOnSuccess(TestCase*);
  void setOnFailure(TestCase*);
};

class TestCaseInterface {
private:
  vector<TestCase*>* test_cases;
public:
  TestCaseInterface();
  bool runTest(TestCase*);
  bool runTests(TestCase*);
  void registerNewTest(TestCase*);
  void startTests();
  ~TestCaseInterface();
};
