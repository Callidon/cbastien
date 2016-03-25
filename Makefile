# Projet de compilation - M1 ALMA
# auteurs : Pierre Gaultier & Thomas Minier
CXX = g++
CXXFLAGS = -I./includes/ --std=c++11 -Wall
SOURCES = src/generators.cpp src/scanner.cpp src/table_symboles.cpp src/analyser.cpp src/actions.cpp src/serializer.cpp src/interpreter.cpp
.PHONY : clean

cbastien: $(SOURCES:.cpp=.o)

clean:
	rm src/*.o cbastien
