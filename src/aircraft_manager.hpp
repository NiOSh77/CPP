#pragma once

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

    void print_aircrafts();

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;

    void printsNumberAircraftByAirlines(const std::string &airlineType) const;

    int get_required_fuel() const;
};