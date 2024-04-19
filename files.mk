#####	CONFIG		############################################################
CC = g++
CFLAGS = -Wall -Wextra -Werror -g -std=c++11
NAME = scop
OBJDIR = obj/
BUILDDIR = builds/
SOURCEDIR = srcs/
HEADERDIR = includes/

MAIN_FILE = $(SOURCEDIR)main.cpp

SRC =		$(MAIN_FILE) \
			$(SOURCEDIR)Shader.cpp \
			$(SOURCEDIR)events.cpp \
			$(SOURCEDIR)scopm/src/Vector3.cpp \
			$(SOURCEDIR)scopm/src/Vec4.cpp \
			$(SOURCEDIR)scopm/src/Matrix4x4.cpp \
			lib/glad/src/glad.cpp \
			lib/stb/src/stb_image.cpp
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

GLFW = 		lib/glfw
LIB_GLFW =	$(GLFW)/lib-universal/libglfw3.a
GLAD = 		lib/glad

CCHEADERS = -I$(GLFW)/include/ \
			-I$(GLAD)/include/ \
			-I$(ASSIMP)/include/ \
			-Ilib/stb/include/ \
			-Isrcs/scopm/include/ \

CCFRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -std=c++11

#####	COLORS		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m
