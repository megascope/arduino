# Circuit Python
Single file code to interact with an Adafruit Circuit Playground Bluefruit (nRF5280)


## Recommended setup
Install Arduino for Visual Studio Code extension.

Serial console will give access to device.

## Setup
To get python intellisense working with VSCode

```

# create virtualenv
python -m venv .venv

# activate
source .venv/bin/activate

# install requirements
pip3 install -r requirements.txt
```

## Usage

Copy the contents of a given file to the device as `code.py` and it should start running automatically.

If an error occurs it will print to the serial console.

For example:
```
code.py output:
Traceback (most recent call last):
  File "code.py", line 38, in <module>
  File "code.py", line 17, in poll_lights
NameError: local variable referenced before assignment
```


