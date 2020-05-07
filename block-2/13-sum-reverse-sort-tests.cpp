#include "13-sum-reverse-sort-tests.h"
#include "13-sum-reverse-sort.h"
#include "test_runner.h"

#include <algorithm>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void TestSum() {
    AssertEqual(Sum(2, 2), 4, "2 + 2");
    AssertEqual(Sum(0, 0), 0, "0 + 0");
    AssertEqual(Sum(-2, -2), -4, "-2 + -2");
}

void TestReverse() {
    string s = "Hi!";
    AssertEqual(Reverse(s), "!iH", "Hi!");
}

void TestSort() {
    vector<int> vec = {2, 1, 555};
    vector<int> ref = {1, 2, 555};
    Sort(vec);
    AssertEqual(vec, ref, "2, 1, 555");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestSum, "TestSum");
    runner.RunTest(TestReverse, "TestReverse");
    runner.RunTest(TestSort, "TestSort");
}