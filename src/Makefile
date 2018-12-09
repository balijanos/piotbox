# RPIOTBOX MAKEFILE
# (C) 2017, Hi-Project Ltd.
# RPI V3 FLAGS

# DEBUG=-DDEBUG
 
CCFLAGS= -mfpu=neon-fp-armv8 -mfloat-abi=hard -march=armv8-a+crc -mtune=cortex-a53 $(DEBUG) -w
CIFLAGS= -I=/usr/include/lua5.2 
CLFLAGS= -lwiringPi -lArduiPi_OLED -lpthread -fstack-protector
LUA_LIBS=$(shell pkg-config --libs lua5.2)

PROGRAM= ../piotbox
COBJS= compat.o rotaryencoder.o luawpi.o
CPPOBJS= luadisplay.o piotbox.o 

CPP= gcc
CXX= g++

all: ${PROGRAM}

${PROGRAM}: $(CPPOBJS) $(COBJS) 
	$(CXX) ${CCFLAGS} $(CIFLAGS) ${LUA_LIBS} -w -Wno-write-strings -o $(PROGRAM) $(COBJS) $(CPPOBJS) ${CLFLAGS} 

clean:
	rm -rf $(PROGRAMS) $(COBJS) $(CPPOBJS)

piotbox.o: piotbox.cpp piotbox.h buttons.h encoders.h
	$(CXX) -c piotbox.cpp -o piotbox.o ${CCFLAGS} $(CIFLAGS)
	
compat.o: compat.c compat.h
	$(CPP) -c compat.c -o compat.o ${CCFLAGS} $(CIFLAGS)
	
luadisplay.o: luadisplay.cpp luadisplay.h 
	$(CXX) -c luadisplay.cpp -o luadisplay.o ${CCFLAGS} $(CIFLAGS) 
 
rotaryencoder.o: rotaryencoder.c
	$(CPP) -c rotaryencoder.c -o rotaryencoder.o ${CCFLAGS} $(CIFLAGS)
	
luawpi.o: luawpi.c
	$(CPP) -c luawpi.c -o luawpi.o ${CCFLAGS} $(CIFLAGS)
