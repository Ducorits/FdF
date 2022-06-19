CC		=	gcc

SHELL	:= /bin/bash

RED		= \033[1;31m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
ORANGE	= \033[1;38;5;214m
GREEN	= \033[1;32m
RESET	= \033[0m
UP1		= \033[1F
BEGIN	= \033[0G
SAVE	= \0337
RESTORE	= \0338
INSET	= $(BEGIN)$(GREEN)+ $(BLUE)

SRCS	=	main.c

INC		= -I ./include

LIBFT	= libft/libft.a

MLX		= MLX42/libmlx42.a

ifdef $(TESTFLAGS)
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
else
CFLAGS	= -Wall -Wextra -Werror
endif

NAME	= fdf

OBJS	= $(patsubst %.c, obj/%.o, $(SRCS))

all: heading comp

.PHONY: heading comp re rere

comp: $(NAME)

heading:
	@printf "$(CYAN)----< $(ORANGE)Duco's FdF $(CYAN)>----\n"; \

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@
	@printf "$(INSET)$(BLUE)Compiling: $(GREEN)%-29s $(CYAN)%-10s$(RESET)\n" "$^" ""

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBFT) $(MLX) -o $@
	@printf "$(INSET)Compiling: Program $@\n"

$(LIBFT):
	@make -C libft/ SILENT=1

$(MLX):
	@make -C MLX42/

run_test:

clean:
	@rm -rf obj
	@printf "\033[1;31m- $(BLUE)Removed object files\n$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[1;31m- $(BLUE)Removed program file\n$(RESET)"

depclean:
	@make -C libft/ fclean
	@make -C MLX42/ fclean

re: heading fclean comp

rere: heading depclean fclean comp
