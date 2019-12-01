#!/bin/bash
python simple-serial-2-arduino-03.py RT,2
sleep 5
python simple-serial-2-arduino-03.py SP,0,0,0,0,0,0,5000
sleep 5
python simple-serial-2-arduino-03.py GT,60,300,220,4000
sleep 5
python simple-serial-2-arduino-03.py RT,6
sleep 11
python simple-serial-2-arduino-03.py RT,2
sleep 4
echo Done!

