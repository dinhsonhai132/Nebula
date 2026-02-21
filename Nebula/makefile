CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

LIBS = -lSDL2 -lSuny
LDFLAGS = -Wl,--subsystem,console

TARGET = nebula.exe
SOURCES = main.cpp game.cpp engine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o 2>nul || true