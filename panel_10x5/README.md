# Setup

Take a 50 count string of WS2811 lights and put them in a serpentine layout like so:

```
x--x--x--x--x--x--x--x--x--x
                           |
x--x--x--x--x--x--x--x--x--x
|
x--x--x--x--x--x--x--x--x--x
                           |
x--x--x--x--x--x--x--x--x--x
|
x--x--x--x--x--x--x--x--x--x
```

Giving you a 10x5 LED panel

# Mock/Emulation

This project contains a console based FastLED emulator in the `../emulator` folder to speed up development and testing of writing to the panel, instead of having to upload to an arduino each time.

To use just run `make` (assuming you have g++ / clang installed) and then run `build/emulator/test`

# Images
In the `bmp2xbm` folder is a python script to convert bmp files into the XBM format. This can be copied into `images.h` / `images.cpp`
