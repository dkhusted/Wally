#include "Particle.h"
#include "Arduino.h"
#include "Wire.h"

/*   Global Variables                         */
//Buffer for features 96*96 = 9216 floats
float *feature_buf = (float *) malloc(9216*sizeof(float)); 
int buf_ix = 0;


// Når den modtager "end" aka 6 bytes så har den modtaget de sidste features fra billedet før dette. TODO
// e=101 n=110 d= 100 --> 311
void receiveEvent(int howMany) {
    //Features sendt float * 10000. Needs to be divided by 10000
    float feature = 0.0;
    while(Wire.available())
    {
        int s_receive = Wire.read();
        feature = (feature + s_receive) / 100;
    }
    Serial.println("Feature from master:");    
    Serial.println(feature,4);    
    feature_buf[buf_ix] = feature;
    buf_ix = buf_ix + 1;
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);

    Serial.println("Test of Transporting img data from Arduino to Argon, via I2C");

    Serial.println();
    memset(feature_buf, 0, sizeof(*feature_buf));
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
}



// I2C TEST
void loop(){


}

