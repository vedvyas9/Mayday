import RPi.GPIO as GPIO #import Raspberry Pi GPIO library
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time


cred = credentials.Certificate(r'''/home/pi/Desktop/mayday-saddy-firebase-adminsdk-jjbng-bd4e2e4263.json''')
firebase_admin.initialize_app(cred, {
    'databaseURL' : 'https://mayday-saddy.firebaseio.com/'
})
ref = db.reference()
users_ref = ref.child('Button')


def button_callback1(channel):
    ref = db.reference()
    users_ref = ref.child('Button')
    users_ref.update({'Button1': 1})
    print("A")
    users_ref.update({'Button1': 0}) 


def button_callback2(channel):
    ref = db.reference()
    users_ref = ref.child('Button')
    users_ref.update({'Button2': 1})
    print("B")
    users_ref.update({'Button2': 0})


def button_callback3(channel):
    ref = db.reference()
    users_ref = ref.child('Button')
    users_ref.update({'Button3': 1})
    print("C")
    users_ref.update({'Button3': 0})

def button_callback4(channel):
    ref = db.reference()
    users_ref = ref.child('Button')
    users_ref.update({'Button4': 1})
    print("D")
    users_ref.update({'Button4': 0})
    


GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(31, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.setup(33, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(35, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(37, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


GPIO.add_event_detect(31,GPIO.RISING,callback=button_callback1)# Setup event on pin 10 rising edge
GPIO.add_event_detect(33,GPIO.RISING,callback=button_callback2)
GPIO.add_event_detect(35,GPIO.RISING,callback=button_callback3)
GPIO.add_event_detect(37,GPIO.RISING,callback=button_callback4)


SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

# photoresistor connected to adc #0
photo_ch = 0

#port init
def init():
         GPIO.setwarnings(False)
         GPIO.cleanup()			#clean up at the end of your script
         GPIO.setmode(GPIO.BCM)		#to specify whilch pin numbering system
         # set up the SPI interface pins
         GPIO.setup(SPIMOSI, GPIO.OUT)
         GPIO.setup(SPIMISO, GPIO.IN)
         GPIO.setup(SPICLK, GPIO.OUT)
         GPIO.setup(SPICS, GPIO.OUT)
         
#read SPI data from MCP3008(or MCP3204) chip,8 possible adc's (0 thru 7)
def readadc(adcnum, clockpin, mosipin, misopin, cspin):
        if ((adcnum > 7) or (adcnum < 0)):
                return -1
        GPIO.output(cspin, True)	

        GPIO.output(clockpin, False)  # start clock low
        GPIO.output(cspin, False)     # bring CS low

        commandout = adcnum
        commandout |= 0x18  # start bit + single-ended bit
        commandout <<= 3    # we only need to send 5 bits here
        for i in range(5):
                if (commandout & 0x80):
                        GPIO.output(mosipin, True)
                else:
                        GPIO.output(mosipin, False)
                commandout <<= 1
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)

        adcout = 0
        # read in one empty bit, one null bit and 10 ADC bits
        for i in range(12):
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)
                adcout <<= 1
                if (GPIO.input(misopin)):
                        adcout |= 0x1

        GPIO.output(cspin, True)
        
        adcout >>= 1       # first bit is 'null' so drop it
        return adcout

def main():
         init()
         time.sleep(1)
         print("will start detect water level\n")
         while True:
                  adc_value=readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
                  if adc_value == 0:
                           print("no water\n")
						   ref = db.reference()
							users_ref = ref.child('Button')
							users_ref.update({'Waterlevel': 0})
                  elif adc_value>0 and adc_value<20 :
                           print("it is raindrop\n")
						   ref = db.reference()
							users_ref = ref.child('Button')
							users_ref.update({'Waterlevel': 5})
                  elif adc_value>=25 and adc_value<250 :
                           print("it is water flow")
                           print("water level:"+str("%.1f"%(adc_value/200.*100))+"%\n")
						   ref = db.reference()
							users_ref = ref.child('Button')
							users_ref.update({'Waterlevel': 10})
                  #print "adc_value= " +str(adc_value)+"\n"
				  
                  time.sleep(1)
        

if __name__ == '__main__':
         try:
                  main()
                 
         except KeyboardInterrupt:
                  pass


message = input("Press enter to quit") # Run until someone presses enter

print ('SUCCESS')




GPIO.cleanup() # Clean up
