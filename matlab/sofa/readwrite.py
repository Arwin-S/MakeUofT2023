import serial

ser = serial.Serial('/dev/ttyACM0',9600)

while True:
    read_serial=ser.readline()
    s = str((ser.readline(),30))
    print(s)

