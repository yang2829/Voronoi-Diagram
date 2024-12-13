target = _fortune$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -shared -fPIC -m64 $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
PYTEST = test_fortune.py
source = ./src/Beachline.cpp ./src/Fortune.cpp ./src/main.cpp

all: clean $(target)

$(target): ./src/*.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(target) $(PYTEST)
	python3 -m pytest -v

testexe: $(source)
	$(CXX) -o test.exe $^

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/ *.exe