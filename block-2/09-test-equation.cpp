#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
             os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    double disc = b * b - 4 * a * c;
    // Проверка на квадратное / линейное уравнение
    if (a != 0) {
        if (disc > 0) {
            // int first = (-b + sqrt(disc)) / (2 * a);
            // int second = (-b - sqrt(disc)) / (2 * a);
            return 2;
        }
        if (disc == 0) {
            return 1;
            // cout << (-b + sqrt(disc)) / (2 * a) << endl;
        } else {
            return 0;
        }
    } else {
        if (!((b == 0 && c == 0) || (b == 0 && c != 0))) {
            return 1;
            // cout << -(c / b) << endl;
        } else { 
            return 0;
        }
    }
}

void TestQuadratic() {
    AssertEqual(GetDistinctRealRootCount(2, 5, 2), 2, "random 2 5 2");
    AssertEqual(GetDistinctRealRootCount(2, 5, 2), 2, "random 2 5 3");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "same roots 2 4 2");
    AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "zero roots 2 1 2");
    AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0, "zero division 0 0 2");
    AssertEqual(GetDistinctRealRootCount(2, 0, 0), 1, "2x^2 = 0 (2 0 0)");    
}

void TestLinear() {
    AssertEqual(GetDistinctRealRootCount(0, 4, 10), 1, "2 operands 0 4 10");
    AssertEqual(GetDistinctRealRootCount(0, 4, 0), 1, "1 operand 0 4 10");
    AssertEqual(GetDistinctRealRootCount(0, 0, 99999), 0, "zero division 0 0 2");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestQuadratic, "TestQuadratic");
    runner.RunTest(TestLinear, "TestLinear");
}

int main() {
    TestAll();
    // добавьте сюда свои тесты
    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
	os << "{";
	bool first = true;
	for (const auto &kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string &hint) { AssertEqual(b, true, hint); }

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string &test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception &e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

void TestRootCount() {
	mt19937 gen;
	uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i) {
		const auto a = unif(gen);
		const auto b = unif(gen);
		const auto c = unif(gen);

		const auto count = GetDistinctRealRootCount(a, b, c);

		Assert(count >= 0 && count <= 2,
			"Quadratic equation has only 0, 1 or 2 real roots.");
	}
}

void TestOneRoot() {
	mt19937 gen;
	uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i) {
		const auto x_1 = unif(gen);

		const auto p = x_1 + x_1;
		const auto q = x_1 * x_1;

		const auto count = GetDistinctRealRootCount(1, p, q);
		stringstream description;
		description << showpos << "x^2" << p << "x" << q
			<< " = 0 has 1 real root.";

		AssertEqual(count, 1, description.str());
	}
}

void TestNoRoots() {
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
		"x^2+1 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
		"x^2+3x+4 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
		"x^2-2x+10 = 0 has 0 real roots.");
}

void TestLinearEquation() {
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
		"2x+1 = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
		"-x = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
		"120x - 10 = 0 has 1 real root.");
}

void TestConstant() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
		"c = 0, where c = 1 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
		"c = 0, where c = -10 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
		"c = 0, where c = 189238910 has 0 real roots.");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRootCount, "TestRootCount");
	runner.RunTest(TestOneRoot, "TestOneRoot");
	runner.RunTest(TestNoRoots, "TestNoRoots");
	runner.RunTest(TestLinearEquation, "TestLinearEquation");
	runner.RunTest(TestConstant, "TestConstant");
	return 0;
}
*/



/* Task:
Функция
int GetDistinctRealRootCount(double a, double b, double c);

возвращает количество уникальных действительных корней уравнения ax² + bx + c = 0. 
Разработайте набор юнит-тестов для проверки корректности реализации этой функции. 
Случай, когда все три коэффициента равны нулю, тестировать не надо.

Начать работу вы можете с шаблона, который содержит наш фреймворк юнит-тест и заготовку 
функции GetDistinctRealRootCount.

test_equation.cpp

*/