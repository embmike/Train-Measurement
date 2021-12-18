#include <iostream>
#include <array>
#include "device.hpp"

//Erstelle Device und lege Parameter fest
namespace TestSet
{
    Device device;
    constexpr double speed_mean { 80.0 };  // m/s
    constexpr double speed_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    constexpr double time { 10.0 }; // 10s
    constexpr uint32_t samples { static_cast<uint32_t>(time / dt) };
}


int main(int, char**)
{
    // Initialisiere das Gerät
    Initialize_Device(TestSet::device, TestSet::speed_mean, TestSet::speed_stddev, TestSet::dt);

    // Fahre mit dem Gerät
    for(uint32_t counter = 0; counter < TestSet::samples; counter++)
    {
        // Messen die Geschwindigkeit
        Measure_Velocity(TestSet::device);

        // Filtere die Geschwindigkeit
        Filter_Velocity(TestSet::device);

        // Brechne den Weg
        Calculate_Position(TestSet::device);

        // Plotte ein Weg-Zeit-Deiagramm
        Plot(TestSet::device);
    }
}
