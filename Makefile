# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date

build: clean build/main.o
	$(CC) $(CFLAGS) -o rccar build/main.o -lbluetooth -levdev -lpigpio
 
# The main.o target can be written more simply
 
build/main.o: src/main.cpp src/Drive.h 
	$(CC) $(CFLAGS) -c src/main.cpp -lbluetooth -levdev -lpigpio -o build/main.o

clean: 
	rm -rf build/*
	rm -f rccar