#include <iostream>
#include "functional_iter.hpp"
#include "device.hpp"

//Erstelle Device und lege Parameter fest
namespace TestSet
{
    // Testgerät
    constexpr double speed_mean { 80.0 };  // m/s
    constexpr double speed_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    Device device {speed_mean, speed_stddev, dt};
    
    // Testlauf
    constexpr double time { 10.0 }; // 10s
    constexpr std::size_t samples { static_cast<uint32_t>(time / dt) };
    std::size_t counter { 0 };
}


int main(int, char**)
{
    // The device is a train - the Maglev
    [[maybe_unused]] Device& train { TestSet::device };

    // 1 - Gruppiere Fahren mit dem Zug zu einer Lambda-Funktion
    auto Drive_Train = [&train](std::size_t& iter){
        // 1.1. - Messen die Geschwindigkeit
        train.Measure_Velocity();

        // 1.2. - Filtere die Geschwindigkeit
        train.Filter_Velocity();

        // 1.3. - Brechne den Weg
        train.Calculate_Position();

        // 1.4. - Plotte ein Weg-Zeit-Deiagramm
        train.Plot(iter);
    };

    // Endlich fahren
    for_each_iter(TestSet::counter, TestSet::samples, Drive_Train);
}
