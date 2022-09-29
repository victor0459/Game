CXX=g++
CFLAGS=-g -O2 -Wall -fPIC -Wno-deprecated 

INC=-I../../game_reactor/include
LIB=-L../../game_reactor/lib -lreactor -lpthread
OBJS = $(addsuffix .o, $(basename $(wildcard *.cc)))

all:
		        $(CXX) -o c $(CFLAGS)  c.cpp $(INC) $(LIB)
		        $(CXX) -o client $(CFLAGS)  client.cpp $(INC) $(LIB)

clean:
		        -rm -f *.o c client

