CXX = clang++
CXXFLAGS = -I/opt/homebrew/include -std=c++14
LDFLAGS = -L/opt/homebrew/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = sfml_test.cpp src/window/window.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = sfml_test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)
