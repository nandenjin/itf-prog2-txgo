txgo: ImageUtil.o TextUtil.o Track.o map.o GenericTimer.o drive.o main.o
	cc -o txgo ./lib/libglpng.ICHO.a ImageUtil.o TextUtil.o Track.o map.o GenericTimer.o drive.o main.o -L. -I. -lglut -lGL -lGLU -lXi -lXrandr -lm

.c.o: 
	cc -c $< -I. -Wall

run: txgo
	./txgo
	
clean:
	rm -f *.o *.c~ *.h~ txgo
