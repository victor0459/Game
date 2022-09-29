TARGET=./bin/server
CXX=g++
CFLAGS=-g -O2 -Wall -fPIC -Wno-deprecated 

#INC=-I./include -I$(LARS_REACTOR_H)
#LIB=-L../game_reactor/lib -lreactor -lpthread
#OBJS = $(addsuffix .o, $(basename $(wildcard *.cc)))

LARS_REACTOR=../game_reactor
LARS_REACTOR_H =$(LARS_REACTOR)/include
LARS_REACTOR_LIB=$(LARS_REACTOR)/lib  -lreactor

INC=-I./include -I$(LARS_REACTOR_H)

OTHER_LIB = -lpthread -ldl
LIB=  -L$(LARS_REACTOR_LIB) $(OTHER_LIB)
SRC= ./src
OBJS = $(addsuffix .o, $(basename $(wildcard $(SRC)/*.cpp)))

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) $(INC) $(LIB)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(INC)
clean:
		        -rm -f src/*.o $(TARGET)

