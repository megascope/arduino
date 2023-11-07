CC=g++
CFLAGS=-std=c++14 -I emulator
ODIR=obj
LIBS=-lm 

DEPS = characters.h defines.h emulator/Arduino.h emulator/FastLED.h

_OBJ = characters.o test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
