//unsigned long duration;
long minutePulseCount;

//Used to measure power.
//unsigned long pulseTime,lastTime;

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
    //System.sleep(D0,RISING);
}

void loop() {
    //duration = pulseIn(D0, HIGH);
    //Particle.publish("Duration", String(duration));
    //delay(5000);
    //Particle.publish("kWh", String(elapsedkWh));
    //if (dayPulseCount > 100000000) dayPulseCount = 0;
    //delay(60000);
    //Particle.publish("kW", String::format("%.2f",kilowatts));
}

void onPulse() {
    //used to measure time between pulses.
    //lastTime = pulseTime;
    //pulseTime = micros();
    
    //pulseCounter
    //dayPulseCount++;
    minutePulseCount++;
    
    //Calculate power
    //power = (3600000000.0 / (pulseTime - lastTime))/ppwh;
    
    //Find kwh elapsed
    //elapsedkWh = (1.0*dayPulseCount/(ppwh*1000)); //multiply by 1000 to convert pulses per wh to kwh
}

void onMinute() {
    //Mesh.on();
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
    //delay(5000);
    //Mesh.off();
}