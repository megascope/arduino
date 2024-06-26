import time
import board
import neopixel
import signal

# Choose an open pin connected to the Data In of the NeoPixel strip, i.e. board.D18
# NeoPixels must be connected to D10, D12, D18 or D21 to work.
pixel_pin = board.D18

# The number of NeoPixels
num_pixels = 100

# The order of the pixel colors - RGB or GRB. Some NeoPixels have red and green reversed!
# For RGBW NeoPixels, simply change the ORDER to RGBW or GRBW.
ORDER = neopixel.GRB

def cleanup():
    print("Clearing pixels...")
    for i in range(0, num_pixels):
        pixels[i] = (0,0,0)

    pixels.show()

def signal_handler(sig, frame):
    print("Caught", sig)
    # Your cleanup code here
    cleanup()
    exit(0)

signal.signal(signal.SIGINT, signal_handler)

pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.2, auto_write=False, pixel_order=ORDER
)
