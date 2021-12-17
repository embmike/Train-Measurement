#include "device.hpp"


void Initialize_Device(Device& device, double speed_mean, double speed_stddev)
{
    device.state = DeviceState::INITILIZED;

    std::random_device rd {};
	device.generator = std::mt19937 {rd()};
	device.distribution = std::normal_distribution<double> {speed_mean, speed_stddev};
}


double Measure_Velocity(Device& device)
{
    device.state = DeviceState::MEASURED;

    device.measurement = device.distribution(device.generator);

    return device.measurement;
}


double Filter_Velocity(Device& device)
{
    device.state = DeviceState::FILTERED;
    return 2.0;
}


double Calculate_Position(Device& device)
{
    device.state = DeviceState::CALCULATED;
    return 3.0;
}


void Plot(Device& device)
{
    device.state = DeviceState::PLOTTED;
}