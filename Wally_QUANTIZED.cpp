/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include "Particle.h"
#include "Arduino.h"
#include "Wire.h"
#include <Wally_handsignTest_multipleObjects_inferencing.h>

/* Defines ---------------------------------------------------------------- */
#define SIFEA 2304 //Size of Feature Array

/* Global ---------------------------------------------------------------- */
int8_t g_Feature_buf[SIFEA] = {0}; 
uint16_t g_Buf_ix = 0;
bool end_flag = false;
bool m_flag = false;
int bytes_rec = 0;

/**
 * @brief Handler for webhook respons
 * 
 * @param[in] event Name of event 
 * @param[in] data  Data contained in respons
 */
void myHandler(const char *event, const char *data) {
    float temp = atof(data) - 32; //Convert from Fahrenheit to Celsius
    ei_printf("%.2f Celsius in Copenhagen \n",temp);
}

/**
 * @brief Event to be triggered when Master sends data via I2C
 * 
 * @param[in] howMany Amount of bytes received
 */
void receiveEvent(int howMany) {
    m_flag = true;
    bytes_rec = howMany;
    return;
}

/**
 * @brief      Argon setup function
 */
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo");
    Particle.subscribe("hook-response/local_temp", myHandler, MY_DEVICES);
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
}

/**
 * @brief   Argon main function
 * @def     Handles I2C communication and processing of quantized features.
 *          
 */
void loop()
{
    if(m_flag){
        while(Wire.available())
        {
            if(bytes_rec == 2){
                end_flag = true;
                break;
            }
            /*
            byte_counter++;
            uint8_t s_receive = Wire.read();
            if(s_receive == 100) s_receive = 0; // Instead of 0, which cant be handle by wire.write, we receive 100.
            feature = (feature + s_receive) / 100;
            if(byte_counter==2){
                g_Feature_buf[g_Buf_ix] = feature;
                g_Buf_ix += 1;
                byte_counter=0;
                feature = 0.0;
            }
            */
            int8_t s_receive = Wire.read();
            if(s_receive == 100) s_receive = 0; // Instead of 0, which cant be handle by Wire.write, we receive 100.
            g_Feature_buf[g_Buf_ix] = s_receive;
            g_Buf_ix += 1;
            
        }
        m_flag=false;
    }
    if(end_flag){
    /*Run inferencing only, no DSP ********************************************************/
    ei_impulse_result_t result = { 0 };
#if EI_CLASSIFIER_STUDIO_VERSION < 3
        const ei_impulse_t impulse = ei_construct_impulse();
#else
       const ei_impulse_t impulse = ei_default_impulse;
#endif
/*
    ei::matrix_i8_t features_matrix(1, impulse.nn_input_frame_size);
    
    if ((memcpy(features_matrix.buffer,g_Feature_buf,SIFEA*sizeof(float)))==NULL){
        ei_printf("Error accured during memccpy");
        ei_printf("\n");
    }
*/
    
    EI_IMPULSE_ERROR init_res = run_nn_inference_image_quantized(&impulse, g_Feature_buf, SIFEA, &result, true);
    if (init_res != EI_IMPULSE_OK) {
        ei_printf("ERROR accured during inferencing: %d", init_res);
        return;
    }

/***********************************************************************************************/

    // print the predictions
    ei_printf("(Classification: %d ms.)",result.timing.classification);
    ei_printf(": \n");
    
    #if EI_CLASSIFIER_OBJECT_DETECTION == 1
    bool bb_found = result.bounding_boxes[0].value > 0;
    for (size_t ix = 0; ix < result.bounding_boxes_count; ix++) {
        auto bb = result.bounding_boxes[ix];
        if (bb.value == 0) {
            continue;
        }
        int value = *bb.label;
        char label = *bb.label;
        if (value > 95){
            switch(label){
                case 'a':
                Particle.publish("local_temp");
                Serial.println(value);
                Serial.println();
                Serial.println(label);
                break;

                default:
                break;
            }

        }
    }

    if (!bb_found) {
        ei_printf("No objects found\n");
    }
#else
    ei_printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("%.5f", result.classification[ix].value);}
#endif
    //Make ready for new detection
    end_flag=false;
    g_Buf_ix = 0;
    memset(g_Feature_buf,0,sizeof(g_Feature_buf));
    }
}
