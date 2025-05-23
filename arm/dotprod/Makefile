OPT_ASM=-S -l -O3 -march=armv8.4-a+dotprod
OPT_CMP=-c -O3 -march=armv8.4-a+dotprod 

all:
	mkdir -p build
	g++ $(OPT_ASM) dotprod.cpp -o build/dotprod.S
	g++ $(OPT_CMP) dotprod.cpp -o build/dotprod.o
	g++ build/dotprod.o -o build/dotprod
	build/dotprod

clean:
	rm -rf build
