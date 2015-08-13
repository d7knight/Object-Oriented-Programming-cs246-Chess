CXX = g++ # compiler
CXXFLAGS = -g -Wall -MMD # compiler flags
OBJECTS = bishop.o board.o empty.o king.o knight.o main.o pawn.o piece.o player.o queen.o rook.o scoreboard.o textdisplay.o window.o # object files forming executable
DEPENDS = ${OBJECTS:.o=.d} # substitute “.o” with “.d”
EXEC = chess -lX11 # executable name

${EXEC} : ${OBJECTS} # link step
	${CXX} ${OBJECTS} -o ${EXEC}



