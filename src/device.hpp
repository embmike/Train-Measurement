#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>
#include <array>

using filter_array = std::array<double,10>;

enum struct DeviceState
{
    UNDEFINED,
    INITILIZED,
    MEASURED,
    FILTERED,
    CALCULATED,
    PLOTTED
};

struct Device
{
    DeviceState state { DeviceState::UNDEFINED };
    uint32_t lastPosition { 0 };
    filter_array filterValues { 0 };
};

// Initialisiere das Gerät
void Initialize_Device(Device&);

// Messen die Geschwindigkeit
double Measure_Velocity(Device&);

// Filtere die Geschwindigkeit
double Filter_Velocity(Device&);

// Brechne den Weg
double Calculate_Position(Device&);

// Plotte ein Weg-Zeit-Deiagramm
void Plot(Device&);

#endif //DEVICE_H