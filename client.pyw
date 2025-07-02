import socket
import serial 
import serial.tools.list_ports
import time
import threading
import queue





comport = "COM3" # <----- Your COM port goes here
ip = "127.0.0.1"
udp_port = 6969

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((ip, udp_port))
sock.settimeout(5.0)
print("Listening for UDP packets!")

ser = serial.Serial()
ser.port = comport
ser.baudrate = 115200
ser.setDTR(False)
ser.write_timeout = 1
ser.open()


ack_queue = queue.Queue()

def serial_reader_thread(serial_port, ack_queue):
    while True:
        try:
            if serial_port.in_waiting > 0:
                line = serial_port.readline().decode('utf-8', errors='ignore').strip()
                if line:
                    if line == "OK":
                        ack_queue.put(line)   # enqueue ACK for main thread
                    else:
                        print(f"[SERIAL LOG] {line}")  # print other logs
        except Exception as e:
            print(f"Serial read error: {e}")
            break

def awaitACK(timeout=1):
    try:
        ack = ack_queue.get(timeout=timeout)
        if ack == "OK":
            return True
    except queue.Empty:
        pass
    return False


log_thread = threading.Thread(target=serial_reader_thread, args=(ser, ack_queue), daemon=True)
log_thread.start()

                        


while True:
    try: 
        data, addr = sock.recvfrom(1024)
    except socket.timeout:
          print("UDP socket timeout!")
          continue
    except Exception as e:
          print("UDP Error! " + e)
          continue
    print(f"Received {len(data)} bytes from {addr}")
    rawData = data.decode('utf-8')
    splitData = rawData.split("$")
    speed = int(float(splitData[0][:-1]))
    rpm = int(float(splitData[1][:-1]))
    absStatus = 1 if splitData[2] == "true" else 0
    if (splitData[3] == "0"):
          gear = "N"
    elif (splitData[3] == "-1"):
          gear = "R"
    else:
          gear = splitData[3]
          
    
    fuellvl = int(float(splitData[4][:-1]))
    engine_status = 1 if splitData[5] == "true" else 0
    tclvl = int(splitData[6])
    left_signal = 1 if splitData[7] == "true" else 0 # expect nil as false
    right_signal = 1 if splitData[8] == "true" else 0 # expect nil as false
    hazard_signal = 1 if splitData[9] == "true" else 0 # expect nil as false
    highbeams = 1 if splitData[10] == "true" else 0
    handbrake = 1 if splitData[11] == "1" else 0
    headlight = 1 if splitData[12] == "true" else 0
    # print(splitData[0])
    print(speed, rpm, absStatus, gear, fuellvl, engine_status, tclvl, left_signal, right_signal, hazard_signal, highbeams, handbrake, headlight)
    # print("Serial Intake: " + ser.read())
    
    sendStr = str(speed) + "-" + str(rpm) + "-"  + str(absStatus) + "-" + str(gear) + "-" + str(fuellvl) + "-" + str(engine_status) + "-" + str(tclvl) + "-" + str(time.localtime().tm_hour) + "-" + str(time.localtime().tm_min) + "-" + str(left_signal) + "-" + str(right_signal) + "-" + str(hazard_signal) + "-" + str(highbeams) + "-" + str(handbrake) + "-" + str(headlight) + "-&"
    bytesofSendStr = sendStr.encode()
    try:
        ser.write(bytesofSendStr)
    except serial.SerialTimeoutException:
          print("Serial write timed out :(((((")
    except serial.SerialException as e:
          print("Serial Error: " + e)
    ser.flush()
    if not awaitACK(timeout=1):
        print("No acknowledgement received, stopping...")
        break
