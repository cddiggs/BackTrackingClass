all	: threeCond sudoku maze

threeCond	: threeCond.o backtrack.o
	g++ -o threeCond threeCond.o backtrack.o
threeCond.o: threeCond.cc backtrack.h
	g++ -c threeCond.cc

sudoku	: sudoku.o backtrack.o
	g++ -o sudoku sudoku.o backtrack.o
sudoku.o: sudoku.cc backtrack.h
	g++ -c sudoku.cc


maze	: maze.o backtrack.o
	g++ -o maze maze.o backtrack.o
maze.o: maze.cc backtrack.h
	g++ -c maze.cc


backtrack.o	:backtrack.h
	g++ -c backtrack.ccclean	:
	rm -rf backtrack.o threeCond threeCond.o sudoku sudoku.o maze maze.o

