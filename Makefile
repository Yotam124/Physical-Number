#!make -f

all: test
	./$<

demo: PhysicalNumberDemo.o PhysicalNumber.o
	clang++-6.0 -std=c++17 $^ -o demo

test: PhysicalNumberTest.o PhysicalNumber.o
	clang++-6.0 -std=c++17 $^ -o test

%.o: %.cpp
	clang++-6.0 -std=c++17 --compile $< -o $@

PhysicalNumber.o: PhysicalNumber.hpp Unit.hpp

PhysicalNumberDemo.o: PhysicalNumber.hpp Unit.hpp

PhysicalNumberTest.o: PhysicalNumber.hpp Unit.hpp badkan.hpp

clean:
	rm -f *.o demo test

