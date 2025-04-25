CC		= g++
CFLAGS	= -Wall -pipe -g -W -O2 
LDFLAGS	= $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 allegro_main-5)
SOURCES	= \
	../Common/AllegroSystem.cpp		\
	../Common/AllegroScreen.cpp		\
	../Common/AllegroKeyboard.cpp	\
	../Common/SuperMode7.cpp		\
	../Common/ObjectSize.cpp		\
	../Common/Track.cpp				\
	../Game/Camera.cpp			    \
	TrackEditor.cpp

EXECUTABLE	= editor

all:
	$(CC) main.cpp -o $(EXECUTABLE) $(CFLAGS) -I. -I../Game -I../Common $(SOURCES) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)