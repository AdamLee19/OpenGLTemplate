CC = g++
CPP = cpp 
H = h
CPPFLAGS = -DAPPLE -Wall -std=c++11 -g
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3 -lGLEW
PROJECT = template


#HFILES = ToolKit.${H} Vector.${H} Utility.${H}
#OFILES = ToolKit.o Vector.o Utility.o

#${CC} ${FLAGS} -o ${BIN} ${PROJECT} ${INC} ${PROJECT}.o ${OFILES} ${FRAMEWORKS}

${PROJECT}:	${PROJECT}.o
	${CC} ${CPPFLAGS} -o ${PROJECT} ${PROJECT}.o ${INC} ${FRAMEWORKS}

${PROJECT}.o : ${PROJECT}.${CPP}
	${CC} ${CPPFLAGS} -c ${PROJECT}.${CPP}






clean:
	rm -f core.* *.o *~ ${PROJECT}

