#pragma once

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int nb_crashed_aircraft = 0;

    void print_aircrafts();

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;

    void printsNumberAircraftByAirlines(const std::string &airlineType) const;

    int get_required_fuel() const;

    int get_nb_crashed_aircraft() const;
};