#Libraries
import RPi.GPIO as IO
import bluetooth
from time import sleep
from time import time

bd_addr = "20:16:07:25:79:41"
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))
#IO Mode (BOARD / BCM)
IO.setmode(IO.BCM)
#set IO Pins
trigR = 18
trigM = 15
trigL = 14
echoR = 23
echoM = 24
echoL = 25
threshold1 = 200
threshold2 = 100
threshold3 = 70
threshold4 = 30
#set IO direction (IN / OUT)
IO.setup(trigR, IO.OUT)
IO.setup(trigM, IO.OUT)
IO.setup(trigL, IO.OUT)

IO.setup(echoR, IO.IN)
IO.setup(echoM, IO.IN)
IO.setup(echoL, IO.IN)
def distance():
    
    #                                           RIGHT RIGHT RIGHT RIGHT
    # set Trigger to HIGH
    IO.output(trigR, True)
    # set Trigger after 0.01ms to LOW
    sleep(0.00001)
    IO.output(trigR, False)
    StartTime = time()
    StopTime = time()
    # save StartTime
    while IO.input(echoR) == 0:
        StartTime = time()
    # save time of arrival
    while IO.input(echoR) == 1:
        StopTime = time() 
    # time difference between start and arrival
    TimeElapsedR = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distR= int((TimeElapsedR * 34300) / 2)
    print("distR: " + str(distR))
    
    
    
    #                                           MID MID MID MID
    # set Trigger to HIGH
    IO.output(trigM, True)
    # set Trigger after 0.01ms to LOW
    sleep(0.00001)
    IO.output(trigM, False)
    StartTime = time()
    StopTime = time()
    # save StartTime
    while IO.input(echoM) == 0:
        StartTime = time()
    # save time of arrival
    while IO.input(echoM) == 1:
        StopTime = time() 
    # time difference between start and arrival
    TimeElapsedM = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distM= int((TimeElapsedM * 34300) / 2)
    print("distM: " + str(distM))
    
    
    
    #                                           LEFT LEFT LEFT LEFT
    # set Trigger to HIGH
    IO.output(trigL, True)
    # set Trigger after 0.01ms to LOW
    sleep(0.00001)
    IO.output(trigL, False)
    StartTime = time()
    StopTime = time()
    # save StartTime
    while IO.input(echoL) == 0:
        StartTime = time()
    # save time of arrival
    while IO.input(echoL) == 1:
        StopTime = time() 
    # time difference between start and arrival
    TimeElapsedL = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distL= int((TimeElapsedL * 34300) / 2)
    print("distL: " + str(distL))
    
    
    
    #                                           TRANSMISSION TRANSMISSION
    sent = ""
    if distL>threshold1:
        sent+='0'
    elif distL>threshold2:
        sent+='1'
    elif distL>threshold3:
        sent+='2'
    elif distL<threshold4:
        sent+='3'
        
    if distM>threshold1:
        sent+='0'
    elif distM>threshold2:
        sent+='1'
    elif distM>threshold3:
        sent+='2'
    elif distM<threshold4:
        sent+='3'
        
    if distR>threshold1:
        sent+='0'
    elif distR>threshold2:
        sent+='1'
    elif distR>threshold3:
        sent+='2'
    elif distR<threshold4:
        sent+='3'
        
    
    sent+='\n'
    print(sent)
    return sent
    
    
try:
    while True:
        dist = distance()
        sock.send(dist+"\n")
        sleep(0.1)
        # Reset by pressing CTRL + C
except KeyboardInterrupt:
    print("Measurement stopped by User")
    IO.cleanup()