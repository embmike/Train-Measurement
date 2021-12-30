#ifndef DEVICE_H
#define DEVICE_H

#include <cstdint>
#include <array>
#include <random>
#include <algorithm>
#include <string_view>
#include <fstream>


class Device
{
public:
    using filter_array = std::array<double,10>;
    using pose_array = std::array<double,2>;
    using system_matrix = std::array<std::array<double,2>,2>;

    enum struct DeviceState
    {
        UNDEFINED,
        INITILIZED,
        MEASURED,
        FILTERED,
        CALCULATED,
        PLOTTED
    };

    struct TimeStamp final
    {
        double timeStep;
        double velocity;
        double position; 
    };

    // Initialisiere das Gerät
    Device(double vel_mean, double vel_stddev, double dt);

    ~Device();

    // Messe die Geschwindigkeit
    double Measure_Velocity();

    // Filtere die Geschwindigkeit
    double Filter_Velocity();

    // Brechne den Weg
    double Calculate_Position();

    // Plotte ein Weg-Zeit-Deiagramm
    void Plot(std::size_t& iter);

    // Siche die Daten in ener Datei
    void Store(std::size_t& iter);


protected:
    Device() = delete;

    DeviceState _state { DeviceState::UNDEFINED };

    // Zufallsgenerator für die Geschwindigkeitsmessung
    std::mt19937 _generator {};
    std::normal_distribution<double> _distribution;
    double _measurement { 0.0 };

    // Filter der Geschwindigkeit
    filter_array _filterValues { 0.0 };

    // Berechnung der Position
    double _dt { 0.1 };

    // Systemgleichung: x(p) = A * x
    system_matrix _system_A {{ 
        {0.0,0.0}, 
        {0.0,0.0} 
    }};

    // Zustandsvektor x = (Position, Geschwindigkeit)
    pose_array _pose_x { 
        0.0, 
        0.0
    };

    void Set_Velocity(double val) {_pose_x[1] = val;}
    double Get_Velocity() {return _pose_x[1];}
    double Get_Position() {return _pose_x[0];}

    std::string_view LOG_DATA_PATH { "../analysis/log_data.csv" };
    std::ofstream _logDataStream;
};


#endif //DEVICE_H