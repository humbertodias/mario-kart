CC		= g++
CFLAGS	= -c -Wall -pipe -g -W -O2
INC	= $(shell pkg-config --cflags allegro-5 allegro_image-5)
LIB	= $(shell pkg-config --libs allegro-5 allegro_image-5)

all: 
	$(CC) $(CFLAGS) *.cpp $(INC) $(LIB)

clean:
	rm -f *.o