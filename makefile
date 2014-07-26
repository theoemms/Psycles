CC = g++
CFLAGS = -lGL -lGLU -lglut
CFLAGSMAC = -framework Carbon -framework GLUT -framework OpenGL
SOURCES = Drawable.cpp Updatable.cpp Game.cpp Vector3.cpp Light.cpp Camera.cpp KeyboardEvent.cpp main.cpp
DEPENDENCIES = Globals.h Drawable.h Updatable.h Game.h Vector3.h Light.h Camera.h KeyboardEvent.h
EXEC_NAME32 = bin/x86/psycles
EXEC_NAME64 = bin/x64/psycles
EXEC_NAMEMAC = bin/osx/psycles

main : $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC_NAME64)

x86 : $(SOURCES) $(DEPENDENCIES)
	$(CC) -m32 $(CFLAGS) $(SOURCES) -o $(EXEC_NAME32)

mac:  $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGSMAC) $(SOURCES) -o $(EXEC_NAMEMAC)

all : main x86

clean :
	rm main


