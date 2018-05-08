MAIN=main.cpp
HEADERS=matrix.hpp matrix.cpp
EXEC=Project1

default:
	g++ ${MAIN} ${HEADERS} -o ${EXEC}

release:
	rm -rf ${EXEC}
