#Made in Capstone Team No.7 , Log

CC = g++
TARGET = _PreGraphModule
OBJECTS = main.o Adjcency_grpah.o Graph.o node.o play.o Statenode.o Moveable.o Minmaxstage.o SelectAlgorithm.o

CPPFLAGS = -I/usr/local/lib
LDFLAGS = -L/usr/local/lib -std=c++11 -g
OPTIONFLAG = -std=c++11 -g
RESOURCESIZE = -Wl,--stack,1073741824,--heap,1073741824
LDLIBS = -lboost_serialization


$(TARGET) : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

main.o : Graph.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c main.cpp $(LDLIBS) $(RESOURCESIZE)

Adjcency_grpah.o : Adjcency_grpah.h Moveable.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c Adjcency_grpah.cpp $(LDLIBS) $(RESOURCESIZE)

Graph.o : Graph.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c Graph.cpp $(LDLIBS) $(RESOURCESIZE)

play.o : play.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c play.cpp $(LDLIBS) $(RESOURCESIZE)

node.o : node.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c node.cpp $(LDLIBS) $(RESOURCESIZE)

Statenode.o : Statenode.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c Statenode.cpp $(LDLIBS) $(RESOURCESIZE)

Moveable.o : Moveable.h
	$(CC) -c Moveable.cpp

Minmaxstage.o : Minmaxstage.h
	$(CC) -c Minmaxstage.cpp

SelectAlgorithm.o : SelectAlgorithm.h Minmaxstage.h
	$(CC) -c SelectAlgorithm.cpp
	
clean :
	rm $(OBJECTS) $(TARGET)

path :
	echo LD_LIBRARY_PATH
	LD_LIBRARY_PATH=/usr/local/lib
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	export LD_LIBRARY_PATH

start :
	./$(TARGET) $(RESOURCESIZE) -j 4

gdb :
	gdb $(TARGET)
