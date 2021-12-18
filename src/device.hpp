#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>
#include <array>
#include <random>
#include <algorithm>


class Device final
{
public:
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

    // Initialisiere das Gerät
    Device(double speed_mean, double speed_stddev, double dt);

    // Messen die Geschwindigkeit
    double Measure_Velocity();

    // Filtere die Geschwindigkeit
    double Filter_Velocity();

    // Brechne den Weg
    double Calculate_Position();

    // Plotte ein Weg-Zeit-Deiagramm
    void Plot(std::size_t& iter);

private:
    Device() = delete;

    DeviceState state { DeviceState::UNDEFINED };

    // Zufallsgenerator für die Geschwindigkeitsmessung
    std::mt19937 generator {};
	std::normal_distribution<double> distribution;
    double measurement { 0.0 };

    // Filter der Geschwindigkeit
    filter_array filterValues { 0.0 };
    double velocity { 0.0 };

    // Berechnung der Position
    double dt { 0.1 };
    double position { 0.0 };
};


#endif //DEVICE_H