#include "aircraft_factory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type)
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    std::string flight_number;// = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    do {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    } 
    while(flight_numbers.find(flight_number) != flight_numbers.end());
    flight_numbers.insert(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower()); 
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft()
{
    return create_aircraft(*(aircraft_types[rand() % 3]));
}

std::string AircraftFactory::get_airline(const int index)
{
    assert(index < 0 || index > sizeof(airlines)/sizeof(airlines[0]) && " index out of bound");
    return airlines[index];
}