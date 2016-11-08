#MAKEFILE

#Author
AUTHOR_NAME=LeonardoSantosPaulucio

#Compiler
CC=g++

#Compiler flags
FLAGS=-Wall

#Libs
OPENGL_LIB=-lGL -lGLU -lglut
MATH_LIB=-lm

#Sources variables
TINYXML2_SOURCE= $(wildcard tinyxml2/*.cpp)
SOURCES= $(wildcard sources/*.cpp)

#Executable name
EXECUTABLE_NAME=trabalhocg

all: $(TINYXML2_SOURCE:.cpp=.o) $(SOURCES:.cpp=.o)
	@echo Compiling program
	@$(CC) main.cpp $^ $(FLAGS) $(OPENGL_LIB) $(MATH_LIB) -o $(EXECUTABLE_NAME)
	@echo Done

%.o: %.cpp
	@echo Making object file: $@
	@$(CC) -c $< $(FLAGS) -o $@

run: all
	./$(EXECUTABLE_NAME) ./

zip: clean
	zip -r $(AUTHOR_NAME).zip main.cpp tinyxml2 sources Makefile

rebuild: clean all

clean:
	@echo Cleaning object files
	@rm -f *~ $(SOURCES:.cpp=.o) $(TINYXML2_SOURCE:.cpp=.o) $(EXECUTABLE_NAME)
	@echo Done
