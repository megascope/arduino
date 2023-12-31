# Circuit Playground NeoPixel
import time
import board
import neopixel

NUMPIXELS = 10

pixels = neopixel.NeoPixel(board.NEOPIXEL,
            NUMPIXELS, brightness=0.1, auto_write=False)

# choose which demos to play
# 1 means play, 0 means don't!
color_chase_demo = 0
flash_demo = 0
rainbow_demo = 1
rainbow_cycle_demo = 0


def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 0 or pos > 255:
        return (0, 0, 0)
    if pos < 85:
        return (255 - pos * 3, pos * 3, 0)
    if pos < 170:
        pos -= 85
        return (0, 255 - pos * 3, pos * 3)
    pos -= 170
    return (pos * 3, 0, 255 - pos * 3)


def color_chase(color, wait):
    for i in range(10):
        pixels[i] = color
        time.sleep(wait)
        pixels.show()
    time.sleep(0.5)


def rainbow_cycle(wait):
    for j in range(255):
        for i in range(10):
            rc_index = (i * 256 // 10) + j * 5
            pixels[i] = wheel(rc_index & 255)
        pixels.show()
        time.sleep(wait)


def rainbow(wait):
    for j in range(255):
        for i in range(len(pixels)):
            idx = int(i + j)
            pixels[i] = wheel(idx & 255)
        pixels.show()
        time.sleep(wait)


RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
WHITE = (255, 255, 255)
OFF = (0, 0, 0)

class fade():
    def __init__(self, index, current):
        self.current = current
        self.index = index
        self.steps = 0
        self.to = current
        self.diff = [0.0, 0.0, 0.0]
        pixels[self.index] = self.current

    def target(self, to, steps):
        self.to = to
        self.steps = steps
        for i in range(3):
            d = float(self.to[i]) - float(self.current[i])
            self.diff[i] = d/self.steps
            #print(i, d, self.steps, self.diff[i])

    def step(self):
        if self.steps == 0:
            return True
        self.steps -= 1
        if self.steps <= 0:
            self.current = self.to
            pixels[self.index] = self.current
            #print(self.steps, self.to, self.current, "DONE")
            return True
        else:
            self.current = (int(float(self.to[0]) - self.steps * self.diff[0]),
            int(float(self.to[1]) - self.steps * self.diff[1]),
            int(float(self.to[2]) - self.steps * self.diff[2]))
            pixels[self.index] = self.current
            #print(self.steps, self.to, self.current, self.diff)
            return False

fades = []

for i in range(NUMPIXELS):
    fades.append(fade(i, RED))

colors = [BLUE, GREEN, YELLOW, PURPLE, RED]
#colors = [BLUE, RED]
cindex = 0

while True:
    done = False
    for f in fades:
        done = f.step() | done
    pixels.show()
    if done:
        c = colors[cindex]
        cindex = ( cindex + 1 ) % len(colors)
        #print("done", c)
        for f in fades:
            f.target(c, 255)

    time.sleep(0.1)
    continue

    if color_chase_demo:
        color_chase(RED, 0.1)  # Increase the number to slow down the color chase
        color_chase(YELLOW, 0.1)
        color_chase(GREEN, 0.1)
        color_chase(CYAN, 0.1)
        color_chase(BLUE, 0.1)
        color_chase(PURPLE, 0.1)
        color_chase(OFF, 0.1)

    if flash_demo:
        pixels.fill(RED)
        pixels.show()
        # Increase or decrease to change the speed of the solid color change.
        time.sleep(1)
        pixels.fill(GREEN)
        pixels.show()
        time.sleep(1)
        pixels.fill(BLUE)
        pixels.show()
        time.sleep(1)
        pixels.fill(WHITE)
        pixels.show()
        time.sleep(1)

    if rainbow_cycle_demo:
        rainbow_cycle(0.05)  # Increase the number to slow down the rainbow.

    if rainbow_demo:
        rainbow(0.05)  # Increase the number to slow down the rainbow.