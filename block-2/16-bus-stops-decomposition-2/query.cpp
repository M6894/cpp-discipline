#include <string>
#include <iostream>
#include "query.h"

using namespace std;

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    if (string operation; is >> operation) {
        if (operation == "NEW_BUS") {
            q.type = QueryType::NewBus;
            is >> q.bus;
            int stops_count = 0;
            is >> stops_count;
            q.stops.resize(stops_count);
            for (string& stop : q.stops) {
                is >> stop;
            }
        } else if (operation == "BUSES_FOR_STOP") {
            q.type = QueryType::BusesForStop;
            is >> q.stop;
            return is;
        } else if (operation == "STOPS_FOR_BUS") {
            q.type = QueryType::StopsForBus;
            is >> q.bus;
        } else if (operation == "ALL_BUSES") {
            q.type = QueryType::AllBuses;
        }
    }
    return is;
}