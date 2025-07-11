# BMW E9X (330i KOMBI)

This repository is for connecting your BMW E92 (or any other E9X variant) instrument cluster with Assetto Corsa via an Arduino

## Requirements

Assetto Corsa
BMW E9X Instrument Cluster (E92 330i Preferred)
Seed Canbus Shield V2
Arduino UNO
USB A -> USB B Cable
Cables (to connect)
2.2kΩ NTC Thermosistor or 3.5 kΩ - 2 kΩ Resistor (To Surpress Ice Warning On Ignition)
Visual Studio Code
PlatformIO
Python

## Setup & Installation

Connect your CAN Cables to the cluster like this...
![connect can-hi and can-lo
](https://europe1.discourse-cdn.com/arduino/original/4X/0/a/d/0adcfa0b3805bf037b1e4c1fd241c35ea7792bcb.jpeg)
Use a 12V power supply for the Instrument Cluster's power.
I reccomend using a relay to easily switch on/off the cluster with your arduino. (Connect Digital Pin 2 to your switch from the Arduino for a 5V signal to the relay's middle pin to trigger from a switch)

You'll need to use PlatformIO to upload code to your Arduino.
Search for it in the VS Code Extension Store, open it up, and load this repository.
After that, there should be an arrow on the bottom bar of VS Code, click that to upload it to your arduino.

## Usage

Firstly, plug your Arduino in to your computer.
In your Assetto Corsa root folder, open apps/lua and place the signal_transponder folder located in the app folder in this repositry into the lua folder in Assetto Corsa - This is to install the lua telemetry app.

Next, ensure python is downloaded and create a folder to place portfinder.py and client.pyw on your computer.

Open command prompt in the folder and run
`pip install pyserial`

Then, run portfinder.py to locate the port of your Arduino, and open client.pyw in notepad.

In client.pyw, replace `COM3` with your COM port.

```py
comport =  "COM3"  # <----- Your COM port goes here
```

You can then save and close the file.

Run client.pyw and start Assetto Corsa up.

Once you press drive and your engine is on, your cluster should spring to life!

From then on, every time you restart your computer, run client.pyw and start Assetto Corsa up to use the cluster.

## Features

- Assetto Corsa Turn Signal Support
- Speedometer
- Tachometer
- Working Clock (Represents Real Time)
- Fuel Gauge
- Transmission Functionality (Reverse, Neutral, or Current Gear)
- High Beams + Headlights Functionality
- Handbrake
- Custom Telemetry Software

## Data Pipeline

Telemetry Data follows a "pipeline" as it makes it's way to the Arduino.<br>
**Assetto Corsa App (Lua App)** --- UDP ⮕ **Python Script** --- Serial ⮕ **Arduino** --- Canbus ⮕ **Instrument Cluster**

Data is collected through the Assetto Corsa Lua app, and is then sent as UDP packets to the python script via localhost.
It's then sent via serial to the Arduino, where it's data is parsed and sent as canbus packets.

## Credits

[e90-dashboard-ets2](https://github.com/Marcin648/e90-dashboard-ets2) --- used for speed, rpm and counter frames<br>
[BMW Canbus Codes](https://www.loopybunny.co.uk/CarPC/k_can.html) --- used for most can codes<br>
[Controlling BMW E90 Instrument Cluster](https://forum.arduino.cc/t/controlling-bmw-e90-instrument-cluster/670728) --- used for wiring diagram + general wiring information<br>
[opendbc-BMW-E8x-E9x](https://github.com/dzid26/opendbc-BMW-E8x-E9x) --- used for dbc file which was used for certain can commands such as transmission<br>
[Assetto Corsa Lua SDK](https://github.com/ac-custom-shaders-patch/acc-lua-sdk) --- used for lua app
