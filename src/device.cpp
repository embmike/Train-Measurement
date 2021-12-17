#include "device.hpp"
#include <iostream>


void Initialize_Device( Device& dev, double speed_mean, double speed_stddev, double dt)
{
    dev.state = DeviceState::INITILIZED;

    // Zufallsgenerator für die Geschwindigkeitsmessung
    std::random_device rd {};
	dev.generator = std::mt19937 {rd()};
	dev.distribution = std::normal_distribution<double> {speed_mean, speed_stddev};

    // Initialisiere Filter mit dem Mittelwert
    std::for_each(dev.filterValues.begin(), dev.filterValues.end(), [&speed_mean](double& d){d = speed_mean;});

    // Abtastrate
    dev.dt = dt;
}


double Measure_Velocity(Device& dev)
{
    dev.state = DeviceState::MEASURED;

    dev.measurement = dev.distribution(dev.generator);

    return dev.measurement;
}


double Filter_Velocity(Device& dev)
{
    dev.state = DeviceState::FILTERED;

    // Gleitender Mittelwertfilter
    std::rotate(dev.filterValues.rbegin(), dev.filterValues.rbegin() + 1, dev.filterValues.rend());
    dev.filterValues.at(0) = dev.measurement;
    dev.filterValue = std::accumulate(dev.filterValues.begin(), dev.filterValues.end(), 0) / dev.filterValues.size();

    return dev.filterValue;
}


double Calculate_Position(Device& dev)
{
    dev.state = DeviceState::CALCULATED;

    dev.position += dev.filterValue * dev.dt;

    return dev.position;
}


void Plot(Device& dev)
{
    dev.state = DeviceState::PLOTTED;

    std::cout << "v=" << dev.filterValue << " m/s"
              << " / " 
              << "s=" << dev.position << " m\n";
}
