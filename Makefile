CC		=	gcc

SHELL	:=	/bin/bash

UNAME	:=	$(shell uname)

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

SRCS	=	main.c \
			error_check.c \
			debug.c \
			fdf_init.c \
			map_init.c \
			fdf_exit.c \
			fdf_loop.c \
			fdf_free.c \
			fdf_keycheck.c \
			map_utils.c \
			transforms.c \
			drawline.c \
			fdf_scrollhook.c \
			perspective.c \
			hsv.c \
			color.c

TEST_SRC=	error_check.c \
			debug.c \
			fdf_init.c \
			map_init.c \
			fdf_exit.c \
			fdf_loop.c \
			fdf_free.c \
			fdf_keycheck.c \
			map_utils.c \
			transforms.c \
			drawline.c \
			fdf_scrollhook.c \
			perspective.c \
			hsv.c \
			color.c

INC		= -I ./include

LIBFT	= libft/libft.a

MLX		= MLX42/libmlx42.a

ifeq ($(UNAME),Linux)
GLFW	= -lglfw
else
GLFW	= libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit
endif

MATHLIB	= -lm

ifeq ($(DEBUG), 1)
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
else
CFLAGS	= -Wall -Wextra -Werror
endif

ifeq ($(OPTIMIZE), 1)
CFLAGS	:= $(CFLAGS) -o3
endif

NAME	= fdf

OBJS	= $(patsubst %.c, obj/%.o, $(SRCS))
TEST_OBJ= $(patsubst %.c, obj/%.o, $(TEST_SRC))

all: heading comp

.PHONY: heading comp re rere test libft mlx

comp: $(NAME)

libft:
	@make -C libft/ SILENT=1
	@cp libft/include/libft.h include/libft.h

mlx: $(MLX)

heading:
	@printf "$(CYAN)----< $(ORANGE)Duco's FdF $(CYAN)>----\n"; \

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@
	@printf "$(INSET)$(BLUE)Compiling: $(GREEN)%-29s $(CYAN)%-10s$(RESET)\n" "$^" ""

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INC) $(LIBFT) $(MLX) $(GLFW) $(MATHLIB) -o $@
	@printf "$(INSET)Compiling: Program $@\n"

$(LIBFT):
	@make -C libft/ SILENT=1
	@cp libft/include/libft.h include/libft.h

$(MLX):
	@make -C MLX42/

test: test/test.c $(MLX) $(LIBFT) $(TEST_OBJ)
	@printf "$(INSET)$(ORANGE)Running Tests:\n"
	@$(CC) $(CFLAGS) $(INC) -c test/test.c -o test/test.o
	@$(CC) $(CFLAGS) $(TEST_OBJ) test/test.o $(INC) $(LIBFT) $(MLX) $(GLFW) $(MATHLIB) -o test.out
	@./test.out

clean:
	@rm -rf obj
	@printf "\033[1;31m- $(BLUE)Removed object files\n$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[1;31m- $(BLUE)Removed program file\n$(RESET)"

depclean:
	@make -C libft/ fclean
	@make -C MLX42/ fclean

testclean:fclean depclean
	@rm -rf test/test.o
	@rm -rf test.out

re: heading fclean comp

rere: heading fclean depclean comp
