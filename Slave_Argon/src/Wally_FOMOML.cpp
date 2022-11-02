#include "Particle.h"
#include "Arduino.h"
#include "Wire.h"

#ifdef FOMO
#line 1 "/home/kultul/Code_workspace/Particle_Io/Wally_FOMOML/src/Wally_FOMOML.ino"
#endif

#ifdef FOMO
/* Includes ---------------------------------------------------------------- */
#include <Wally_handsignTest_multipleObjects_inferencing.h>

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr);
void setup();
void loop();
#line 26 "/home/kultul/Code_workspace/Particle_Io/Wally_FOMOML/src/Wally_FOMOML.ino"
static const float features[] = {};

/**
 * @brief      Copy raw feature data in out_ptr
 *             Function called by inference library
 *
 * @param[in]  offset   The offset
 * @param[in]  length   The length
 * @param      out_ptr  The out pointer
 *
 * @return     0
 */
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}
#endif


int tmp_buf = 0;

void receiveEvent(int howMany) {
    //Features sendt float * 10000. Needs to be divided by 10000
    while(Wire.available())
    {
        tmp_buf = Wire.read();
        Serial.println("Feature from master:");    
        Serial.print(tmp_buf);
        Serial.println();

    }

}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);

    Serial.println("Test of Transporting img data from Arduino to Argon, via I2C");

    Serial.println();

    Wire.begin(8);
    Wire.onReceive(receiveEvent);
}



// I2C TEST
void loop(){
}


#ifdef FOMO
void loop()
{

    ei_printf("Edge Impulse standalone inferencing (Arduino)\n");

    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
            EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
        delay(1000);
        return;
    }

    ei_impulse_result_t result = { 0 };

    // the features are stored into flash, and we don't want to load everything into RAM
    signal_t features_signal;
    features_signal.total_length = sizeof(features) / sizeof(features[0]);
    features_signal.get_data = &raw_feature_get_data;

    // invoke the impulse
    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
    ei_printf("run_classifier returned: %d\n", res);

    if (res != 0) return;

    // print the predictions
    ei_printf("Predictions ");
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
        result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    ei_printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("%.5f", result.classification[ix].value);
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf(", ");
#else
        if (ix != EI_CLASSIFIER_LABEL_COUNT - 1) {
            ei_printf(", ");
        }
#endif
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("%.3f", result.anomaly);
#endif
    ei_printf("]\n");

    // human-readable predictions
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif

    delay(1000);

}

#endif