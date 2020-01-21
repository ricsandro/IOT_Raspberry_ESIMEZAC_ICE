import os
import glob
import time
from urllib.parse import urlencode
from urllib.request import Request, urlopen
import requests
import serial
import sys
rx=0
act='T'

url = 'http://sensoresonlinesandro.herokuapp.com/catch' # Set destination URL here
respuno= 'http://sensoresonlinesandro.herokuapp.com/respdos'
data = {'serial': 's2','name':'E.Hall','valor':rx,'actuador':act}     # Set POST fields here
request = Request(url, urlencode(data).encode())

practis = Request(respuno)


ser= serial.Serial(port='/dev/ttyUSB0',
#ser= serial.Serial(port='/dev/ttyACM0',
                   baudrate=9600,
                   parity=serial.PARITY_NONE,
                   stopbits=serial.STOPBITS_ONE,
                   bytesize=serial.EIGHTBITS,
                   timeout=1
                   )


def send():
    data = {'serial': 's2','name':'E.Hall','valor':rx,'actuador':act}     # Set POST fields here    
    request = Request(url, urlencode(data).encode())    
    json = urlopen(request).read().decode()    
def rea():
    lectura = urlopen(practis).read().decode()
    print(lectura)
    

lectura='1'    
while True:
    rea()
    time.sleep(2)
    ser.write(lectura.encode('ascii'))    
    try:
        rx=ser.readline()
        rx=rx.decode("utf-8","strict")
        rx=int(rx)
        rx=(rx*100/1023)
        rx=int(rx)
        print('El valor leido del sensor es')
        print(rx)
        if(rx>60):
            act='t';
        else:
            act='f'
        send()
    except KeyboardInterrupt:  # Keyboard CTRL c, Shut down serial and close
        ser.close()
        sys.exit(1)
        
    except:
        print('sin datos')