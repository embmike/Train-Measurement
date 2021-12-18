# Den Weg eines Fahrzeugs aus seiner Geschwindigkeit ermitteln

## 1. Blockschaltbild des Geräts

<br>

<!-- ![Blockschaltbild](./images/v_s_bsb.PNG) -->
<img src="./images/v_s_bsb.PNG" alt="Blockschaltbild" width="50%" height="50%" />  

<br>
<br>

## 2. Entwicklungsschritte

Entwicklungsschritte sind:
-	2.1. Formuliere die Idee mit einem Blockschaltbild (BSB)
-	2.2. Erstelle ein C++-Projekt in Visual Studio Code
-	2.3. Schreibe die einzelnen [Arbeitsschritte](#link3) des BSD auf
-   2.4. Deklariere die [Schnittstelle](#link4) und inkludiere sie
-   2.5. Definiere die [Funktionsrümpfe](#link5) und rufe die Schnittstelle auf
-   2.6. Definiere alle [Funktionen](#link6)
-   2.7. Definiere zu jeder Funktion ein Unit-Test
-	2.8. Dokumentation (Dateien und md-Datei) abschließen

<br>
<br>

### <span id="link3">2.3. Schreibe die einzelnen Arbeitsschritte des BSD auf</span>

*Wie bei einem Hausbau zeichnet zuerst eine Architekt das Haus. Der Softwerker pinselt ein Blockschaltbild seiner Idee.*

Schreibe den Ablauf des Blockschaltbilds als Kommentar auf:
-   Definere das Testset. 
    -   Ein Zug fährt mit konstanter Geschwindigkeit.
    -   Ein Messgerät misst die Geschwindigkeit und ermittelt daraus die aktuelle Position. 
-   Die Messung soll 10s mit einer Auflösung von 100ms dauern.
-   Für die Iteration der Abtaswerte soll die "for_each_iter"-Funktion verwendet werden.
    -   Ach, die existiert noch garnicht. Kommt später. :smiley:


Datei main.cpp:
```C++
//...

//Erstelle Device und lege Parameter fest
namespace TestSet
{
    // Testgerät
    constexpr double speed_mean { 80.0 };  // m/s
    constexpr double speed_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    // the device object
    
    // Testlauf
    constexpr double time { 10.0 }; // 10s
    constexpr std::size_t samples { static_cast<uint32_t>(time / dt) };
    std::size_t counter { 0 };
}

int main(int, char**)
{
    // The device is a train - the Maglev

    // 1 - Gruppiere Fahren mit dem Zug zu einer Lambda-Funktion
    auto Drive_Train = [](std::size_t& iter){
        // 1.1. - Messen die Geschwindigkeit

        // 1.2. - Filtere die Geschwindigkeit

        // 1.3. - Brechne den Weg

        // 1.4. - Plotte ein Weg-Zeit-Deiagramm
    };

    // Endlich fahren
    for_each_iter(TestSet::counter, TestSet::samples, Drive_Train);
}

// ...
```

<br>

### <span id="link4">2.4. Deklare die Schnittstelle und inkludiere sie</span>

*Nun erfolgt der Rohbau. Der Softwerker deklariert die Schnistelle als Funktionen.*

Datei functional_iter.hpp:

```C++
// ...

// Berechne über für jede Iteration
void for_each_iter(std::size_t& iter, const size_t size, std::function<void(void)> fn);
void for_each_iter(std::size_t& iter, const size_t size, std::function<void(std::size_t&)> fn);

// ...
```
<br>

Datei device.hpp:

```C++
// ...

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
};

// ....
```

<br>

### <span id="link5">2.5. Definiere die Funktionsrümpfe und rufe die Schnittstelle auf</span>

*Der Rohbau schreitet voran. Der Softwerker definiert die Schnittstellen-Funtionen als Funktionsrümpfe.*
*Jede Funktion setzt einen Zusatand. Die Funktionen werden in der "Main"-Funktion geordnet aufgerufen*

*Nun wird der Rohbau abgenommen. Der Softwerker testet den korrekten Aufruf der Schnittstellen mittels der Zustaände im Debugger*

Datei device.cpp:

```C++
// ...

Device::Device(double speed_mean, double speed_stddev, double dt)
{
    dev.state = DeviceState::INITILIZED;
}


double Device::Measure_Velocity()
{
    state = DeviceState::MEASURED;

    return 1.0;
}


double Device::Filter_Velocity()
{
    state = DeviceState::FILTERED;

    return 2.0;
}


double Device::Calculate_Position()
{
    state = DeviceState::CALCULATED;

    return 3.0;
}


void Device::Plot()
{
    state = DeviceState::PLOTTED;
}

// ....
```
<br>

Datei main.cpp:

```C++
// ....

//Erstelle Device und lege Parameter fest
namespace TestSet
{
    // Testgerät
    constexpr double speed_mean { 80.0 };  // m/s
    constexpr double speed_stddev { 8.0 }; // m/s
    constexpr double dt { 0.1 };    // 100ms
    Device device {speed_mean, speed_stddev, dt};
    
    // Testlauf
    constexpr double time { 10.0 }; // 10s
    constexpr std::size_t samples { static_cast<uint32_t>(time / dt) };
    std::size_t counter { 0 };
}


int main(int, char**)
{
    // The device is a train - the Maglev
    [[maybe_unused]] Device& train { TestSet::device };

    // 1 - Gruppiere Fahren mit dem Zug zu einer Lambda-Funktion
    auto Drive_Train = [&train](std::size_t& iter){
        // 1.1. - Messen die Geschwindigkeit
        train.Measure_Velocity();

        // 1.2. - Filtere die Geschwindigkeit
        train.Filter_Velocity();

        // 1.3. - Brechne den Weg
        train.Calculate_Position();

        // 1.4. - Plotte ein Weg-Zeit-Deiagramm
        train.Plot(iter);
    };

    // Endlich fahren
    for_each_iter(TestSet::counter, TestSet::samples, Drive_Train);
}

// ...
```
<br>

### <span id="link6">2.6. Definiere alle Funktionen</span>

*Beim Innausbau erstellt jedes Gewerk seine Einrichungen, der Rohrleger verlegt die Fussbodenheizung, der Elektriker die Kabel. 
Analog impementiert der Softwerker seine Funktionen*

Die Implementierung erfolt in kompakter funktionsorientierter Form, für Schleifen werden Funktionen gewählt - siehe Beispiele.

Datei functional_iter.cpp

```C++
// ...

void for_each_iter(std::size_t& iter, const size_t size, std::function<void(std::size_t&)> fn)
{
    for(; iter < size; iter++)
    {
        fn(iter);
    }   
}

// ..
```

<br>

Datei device.cpp:

```C++
// ...

double Device::Filter_Velocity()
{
    // Gleitender Mittelwertfilter
    std::rotate(filterValues.rbegin(), filterValues.rbegin() + 1, filterValues.rend());
    filterValues.at(0) = measurement;
    velocity = std::accumulate(filterValues.begin(), filterValues.end(), 0) / filterValues.size();

    state = DeviceState::FILTERED;    state = DeviceState::FILTERED;
    return velocity;
}

// ...
```

<br>
<br>

## 3. Debuggen

*Jedes Gewerk prüft seine Einrichtungen, der Elektriker prüft seie Schaltungen, der Softwerker seine Funktionen*
*Deutsches Handwerk kommt von können, nicht von schauen wir mal* :satisfied:

Debuggen durh die Applikation:

![Debug-Image](./images/debug_view3.PNG)

<br>
<br>

## 3. Unit-Test

*Am Ende steht die Abhame, der Elektromeister prüft die Isolationswiderstände, der Bauleiter das gesamte Haus.*
*Der Softwerker seine Arbeit durch Unit-Tests. Leider sind gerade alle noch beschäftigt.* :unamused:

<br>
<br>

## 3. Fazit und Ausblick

Mit dem Wechsel zur Objekorientierung wurden funtionale Aufrufe weiter abstahiert, die allgemeinere "for_each_iter"-Funktion zeigt es deitlich.
Es ergibt sich eine bessere Kohäsion zwischen den Geräte-Parametern und den darauf angewendeten Geräte-Funktionen.

**Offene Punkte**
-   Unit-Test
-   Messdaten in eine datei speichen
-   Messdaten mittels Python visualisieren

<br>
