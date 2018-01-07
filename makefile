objs: logger/logger.o poke/poke.o tests/test.o

*.o: %.cpp
	g++ -c -o $@ $?

test: objs
	g++ -o test.exe tests/test.o logger/*.o poke/*.o
	./test.exe

clean:
	rm -f */*.o */*.a test.exe
