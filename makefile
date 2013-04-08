OPTS  = -Wall -Wextra -g -O3
OBJS  = *.o
FILES = src/parser.cpp src/Tour.cpp

launch: head
	g++  $(OPTS) $(OBJS) src/iter_tsp.cpp -o tsptw-ii

opti: head-opti
	g++ $(OPTS) $(OBJS) src/vnd.cpp -o tsptw-vnd

head: $(FILES)
	g++ $(OPTS) -c $(FILES)

head-opti: $(FILES)
	g++ $(OPTS) -c $(FILES)

clean:
	rm *.o gare

cleaner : clean
	rm *~ class/*~
