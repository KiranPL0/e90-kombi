import serial 
import serial.tools.list_ports

print("Locating COM ports....")
ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))
input("Press [enter] to exit...")