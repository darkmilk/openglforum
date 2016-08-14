LINKS	:=	-lglfw -lGLEW -lGL -lpthread
bin/main: main.o myheader.o
	gcc -o bin/main main.o myheader.o ${LINKS}
main.o: main.c myheader.h
	gcc -c main.c
myheader.o: myheader.c myheader.h
	gcc -c myheader.c
clean:
	rm -rf *.o bin/*
