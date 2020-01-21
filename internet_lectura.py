from urllib.parse import urlencode
from urllib.request import Request, urlopen
import requests
import time

respuno= 'http://sensoresonlinesandro.herokuapp.com/respuno'

practis = Request(respuno)

while True:
    lectura = urlopen(practis).read().decode()
    print(lectura)
    time.sleep(2)