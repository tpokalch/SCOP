
LINKPATH = #/usr/local/Cellar/glfw/3.3.2/lib 

all:
	clang++ main2.cpp ./src/glad.c ft_strsplit.c -I "./deps" -I "./include/" -l $(LINKPATH) glfw.3.3 -l GLEW.2.1.0 -framework OpenGL


#/System/Library/Frameworks/OpenGL.framework/
#	g++ -std=c++11 ft_strsplit.cpp parse.cpp init.cpp MyFramework.cpp main.cpp ../Framework/src/launch.cpp -l SDL2_image-2.0.0 -l SDL2-2.0.0 -o game

