#!/bin/bash
# neopixel library must run as root

source .venv/bin/activate
sudo $(printenv VIRTUAL_ENV)/bin/python3 "$@"
