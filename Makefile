include files.mk

#####	RULES		###################################################

all: $(NAME)

$(NAME) : $(OBJ)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ $(CC) $(LIB_GLFW) $(OBJ) $(CCFRAMEWORKS) -o $(NAME)
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

$(OBJDIR)/%.o: %.cpp
	@ mkdir -p $(@D)
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ $(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	@ rm -f $(OBJ)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)objs ✔️"

fclean: clean
	@ rm -f $(NAME)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)binary ✔️"

re: fclean all

.PHONY: all clean fclean re
