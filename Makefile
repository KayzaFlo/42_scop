CC = g++
CFLAGS = -Wall -Wextra -Werror -g
NAME = scop
BUILDDIR = builds/
SOURCEDIR = srcs/
HEADERDIR = includes/

include files.mk

GLFW = 		/Users/fgeslin/homebrew/opt/glfw


CCHEADERS = -I$(GLFW)/include/

CCLIBS =	-L$(GLFW)/lib -lglfw
# CCLIBS =	-lglfw3

CCFRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CCHEADERS) $(CCLIBS) $(OBJ) $(CCFRAMEWORKS) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

