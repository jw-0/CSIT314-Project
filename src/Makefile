CC = g++
TARGET = csit314.cgi 
LIBS = -lcgicc
CFLAGS = -std=c++14 -g

.PHONY: default all clean

default: $(TARGET)

Debug: $(TARGET)

Release: $(TARGET)

all: default

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS = $(wildcard *.hpp) $(wildcard */*.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

%.o: %.cpp $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
