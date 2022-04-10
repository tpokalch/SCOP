
LINKPATH = #/usr/local/Cellar/glfw/3.3.2/lib 
#/Users/taraspokalchuk/Downloads/glfw-3.3.6.bin.MACOS/include

all:
	clang++ -std=c++11 main2.cpp ft_strsplit.c /Users/taraspokalchuk/Downloads/glad/src/glad.c  -lglfw3 -L/opt/X11/lib -lX11 -lXext -lpthread -ldl -framework OpenGL -framework AppKit -framework IOKit

