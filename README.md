# OverKillBMS_ESPHome
Monitor your OverKill/JDB BMS with ESPHome. Exposes all the information from the BMS over MQTT. 
![1280-960-max-2](https://user-images.githubusercontent.com/107140997/177014934-49a9e192-bbda-47c8-b75a-70feade2163c.jpg)


# PCB
This PCB uses a basic logic level converter and micro DC-DC converter to interface the ESP32-DEVKITC-32D directly into the Bluetooth interface connector. EasyEDA/JLPCB will build the PCB including populating all the surface mount parts and even the cable connector. Gerber, BOM and Pick and Place files are in the PCB directory. The DC-DC converter and pin headers will have to be soldered by hand. 

# ESP32 
The PCB is designed to work with the ESP32-DEVKITC-32D. Digikey #1965-1000-ND and Mouser #356-ESP32-DEVKITC32D. It may work with others, but the dev kits have different pin spacing with some being a pin narrower.  

![PCB-v2](https://user-images.githubusercontent.com/107140997/177014873-3f73d354-1657-48e8-abae-97be63967e65.png)
![1280-960-max](https://user-images.githubusercontent.com/107140997/177014937-dcf19b92-7592-4c85-89b6-e7d1e986cb05.jpg)



# PCB LEDs
Several multi-color LEDs are provided on the PCB. The configuration is customization in the yaml file, but the default is below. 

- Green: Discharge FET on
- Yellow: Charge FET on
- Blue: Low temp protection on
- Red: Anything in an error or not normal state. 


# ESPHome code
The code basically a combination of the ESPHome, and the https://github.com/FurTrader/Overkill-Solar-BMS_2-Arduino-Library library. The BMS library is basically unchanged with the exception of a few type formatting corrections that the ESP32 requires. 

At the moment, this is read only. No configuration changes can be made, but the code is there in the Arduino library for basic control. 

# Example ESPHome information
![MQTT-Explorer](https://user-images.githubusercontent.com/107140997/177014871-44cc665a-d3e5-41db-851b-066be5fb917b.png)



# Configuration 
See overkill_batt1.yml for an example. 
- Change the Wifi and MQTT information to suite. 
- Note that sending all the debug information to syslog is included, but that section can be commented out if not used.
- Change the Libraries section needs to point to the full path of the overkilllib2 folder.
- The name of the BMS and how it appears in MQTT is configured under name:. The default is overkill-batt1. 

# Installing (Assumes you have ESPHome already installed)
1. Download this repo into a folder. 
2. Copy and modify the overkill_batt1.yml example file.
3. Connect up the ESP module with a USB cable. It does not matter if it is connected to the BMS or not. 
4. Type “ESPHome run overkill_batt1.yml”. ESPHome should compile the code and upload it to the ESP32 module. 


# Note on Battery Voltage (12V, untested on 24V). 
The BMS outputs battery voltage on the VBAT+ pin. The DC-DC converter (R-78HE5.0-0.3) on the PCB steps this down to the 5V the ESP32 chip needs. The ESP32 chip is quite power hungry and at 12V battery voltage, the current from the interface port of the BMS is not sufficient to power the ESP32 chip.
This is not an issue with a 48V battery system. It is untested on a 24V battery.  

For a 12V battery bank, the VBAT+ wire from the BMS to the PCB can be cut, and connected directly to the battery positive terminal with a 500ma fuse, so that the PCB gets direct battery voltage. The two communication and ground wires will still be connected to the BMS. **Note: The wire colors on the OverKill provided BMS to Bluetooth cable may be reversed depending on what end you have plugged in to what. Look at the labels on the PCB and the BMS to find the VBAT+ wire. Don’t assume it is the red wire.**











 


