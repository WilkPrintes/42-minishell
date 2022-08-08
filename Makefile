NAME		:= minishell

CC			:= clang

LIBFT		:= ./includes/libft/libft.a

LIBFT_PATH	:= ./includes/libft/

LIBFT_FLAGS	:= -L $(LIBFT_PATH) -lft

HEADER_DIR	:= ./header/ ./includes/libft/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	command_utils.c built_in_utils.c minishell.c vars.c \
				built_in.c exec_command.c handle_fd.c exit_utils.c  \
				parsing.c redirections.c parsing_utils.c pipex.c main_utils.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) -g $(SRC) -o $@ $(INCLUDE) $(LIBFT_FLAGS) -lreadline
	@echo "\033[0;32mMinishell (>‿◠)\033[0m"

$(LIBFT):
	@echo compilando libft...
	@make -s -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@echo apagando libft
	@make fclean -s -C $(LIBFT_PATH)
	@echo "\033[0;31mMinishell deleted (ㆆ_ㆆ)\033[0m"

clean:
	@make clean -s -C $(LIBFT_PATH)
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

leaks:
	@valgrind --leak-check=full --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

.PHONY: all fclean re
