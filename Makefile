CC	=	gcc

SHELL := /bin/bash

BLUE = \033[1;34m
CYAN = \033[1;36m
ORANGE = \033[38;5;214m
GREEN = \033[1;32m
RESET = \033[0m
UP1 = \033[1F
BEGIN = \033[0G
SAVE = \0337
RESTORE = \0338
INSET = $(BEGIN)$(GREEN)+ $(BLUE)

SRCS =

INC	=	-I ./include

ifdef $(TESTFLAGS)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
else
CFLAGS = -Wall -Wextra -Werror
endif

NAME = libft.a

OBJS = $(patsubst %.c, obj/%.o, $(SRCS))

all: heading comp

.PHONY: heading comp compdone done clean fclean re

comp: $(OBJS) compdone $(NAME) done

heading:
	@printf "$(CYAN)---< $(ORANGE)Duco's FdF $(CYAN)>---\n"; \

compdone:
	@printf "$(INSET)$(BLUE)Compiling - $(GREEN)%-29s $(CYAN)%-10s$(RESET)\n" "Done!" ""; \

done:
	@printf "$(BEGIN)$(CYAN)-------< $(ORANGE)Done $(CYAN)>-------\n$(RESET)"; \

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@
	@printf "$(INSET)$(BLUE)Compiling - $(GREEN)%-29s $(CYAN)%-10s$(RESET)\n" "$^" ""
	@$(eval COMP += $@)

$(NAME): $(OBJS)
	@printf "$(INSET)"
	@ar rs $(NAME) $(OBJS)

clean:
	@rm -rf obj
	@printf "\033[1;31m- $(BLUE)Removed object files\n$(RESET)"

fclean: clean
	@rm -f libft.a
	@printf "\033[1;31m- $(BLUE)Removed archive file\n$(RESET)"

re: heading fclean comp
