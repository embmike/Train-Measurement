#include <iostream>
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
void for_each_sample(uint32_t& counter, const uint32_t size, std::function<void(void)> drive)
{
    for(; counter < size; counter++)
    {
        drive();
    }
}

int main(int, char**)
{
    // Initialisiere das Gerät
    Initialize_Device(TestSet::device, TestSet::speed_mean, TestSet::speed_stddev, TestSet::dt);

    // Fahre mit dem Gerät
    auto Drive_Device = [](){
        // Messen die Geschwindigkeit
        Measure_Velocity(TestSet::device);

        // Filtere die Geschwindigkeit
        Filter_Velocity(TestSet::device);

        // Brechne den Weg
        Calculate_Position(TestSet::device);

        // Plotte ein Weg-Zeit-Deiagramm
        Plot(TestSet::device);
    };

    for_each_sample(TestSet::counter, TestSet::samples, Drive_Device);
}
