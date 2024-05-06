from base import pixels, num_pixels

r = 255-8
g = 0
b = 0

while True:

    r = (r + 8) % 255
    g = (g + 16) % 255
    b = (b + 24) % 255

    for i in range(0, num_pixels):
        pixels[(i-1) % num_pixels] = (0, 0, 0)
        pixels[i] = (r, g, b)
        pixels.show()
