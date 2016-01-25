CXX = g++
CXXFLAGS = -I./includes/
SOURCES = src/generators.cpp
.PHONY : clean

cbastien: $(SOURCES:.cpp=.o)

clean:
	rm src/*.o cbastien
