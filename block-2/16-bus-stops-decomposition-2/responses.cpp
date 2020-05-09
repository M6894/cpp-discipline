#include <iostream>
#include <string>
#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    os << r.result;
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    cout << r.result;
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    cout << r.result;
    return os;
}