#include "device.hpp"
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

    state = DeviceState::FILTERED;    state = DeviceState::FILTERED;
    return velocity;
}


double Device::Calculate_Position()
{
    position += velocity * dt;

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
