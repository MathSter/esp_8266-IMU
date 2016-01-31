//Libary to drive 9 or 10 DOF sensor device for sparkfun. foxnovo or GY-91

#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <I2Cdev.h>

//sparkfun 9DOF
#include <ADXL345.h>
#include <ITG3200.h>
#include <HMC5843.h>

/*//GY-91*/
/*#include <BMP085.h>  //BMP285 */
/*#include <MPU9150.h> //MPU9250 */

/*//foxnovo*/
/*#include <L3GD20H.h>*/
/*#include <ADXL345.h>*/
/*#include <HMC5883L.h>*/
/*#include <BMP085.h>*/



    

#ifdef DEBUG_ESP_PORT
#define DEBUG_SENSOR DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_SENSOR
#endif

typedef struct 
{
  public:
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t mx, my, mz;
    
    float temperature;
    float pressure;
    float altitude;
    int32_t lastMicros;     
} measurements;

class sensors {
  private:
    // sensors
    ADXL345 accel;
    ITG3200 giro;
    HMC5843 mag;
    /*BMP085 barometer;*/
    /*MPU9250 accel, giro, mag*/
    // measurment
    measurements measurement;
    
    void takeMeasurment();
    
  public:
    void initialize();
    bool verify();
    const measurements& getMeasurment(){
        takeMeasurment();
        return measurement;
    };
//    measurements getMeasurment(){takeMeasurment(); return measurement;};
    
};




#endif /* _SENSORS_H_ */
