#!/usr/bin/python

import sys
import serial

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

byte = int(sys.argv[1])
#b = int(sys.argv[2]))

# Print to serial
# Todo make tty number more robust in case of +1
out = serial.Serial("/dev/ttyACM0", 19200)
print byte
out.write(chr(byte))