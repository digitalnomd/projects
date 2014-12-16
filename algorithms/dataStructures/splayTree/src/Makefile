compile: driver.out

driver.out: driver.o HashedSplays.o Node.o Util.o
	g++ driver.o HashedSplays.o Node.o Util.o -o driver.out

driver.o: driver.cpp
	g++ -c driver.cpp

HashedSplays.o: HashedSplays.cpp
	g++ -c HashedSplays.cpp

Node.o: Node.cpp
	g++ -c Node.cpp

Util.o: Util.cpp
	g++ -c Util.cpp

run:
	./driver.out $(DATA)

clean:
	rm -f *.o driver.out