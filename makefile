CC = gcc
CFLAGS = -lGL -lGLU -lglut
SOURCES = Drawable.cpp Updatable.cpp Game.cpp Vector3.cpp Light.cpp Camera.cpp KeyboardEvent.cpp main.cpp
DEPENDENCIES = Globals.h Drawable.h Updatable.h Game.h Vector3.h Light.h Camera.h KeyboardEvent.h
EXEC_NAME32 = bin/x86/psycles
EXEC_NAME64 = bin/x64/psycles

x86 : $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC_NAME32)

x64 : $(SOURCES) $(DEPENDENCIES)
	$(CC) -m64 $(CFLAGS) $(SOURCES) -o $(EXEC_NAME32)

all : x86 x64

clean :
	rm -rf main

