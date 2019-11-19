long minutePulseCount;
//power and energy
double kilowatts;

//Number of pulses per wh - found or set on the meter.
int ppwh = 1; //1000 pulses/kwh = 1 pulse per wh

Timer minuteTimer(60000, onMinute);

void setup() {
    Particle.publish("Staring power monitor");
    pinMode(D0, INPUT);
    attachInterrupt(D0, onPulse, FALLING);
    minuteTimer.start();
}

void loop() {
}

void onPulse() {
    minutePulseCount++;
}

void onMinute() {
    if (!Mesh.ready()) {
        Mesh.connect();
    }
    kilowatts = minutePulseCount * 0.06;
    if (waitFor(Mesh.ready, 10000)) {
        char data[128];
        sprintf(data, "{\"power\":\%.2f\, \"watt_hour\":\%ld\}", kilowatts, minutePulseCount);
        Mesh.publish("current-power", data);
    }
    minutePulseCount = 0;
}