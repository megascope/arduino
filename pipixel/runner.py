from base import pixels, num_pixels, cleanup
import time

def animate():

    r = 255-8
    g = 0
    b = 0
    ticks = 0
    max = 1000

    while True:

        r = (r + 8) % 255
        g = (g + 16) % 255
        b = (b + 24) % 255

        for i in range(0, num_pixels):
            pixels[(i-1) % num_pixels] = (0, 0, 0)
            pixels[i] = (r, g, b)
            pixels.show()
            ticks += 1
            if ticks > max:
                return
            time.sleep(0.05)

if __name__ == "__main__":
    print ("Starting pixels...")
    animate()
    cleanup()
