from adafruit_circuitplayground import cp
import time

# Button A slows things down
# Button B speeds them up
# Tiny switch is for off/on

cp.pixels.brightness = 0.5
cp.pixels.fill((0, 0, 0))  # Turn off the NeoPixels if they're on!

# has 10 pixels
NUM_PIXELS = 10
HALF_PIXELS = 5

index = 0

tick_time = 0.01
wait_ticks = 5
ticks = 0

# colors
BLACK = 0x000000
RED =   0xFF0000
RED2 =  0x550000
BLUE =  0x0000FF
BLUE2 = 0x000055

# previous pixel index
def pp_offset(index, offset=-1):
    return (index + offset) % NUM_PIXELS

def poll_lights(index):
    cp.pixels[pp_offset(index, -2)] = BLACK
    cp.pixels[pp_offset(index, -1)] = RED2
    cp.pixels[index] = RED
    cp.pixels[pp_offset(index, 1)] = RED2

    opposite = pp_offset(index, HALF_PIXELS)
    cp.pixels[pp_offset(opposite, -2)] = BLACK
    cp.pixels[pp_offset(opposite, -1)] = BLUE2
    cp.pixels[opposite] = BLUE
    cp.pixels[pp_offset(opposite, 1)] = BLUE2

while True:
    if not cp.switch:
        cp.pixels.fill((0, 0, 0))
        time.sleep(0.1)
        continue

    if cp.button_a:
        wait_ticks += 1
    
    if cp.button_b:
        wait_ticks = max(0, wait_ticks - 1)

    if ticks > wait_ticks:
        poll_lights(index)
        if index == NUM_PIXELS - 1:
            index = 0
        else:
            index += 1
        ticks = 0

    ticks += 1
    time.sleep(tick_time)


