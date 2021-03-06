# -I /sti/til/include-filer
# -L /sti/til/biblioteksfiler (libWHATEVER.so)
# -lfoo lenker inn "foo"-biblioteket (libFOO.so)

minGLUT: minGLUT.cpp
	g++ -o minGLUT minGLUT.cpp -lGL -lGLU -lglut -lGLEW

testmus: testmus.cpp
	g++ -o testmus testmus.cpp -lGL -lGLU -lglut -lGLEW

density: density.cpp
	g++ -o density density.cpp -lGL -lGLU -lglut -lGLEW

GLUT_tutorial: GLUT_tutorial.cpp
	g++ -o GLUT_tutorial GLUT_tutorial.cpp -lGL -lGLU -lglut -lGLEW

test: test.cpp
	g++ -o test test.cpp -lGL -lGLU -lglut -lGLEW

test2: test2.cpp
	g++ -o test2 test2.cpp -lGL -lGLU -lglut -lGLEW
