#include "sensors.h"

void sensors::initialize(){
    // initialize devices
    Serial.println("Initializing I2C devices...");
    accel.initialize();
    giro.initialize();
    mag.initialize();
    
    if(!verify()){
        delay(500);
    }
    
    // Set accel
    Serial.println("setup accel");
    //rate
    accel.setRate(ADXL345_RATE_400);
    //gain
    accel.setRange(ADXL345_RANGE_16G); 
    //mode
    accel.setFIFOMode(ADXL345_FIFO_MODE_BYPASS);
    accel.setFullResolution(1);
    accel.setDataJustification(0);
    accel.setMeasureEnabled(true);
    
    // Set Mag
    Serial.println("setup mag");
    //rate
    mag.setDataRate(HMC5843_RATE_50);
    //gain
    mag.setGain(HMC5843_GAIN_1300);
    //mode
    mag.setMeasurementBias(HMC5843_BIAS_NORMAL);
    mag.setMode(HMC5843_MODE_CONTINUOUS);

    
    // Set Giro
    Serial.println("setup giro");
    //rate
    giro.setRate(39); // F_sample = F_internal / (divider+1)
    giro.setDLPFBandwidth(ITG3200_DLPF_BW_256);
    //gain
    giro.setFullScaleRange(ITG3200_FULLSCALE_2000);
    //mode
    
};

void debug_sensor_failed(const char* device, const uint8_t& id){
    char const* fail_format = "%s device connections failed: id: %d";
//    DEBUG_SENSOR(sprintf(fail_format,device, id));
    Serial.printf(fail_format,device, id);
}

bool sensors::verify(){
    // verify connection
    Serial.println("Testing device connections...");
    if (!accel.testConnection())
    {
        debug_sensor_failed("accel",accel.getDeviceID());   
        return false;
    };
    if (!giro.testConnection())
    {
        debug_sensor_failed("giro",giro.getDeviceID());
        return false;   
    };
    if (!mag.testConnection())
    {
        debug_sensor_failed("mag",mag.getIDA());
        return false;
    };
    return true;
};

void sensors::takeMeasurment(){
    measurements& m = measurement; 
    // read raw heading measurements from devices
    mag.getHeading(&m.mx, &m.my, &m.mz);
    // read raw giro measurements from devices
    giro.getRotation(&m.gx, &m.gy, &m.gz);
    // read raw accel measurements from device
    accel.getAcceleration(&m.ax, &m.ay, &m.az);
    measurement.temperature = giro.getTemperature();
};
