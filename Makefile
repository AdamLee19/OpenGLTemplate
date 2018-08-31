CC = g++
CPP = cpp 
H = h
CPPFLAGS = -DAPPLE -Wall -std=c++11 -g
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3 -lGLEW
PROJECT = template

HFILES = Model.${H} View.${H} Camera.${H}
OFILES = Model.o View.o Camera.o#Vector.o Utility.o

#${CC} ${FLAGS} -o ${BIN} ${PROJECT} ${INC} ${PROJECT}.o ${OFILES} ${FRAMEWORKS}

${PROJECT}:	${PROJECT}.o ${OFILES}
	${CC} ${CPPFLAGS} -o ${PROJECT} ${PROJECT}.o ${OFILES} ${INC} ${FRAMEWORKS}


${PROJECT}.o : ${PROJECT}.${CPP} Model.${H} View.${H}
	${CC} ${CPPFLAGS} -c ${PROJECT}.${CPP}

Model.o : Model.${CPP} Model.${H}
	${CC} ${CPPFLAGS} -c Model.${CPP}

View.o : View.${CPP} View.${H} Camera.${H}
	${CC} ${CPPFLAGS} -c View.${CPP}

Camera.o : Camera.${CPP} Camera.${H}
	${CC} ${CPPFLAGS} -c Camera.${CPP}







clean:
	rm -f core.* *.o *~ ${PROJECT}

