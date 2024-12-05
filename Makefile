target = _fortune$(shell python3-config --extension-suffix)

CXX = g++
# CXXFLAGS = -std=c++17 -Wall -O3 -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
PYTEST = test_fortune.py
source = ./src/Beachline.cpp ./src/Fortune.cpp

# all: $(target)

# $(target): $(source)
# 	$(CXX) $(CXXFLAGS) -I./ -I$(MKL_INC) -I$(NUMPY) -o $@ $^ -lblas -lmkl_rt

# test: $(target) $(PYTEST)
# 	python3 -m pytest -v

testexe: ./src/*.cpp
	$(CXX) -o test.exe $^

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/