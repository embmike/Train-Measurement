#include "device.hpp"
#include "matrix.hpp"
#include <iostream>
#include <iomanip>


Device::Device(double speed_mean, double speed_stddev, double dt)
{
    // Zufallsgenerator für die Geschwindigkeitsmessung
    std::random_device rd {};
	generator = std::mt19937 {rd()};
	distribution = std::normal_distribution<double> {speed_mean, speed_stddev};

    // Initialisiere Filter mit dem Mittelwert
    std::for_each(filterValues.begin(), filterValues.end(), [&speed_mean](double& d){d = speed_mean;});

    // Abtastrate
    dt = dt;

    // Systemnarix A
    system_A = {{
        {1.0,  dt},
        {0.0, 1.0}
    }};

    // Initialisiere Zustandsvektor x = (position, velocity)
    pose_x = {
        0.0,
        speed_mean
    };

    state = DeviceState::INITILIZED;
}


double Device::Measure_Velocity()
{
    measurement = distribution(generator);

    state = DeviceState::MEASURED;
    return measurement;
}


double Device::Filter_Velocity()
{
    // Gleitender Mittelwertfilter
    std::rotate(filterValues.rbegin(), filterValues.rbegin() + 1, filterValues.rend());
    filterValues.at(0) = measurement;
    velocity = std::accumulate(filterValues.begin(), filterValues.end(), 0) / filterValues.size();

    state = DeviceState::FILTERED;
    return velocity;
}


double Device::Calculate_Position()
{
    /*
     * Berechne die neue Position x(k+1) = A * x(k)
     * 1: Aktualisiere Geschwindigkeit
     * 2: Berechne die neuen Zustandsvariablen
     * 3: Extrahiere die neue Position
     */
    pose_x.at(1) = velocity;
    pose_x = mvmul(system_A, pose_x);
    position = pose_x[0];

    state = DeviceState::CALCULATED;
    return position;
}


void Device::Plot(std::size_t& iter)
{
    std::cout << std::setprecision(1) << std::fixed << iter * dt << " s: "
              << "v=" << velocity << " m/s"
              << " / " 
              << "s=" << std::setw(5) << std::setfill(' ') << position<< " m\n";

    state = DeviceState::PLOTTED;
}
