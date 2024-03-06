#####	CONFIG		############################################################
CC = g++
CFLAGS = -Wall -Wextra -Werror -g
NAME = scop
OBJDIR = obj/
BUILDDIR = builds/
SOURCEDIR = srcs/
HEADERDIR = includes/

MAIN_FILE = $(SOURCEDIR)main.cpp

SRC =		$(MAIN_FILE) \
			lib/glad/src/glad.cpp
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

GLFW = 		lib/glfw-3.4.bin.MACOS
GLAD = 		lib/glad

CCHEADERS = -I$(GLFW)/include/ \
			-I$(GLAD)/include/ \

CCLIBS =	-L$(GLFW)/lib-universal -lglfw3 \

CCFRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

#####	COLORS		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m
