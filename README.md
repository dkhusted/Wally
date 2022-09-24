# Wally
> A tiny helper
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
Microprocessor: Particle Argon
IDE: Visual Studio Code
Jupyter Notebook with different python libs. See the note book( Wally_CSV_prepper.ipynb) for details

## Features
List the ready features here:

## Requirements
For this project the following requirements have been specified.

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
First i use Wally_CSV_prepper.ipynb to prepare the MNIST CSV file, this includes converting the data to the correct format and reorganizing the data.
Afterwards it is uploaded to the Edge Impulse Ingestion Service, which requires the API and HMAC key from your own project on Edge Impulse. So change these in the notebook.
Then i train a DNN(Deep Neural Network) on the dataset, launch it on the test set, fine tune the settings and finally convert it into a Arduino Library which then gets send to MCU compatible with the library(in my case i used an Particle Argon)
Next i connect an OV7675 camera to the MCU and use an Arduino library to run it. 
Then using the DNN i trained, i will be able to registere handsigns, which will be making webhooks to specified webservices, fx the handsign for "w" could pull the local weather forecast.

## Usage
How does one go about using it?
Provide various use cases and code examples here.

`write-your-code-here`


## Project Status
Project is: _defined
Project is now _progress

## Acknowledgements
Some usefull links:
 https://www.kaggle.com/code/sayakdasgupta/sign-language-classification-cnn-99-40-accuracy

## Contact
Created by [@dkhusted] - feel free to contact me!


<!-- Optional -->
<!-- ## License -->
<!-- This project is open source and available under the [... License](). -->

<!-- You don't have to include all sections - just the one's relevant to your project -->
