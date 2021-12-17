#include "device.hpp"


void Initialize_Device(Device& dev, double speed_mean, double speed_stddev)
{
    dev.state = DeviceState::INITILIZED;

    std::random_device rd {};
	dev.generator = std::mt19937 {rd()};
	dev.distribution = std::normal_distribution<double> {speed_mean, speed_stddev};

    std::for_each(dev.filterValues.begin(), dev.filterValues.end(), [&speed_mean](double& d){d = speed_mean;});
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

    std::rotate(dev.filterValues.begin(), dev.filterValues.begin() + 1, dev.filterValues.end());
    dev.filterValues.at(0) = dev.measurement;
    dev.filterValue = std::accumulate(dev.filterValues.begin(), dev.filterValues.end(), 0) / dev.filterValues.size();

    return dev.filterValue;
}


double Calculate_Position(Device& dev)
{
    dev.state = DeviceState::CALCULATED;
    return 3.0;
}


void Plot(Device& dev)
{
    dev.state = DeviceState::PLOTTED;
}