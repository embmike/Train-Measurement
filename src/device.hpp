#ifndef DEVICE_H
#define DEVICE_H

// Initialisiere das Gerät
void Initialize();

// Messen die Geschwindigkeit
double MeasureVelocity();

// Filtere die Geschwindigkeit
double Filter_Velocity(double);

// Brechne den Weg
double Calculate_Position(double, double);

// Plotte ein Weg-Zeit-Deiagramm
double Plot(double);

#endif //DEVICE_H