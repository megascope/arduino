#!env python3

from pathlib import Path
import argparse
from PIL import Image

def main():
    parser = argparse.ArgumentParser(
                    prog='bmp2xbm',
                    description='convert bmp to xbm files')
    
    parser.add_argument('filename')
    parser.add_argument('-i', '--invert', action='store_true', help='invert image output')


    args = parser.parse_args()

    im = Image.open(args.filename)
    print("Opened {} with size {}".format(args.filename, im.size))

    xbmout(Path(args.filename).stem, im, args.invert)

def xbmout(name, image, invert):
    print('// header file')
    print('static const XBM {};'.format(name))
    print()

    w = image.size[0]
    h = image.size[1]
    print('// cpp file')

    # 1 byte each 8 pixels
    row_bytes = int(w/8)+1
    elements = []
    print('/*')
    for y in range(0, h):
        element = 0
        count = 0
        for x in range(0, w):
            pixel = image.getpixel((x,y))
            if (pixel == 0) == invert:
                element |= (1 << count)
                print('█',end='')
            else:
                print('░',end='')

            count += 1
            if count == 8:
                count = 0
                elements.append(element)
                element = 0
        
        if count > 0:
            elements.append(element)
            element = 0

        print()
            #print('{}/{}={}'.format(x,y, image.getpixel((x,y))), end='')

    # make sure have right number of items    
    assert(len(elements) == row_bytes * h)
    print('*/')
    print('const DataByte PROGMEM {}_xbm[] = {{'.format(name))

    count = 0
    for element in elements:
        print('0x{:02x}'.format(element), end='')
        count += 1
        if count == len(elements):
            print('};')
        elif count % row_bytes == 0:
            print(',')
        else:
            print(',', end='')

    print('const XBM XBM::{}({}, {}, {}_xbm);'.format(
        name, w, h, name))
if __name__ == '__main__':
    main()


