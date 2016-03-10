# Projet de compilation
# auteurs : Pierre Gaultier & Thomas Minier
CXX = g++
CXXFLAGS = -I./includes/ --std=c++11
SOURCES = src/generators.cpp src/scanner.cpp src/table_symboles.cpp src/analyser.cpp src/serializer.cpp
.PHONY : clean

cbastien: $(SOURCES:.cpp=.o)

clean:
	rm src/*.o cbastien
