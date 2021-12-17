#include <iostream>
#include "device.hpp"

int main(int, char**)
{
    // Erstelle Device und lege Parameter fest
    Device device;
    double speed_mean {80.0f};
    double speed_stddev {8.0f};

    // Initialisiere das Gerät
    Initialize_Device(device, speed_mean, speed_stddev);

    // Messen die Geschwindigkeit
    Measure_Velocity(device);

    // Filtere die Geschwindigkeit
    Filter_Velocity(device);

    // Brechne den Weg
    Calculate_Position(device);

    // Plotte ein Weg-Zeit-Deiagramm
    Plot(device);
}
