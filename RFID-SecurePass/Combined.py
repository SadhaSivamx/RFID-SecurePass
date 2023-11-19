import serial
import datetime
from RecognizeFace import PredictFace
from Capture import  Capturee

def Wre(name):
    # File name
    file_name = "log.txt"
    # Data to append
    dt=str(datetime.datetime.now())
    data_to_append = f"Person : {name} at {dt}\n"

    # Open the file in append mode ('a' for append)
    with open(file_name, 'a') as file:
        # Write the data to the file
        file.write(data_to_append)

    print("Data appended to", file_name)

# Establish serial communication with Arduino
arduino = serial.Serial('COM8', 9600)

while True:
    if arduino.in_waiting > 0:
        data = arduino.readline().decode().strip()  # Read the data from Arduino
        data=data.split()
        if 'access' in data:
            print("Letting In...")
            Capturee()
            Wre(PredictFace())
        elif 'denied' in data:
            print("Denied Access...")