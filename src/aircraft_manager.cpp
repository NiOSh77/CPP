#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft> &aircraft) {return !aircraft->update();}), aircrafts.end());
    return true;
}

void AircraftManager::printsNumberAircraftByAirlines(const std::string &airlineType) const
{
    std::cout << airlineType << " : " << std::count_if(aircrafts.begin(), aircrafts.end(), 
    [airlineType](const std::unique_ptr<Aircraft> &aircraft) 
        {
            return aircraft->get_flight_num().substr(0, 2) == airlineType;
        }) << std::endl;
}