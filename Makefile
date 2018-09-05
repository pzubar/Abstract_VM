CC=g++ 
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=main.cpp AbstractVM.cpp Operand.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=avm

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@