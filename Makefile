NAME		:= minishell

CC			:= gcc

LIBFT		:= ./includes/libft/libft.a

LIBFT_PATH	:= ./includes/libft/

LIBFT_FLAGS	:= -L $(LIBFT_PATH) -lft

HEADER_DIR	:= ./header/ ./includes/libft/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=  minishell.c command_utils.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) -g $(SRC) -o $@ $(INCLUDE) -lreadline $(LIBFT_FLAGS)
	@echo "\033[0;32m Minishell (>‿◠)\033[0m"

$(LIBFT):
	@make -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[0;31m Minishell deleted (ㆆ_ㆆ)\033[0m"

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

.PHONY: all fclean re