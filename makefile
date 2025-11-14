
output: tree.o booktree.h
	g++ main.o -o output

main.o: booktree.cpp booktree.h
	g++ -c main.cpp

booktree.o: booktree.cpp booktree.h
	g++ -c booktree.cpp

clean:
	rm *.o output