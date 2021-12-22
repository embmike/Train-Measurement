#include <iostream>
#include "functional_iter.hpp"
#include "device.hpp"

#define Drive_Train for_each_iter

//Erstelle Device und lege Parameter fest
namespace TestSet
{
    // Testgerät
    constexpr double velocity_mean { 80.0 };  // m/s
    constexpr double velocity_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    Device device {velocity_mean, velocity_stddev, dt};
    
    // Testlauf
    constexpr double time { 10.0 }; // 10s
    constexpr std::size_t samples { static_cast<uint32_t>(time / dt) };
    std::size_t counter { 0 };
}

void Monitor_TrainDrive(std::size_t& iter)
{
    // Der Zug
    Device& train { TestSet::device };

    // 1.1. - Messen die Geschwindigkeit
    train.Measure_Velocity();

    // 1.2. - Filtere die Geschwindigkeit
    train.Filter_Velocity();

    // 1.3. - Brechne den Weg
    train.Calculate_Position();

    // 1.4. - Plotte eine Weg-Zeit-Übersicht
    train.Plot(iter);
    train.Store(iter);
}


int main(int, char**)
{
    // Der Zug, Shinkansen fährt konstant mit einer mittleren Geschwindigkeit von 80m/s.
    // Das Monitorgerät soll aus der Geschwindigkeit die aktuelle Position berechnen und anzeigen.
    Drive_Train(TestSet::counter, TestSet::samples, Monitor_TrainDrive);
}
