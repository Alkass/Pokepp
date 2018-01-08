#include "poke.h"

__attribute__((constructor)) void init_poke() {
  printf("--- Starting Tests ---\n\n");
}

__attribute__((destructor)) void kill_poke() {
  printf("\n--- Testing Ended ---\n");
}

TestCase::TestCase(string title, string criteria, TestCaseStatus (*test)(Logger*), TestCase* on_success, TestCase* on_failure) {
  this->setTitle(title);
  this->setCriteria(criteria);
  this->setTest(test);
  this->setOnSuccess(on_success);
  this->setOnFailure(on_failure);
}

void TestCase::setTitle(string title) {
  this->title = title;
}

void TestCase::setCriteria(string criteria) {
  this->criteria = criteria;
}

void TestCase::setTest(TestCaseStatus (*test)(Logger*)) {
  this->test = test;
}

void TestCase::setOnSuccess(TestCase* on_success) {
  this->on_success = on_success;
}

void TestCase::setOnFailure(TestCase * on_failure) {
  this->on_failure = on_failure;
}

TestCaseInterface::TestCaseInterface() {
  this->test_cases = new vector<TestCase*>();
}

void TestCaseInterface::registerNewTest(TestCase* test_case) {
  this->test_cases->push_back(test_case);
}

bool TestCaseInterface::runTest(TestCase* test_case) {
  if (!test_case || !test_case->test) {
    return false;
  }
  cout << "Running " << test_case->title << " (" << test_case->criteria << ")" << endl;
  Logger logger;
  TestCaseStatus status = test_case->test(&logger);
  if (status == TestCaseStatus::UNKNOWN) {
    if (logger.fatal + logger.error) {
      return false;
    }
    else {
      return true;
    }
  }
  return status == TestCaseStatus::PASSED;
}

bool TestCaseInterface::runTests(TestCase* test_case) {
  if (!test_case || !test_case->test) {
    return false;
  }
  if (this->runTest(test_case)) {
    this->runTests(test_case->on_success);
  }
  else {
    this->runTests(test_case->on_failure);
  }
  return true;
}

void TestCaseInterface::startTests() {
  if (!this->test_cases->size()) {
    cout << "No test cases to run" << endl;
  }
  for (vector<TestCase*>::iterator it = this->test_cases->begin(); it != this->test_cases->end(); it++) {
    if (!(*it)) {
      printf("TestCase object is NULL. Ignoring");
      continue;
    }
    this->runTests(*it);
  }
}

TestCaseInterface::~TestCaseInterface() {
  delete this->test_cases;
}
