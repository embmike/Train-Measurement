#include <iostream>
#include <array>
#include "device.hpp"


int main(int, char**)
{
    // Erstelle Device und lege Parameter fest
    Device device;
    constexpr double speed_mean { 80.0 };  // m/s
    constexpr double speed_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    constexpr double time { 10.0 }; // 10s
    constexpr uint32_t samples { static_cast<uint32_t>(time / dt) };

    // Initialisiere das Gerät
    Initialize_Device(device, speed_mean, speed_stddev, dt);

    // Fahre mit dem Gerät
    for(uint32_t counter = 0; counter < samples; counter++)
    {
        // Messen die Geschwindigkeit
        Measure_Velocity(device);

        // Filtere die Geschwindigkeit
        Filter_Velocity(device);

        // Brechne den Weg
        Calculate_Position(device);

        // Plotte ein Weg-Zeit-Deiagramm
        Plot(device);
    }
}
