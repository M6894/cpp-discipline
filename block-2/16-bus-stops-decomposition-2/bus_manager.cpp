#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "bus_manager.h"
#include "responses.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
    buses_to_stops[bus] = stops;
    for (string& stop : buses_to_stops[bus]) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
    stringstream ss;
    if (stops_to_buses.count(stop) == 0) {
        ss << "No stop"; // << endl;
    } else {
        for (const string& bus : stops_to_buses.at(stop)) {
            ss << bus << " ";
        }
        // ss << endl;
    }
    return {ss.str()};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
    stringstream ss;
    if (buses_to_stops.count(bus) == 0) {
        ss << "No bus"; // << endl;
    } else {
        bool first = true;
        for (const string& stop : buses_to_stops.at(bus)) {
            if (!first) {
                ss << "\n";
            }
            first = false;
            ss << "Stop " << stop << ": ";
            if (stops_to_buses.at(stop).size() == 1) {
                ss << "no interchange";
            } else {
                for (const string& other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        ss << other_bus << " ";
                    }
                }
            }
            // cout << endl;
        }
    }
    return {ss.str()};
}

AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    stringstream ss;
    if (buses_to_stops.empty()) {
        ss << "No buses"; // << endl;
    } else {
        bool first = true;
        for (const auto& bus_item : buses_to_stops) {
            if (!first) {
                ss << "\n";
            }
            first = false;
            ss << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                ss << stop << " ";
            }
        }
    }
    return {ss.str()};
}