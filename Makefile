
LINKPATH = #/usr/local/Cellar/glfw/3.3.2/lib 

all:
	clang++ -std=c++11 main2.cpp ft_strsplit.c /usr/local/src/glad.c  -l glfw.3.3 -l GLEW.2.1.0 -framework OpenGL


