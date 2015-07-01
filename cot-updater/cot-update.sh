#!/bin/bash -e

echo "Updating COT application..."
echo "Copying binaries..."
echo "Copying translations..."
cp -f /media/USB/APP_COT/cot /home/seres/
cp -f /media/USB/APP_COT/libcotlib.so.1.0.0 /home/seres/
cp -f /media/USB/APP_COT/libmodbus.so.1.0.0 /home/seres/
cp -f /media/USB/APP_COT/save.json /home/seres/
echo "Done."
