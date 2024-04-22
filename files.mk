#####	CONFIG		############################################################
CC = g++
CFLAGS = -Wall -Wextra -Werror -g -std=c++11
NAME = scop
OBJDIR = obj/
BUILDDIR = builds/
SOURCEDIR = srcs/
HEADERDIR = includes/

MAIN_FILE = $(SOURCEDIR)main.cpp

GLFW = 		lib/glfw/
GLAD = 		lib/glad/
STB = 		lib/stb/
SCOPM = 	$(SOURCEDIR)scopm/

LIB_GLFW =	$(GLFW)/lib-universal/libglfw3.a

SRC =		$(MAIN_FILE) \
			$(SOURCEDIR)Shader.cpp \
			$(SOURCEDIR)events.cpp \
			$(SCOPM)src/Vec2.cpp \
			$(SCOPM)src/Vec3.cpp \
			$(SCOPM)src/Vec4.cpp \
			$(SCOPM)src/Mat4.cpp \
			$(GLAD)src/glad.cpp \
			$(STB)src/stb_image.cpp
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)


CCHEADERS = -I$(GLFW)include/ \
			-I$(GLAD)include/ \
			-I$(ASSIMP)include/ \
			-I$(STB)include/ \
			-I$(SCOPM)include/ \

CCFRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

#####	COLORS		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m
