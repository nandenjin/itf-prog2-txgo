txgo: main.c
	cc -o txgo main.c -L. -I. -lglut -lGL -lGLU -lXi -lXrandr -lm

run: txgo
	./txgo
