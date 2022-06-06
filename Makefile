NAME		:= minishell

CC			:= gcc

LIBFT		:= ./includes/libft/libft.a

LIBFT_PATH	:= ./includes/libft/

LIBFT_FLAGS	:= -L $(LIBFT_PATH) -lft

HEADER_DIR	:= ./header/ ./includes/libft/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	command_utils.c lucas_utils.c minishell.c vars.c command.c \
				parsing.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) -g $(SRC) -o $@ $(INCLUDE) $(LIBFT_FLAGS) -lreadline
	@echo "\033[0;32mMinishell (>‿◠)\033[0m"

$(LIBFT):
	@make -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[0;31mMinishell deleted (ㆆ_ㆆ)\033[0m"

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

.PHONY: all fclean re
