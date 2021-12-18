#include <iostream>
#include <functional>
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
    uint32_t counter { 0 };
}

// Berechne alle für jeden Abtastwert
void for_each_sample(Device& dev, uint32_t& counter, const uint32_t size, std::function<void(Device& device)> drive)
{
    for(; counter < size; counter++)
    {
        drive(dev);
    }
}

int main(int, char**)
{
    // 0 - Initialisiere das Gerät
    Initialize_Device(TestSet::device, TestSet::speed_mean, TestSet::speed_stddev, TestSet::dt);

    // 1 - Fahre mit dem Gerät
    auto Drive_Device = [](Device& device){
        // 1.1. - Messen die Geschwindigkeit
        Measure_Velocity(device);

        // 1.2. - Filtere die Geschwindigkeit
        Filter_Velocity(device);

        // 1.3. - Brechne den Weg
        Calculate_Position(device);

        // 1.4. - lotte ein Weg-Zeit-Deiagramm
        Plot(device);
    };

    // Endlich fahren
    for_each_sample(TestSet::device, TestSet::counter, TestSet::samples, Drive_Device);
}
