#!/bin/bash -e

echo "Updating COT application..."
echo "Copying binaries..."
echo "Copying translations..."
cp -f /media/USB/APP_COT/cot /home/seres/
chmod 755 /home/seres/cot
chmod 755 /home/seres/cot-translator
cp -f /media/USB/APP_COT/libcotlib.so.1.0.0 /home/seres/
chmod 755 /home/seres/libcotlib.so.1.0.0
cp -f /media/USB/APP_COT/libmodbus.so.1.0.0 /home/seres/
chmod 755 /home/seres/libmodbus.so.1.0.0
cp -f /media/USB/APP_COT/save.json /home/seres/save_origin.json
cp -f /media/USB/APP_COT/save.json /home/seres/save.json
cp -f /media/USB/APP_COT/trad/* /home/seres/
/home/seres/cot-translator -m import /home/seres/save.json /home/seres/
sync
echo "Done."
