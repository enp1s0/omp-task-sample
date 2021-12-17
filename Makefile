CXX=g++
CXXFLAGS=-std=c++14 -fopenmp

TARGET=omp-task.test

$(TARGET):main.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)
  
clean:
	rm -f $(TARGET)
