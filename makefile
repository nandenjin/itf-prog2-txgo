txgo: ImageUtil.o TextUtil.o Track.o map.o Ranking.o GenericTimer.o drive.o main.o
	cc -o txgo ImageUtil.o TextUtil.o Track.o map.o Ranking.o GenericTimer.o drive.o main.o -L. -I. -L./lib -lglut -lGL -lGLU -lXi -lXrandr -lglpng.ICHO -lm

.c.o: 
	cc -c $< -I. -Wall

run: txgo
	./txgo
	
clean:
	rm -f *.o *.c~ *.h~ txgo
