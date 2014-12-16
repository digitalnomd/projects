compile: driver.out

driver.out: Driver.o Graph.o
	g++ Driver.o Graph.o -o driver.out

Driver.o: Driver.cpp
	g++ -c Driver.cpp

Graph.o: Graph.cpp
	g++ -c Graph.cpp

run:
	./driver.out $(FILE)

clean:
	rm -f *.o driver.out
