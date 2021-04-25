#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool comparator(const std::unique_ptr<Aircraft>& aa, const std::unique_ptr<Aircraft>& bb)
{
    auto a = aa.get();
    auto b = bb.get();
    if(a->has_reserved())
    {
        if(b->has_reserved())
        {
            return a->fuel_remaining() < b->fuel_remaining();
        }
        return true;
    }
    else 
    {
        if(b->has_reserved())
        {
            return false;
        }
        return a->fuel_remaining() < b->fuel_remaining();
    }
}

void AircraftManager::print_aircrafts()
{
    auto index = 0;
    for(const auto& current: aircrafts)
    {
        std::string tmp = "NotReserved";
        if(current.get()->has_reserved())
        {
            tmp = "Reserved";
        }
        std::cout << index << " - " << tmp << " / Fuel: " << current.get()->fuel_remaining() << std::endl;
        index++; 
    }
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(), comparator);
    //print_aircrafts();
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