# Wally
> A tiny helper
> https://www.kaggle.com/code/sayakdasgupta/sign-language-classification-cnn-99-40-accuracy
> 

## Table of Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Requirements](#requirements)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Acknowledgements](#acknowledgements)
* [Contact](#contact)
<!-- * [License](#license) -->


## General Information
- The project propose an different approch to smart homes. Instead of using voice commands to get different kinds of information via a traditional smart-home device, like Alexy or Google Home, Wally will use sign language to determine the user request. 
- The reason for this is to inable people with the mute dissability to also have access to an smart home device, and that image processing would be more reliable than audio since bagground noice, such as other people or tv, would not have an effect. The only noice factor would be the light level.
<!-- You don't have to answer all the questions - just the ones relevant to your project. -->


## Technologies Used
Microprocessor: Particle Argon, Arduino Nano BLE 33
IDE: Visual Studio Code
Intern MCU communication: I2C

## Features
Sending 'c' via a serial monitor, like putty, to Arduino will cause it to read a frame from OV7675.
Arduino generates only features via Edge Impulses DPS library, no classification as there is not enough space for both classification model and DSP model.
Arduino sits as Master on I2C, to be able to talk to OV7675 camera, and sends the generatet features to Argon.
	

## Requirements
Tiny ML Kit from Arduino & Edge Impulse
Particle Argon MCU

### Camera
Minimum distance for correct image recognition: 1.5 m.
Pixel resolution: 343 pixels.
Low power design.
Should be able to detec objects moving 1.5 m/s, based on average walking speed for a person between 20-30.
### MCU 
Low power design.
When no object movement have been detected, should enter low power mode.
Has to be able to run a Machine learning algorithme for image classification. Images will be live stream
Response time from low power to finishing image classification: <20 sec

## Setup

## Usage
How does one go about using it?
Provide various use cases and code examples here.

`write-your-code-here`


## Project Status
Project is: _in_definement

## Acknowledgements


## Contact
Created by [@dkhusted] - feel free to contact me!


<!-- Optional -->
<!-- ## License -->
<!-- This project is open source and available under the [... License](). -->

<!-- You don't have to include all sections - just the one's relevant to your project -->
