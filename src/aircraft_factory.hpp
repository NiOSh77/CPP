#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <memory>

class AircraftFactory {
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    Airport *airport;
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    const AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::set<std::string> flight_numbers;


public:
    AircraftFactory(Airport *airport_) 
    : airport (airport_)
    {
    }

    std::string get_airline(const int index);

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    void init(Airport* airport_)
    {
        airport = airport_;
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .10f, .02f, MediaPath { "concorde_af.png" } };
    }

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type);
    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft();
};