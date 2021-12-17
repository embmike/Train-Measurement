#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>
#include <array>
#include <random>

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

    // Zufallsgenerator für die Messung
    std::mt19937 generator;
	std::normal_distribution<double> distribution;

    double measurement { 0.0 };

    uint32_t lastPosition { 0 };
    filter_array filterValues { 0 };
};

// Initialisiere das Gerät
void Initialize_Device(Device&, double speed_mean, double speed_stddev);

// Messen die Geschwindigkeit
double Measure_Velocity(Device&);

// Filtere die Geschwindigkeit
double Filter_Velocity(Device&);

// Brechne den Weg
double Calculate_Position(Device&);

// Plotte ein Weg-Zeit-Deiagramm
void Plot(Device&);

#endif //DEVICE_H