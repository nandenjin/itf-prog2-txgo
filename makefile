txgo: ImageUtil.o main.o
	cc -o txgo ImageUtil.o main.o -L. -I. -lglut -lGL -lGLU -lXi -lXrandr -lglpng -lm

.c.o: 
	cc -c $< -I. -Wall

run: txgo
	./txgo
	
clean:
	rm -f *.o *.c~ *.h~ txgo
