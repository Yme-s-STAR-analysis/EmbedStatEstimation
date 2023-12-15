all: run

run: CreateCsvFile.cxx Util.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3
