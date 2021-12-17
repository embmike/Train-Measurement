#include "device.hpp"


void Initialize_Device(Device& device)
{
    device.state = DeviceState::INITILIZED;
}


double Measure_Velocity(Device& device)
{
    device.state = DeviceState::MEASURED;
    return 1.0;
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