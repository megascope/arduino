#!/usr/bin/env python3
# Create mapping for 10x10 panel which has a switchback led layout

a = 0
b = 99

# output {"map":[0,2,1,3]}
leds = []

a = 49
b = 50
for r in range(0, 10):
    row = []

    # row 0: 50, 49, 51, 48, 52, 47, 53, 46, 54, 45,
    # row 1: 40, 59, 41, 58, 42, 57, 43, 56, 44, 55,

    if r % 2 == 0:
        for c in range(0, 5):
            row.append(b)
            row.append(a)
            a -= 1
            b += 1
        a -= 4
        b += 4
    else:
        for c in range(0, 5):
            row.append(a)
            row.append(b)
            a += 1
            b -= 1
        a -= 6
        b += 6

    leds.append(','.join(str(l) for l in row))


print("""{{"n":"10x10 switchback"
,"width":10
,"height":10
,"map":[{}]}}""".format(',\n'.join(str(l) for l in leds)))
