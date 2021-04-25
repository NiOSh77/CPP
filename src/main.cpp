#include "tower_sim.hpp"
#include "geometry.hpp"

void test_generic_points();

int main(int argc, char **argv)
{
    //test_generic_points();
    TowerSimulation simulation{argc, argv};
    simulation.launch();

    return 0;
}

void test_generic_points()
{
    Point<float, 2UL> p1;
    Point<float, 2UL> p2;
    //auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    std::cout << p1 << std::endl;
}