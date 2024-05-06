#!/bin/bash -e
# from https://learn.adafruit.com/neopixels-on-raspberry-pi/python-usage
python3 -m venv .venv
source .venv/bin/activate
echo installing into $VIRTUAL_ENV
python3 -m pip install --upgrade pip
pip3 install -r requirements.txt
python3 -m pip install --force-reinstall adafruit-blinka
