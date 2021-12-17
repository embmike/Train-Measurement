#include <iostream>
#include "device.hpp"

int main(int, char**)
{
    // Erstelle Device
    Device device;

    // Initialisiere das Gerät
    Initialize_Device(device);

    // Messen die Geschwindigkeit
    Measure_Velocity(device);

    // Filtere die Geschwindigkeit
    Filter_Velocity(device);

    // Brechne den Weg
    Calculate_Position(device);

    // Plotte ein Weg-Zeit-Deiagramm
    Plot(device);
}
