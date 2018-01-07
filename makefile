objs: logger/logger.o poke/poke.o

*.o: %.cpp
	g++ -c -o $@ $?

test: objs tests/test.o
	g++ -O3 -o test.exe tests/test.o logger/*.o poke/*.o
	./test.exe

clean:
	rm -f */*.o */*.a test.exe
