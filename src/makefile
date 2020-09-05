CXX := clang++
CXXFLAGS := -std=c++17 -I../include -Wall -Wextra -Weffc++ -pedantic -O3

OBJ := main.o camera.o render.o material.o sphere.o object.o ray.o vec3.o pt_util.o stb_image_write.o

.PHONY: all clean

all: path_tracer

path_tracer: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o path_tracer


depend:
	$(CXX) $(CXXFLAGS) -E -MM $(OBJ:.o=.cpp) > .depend

clean:
	-rm *.o path_tracer
	-rm -rf *.dSYM

include .depend