# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 12:56:28 by vkettune          #+#    #+#              #
#    Updated: 2024/05/22 15:18:07 by vkettune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

X = \033[0;39m
BLACK = \033[0;30m
DARK_RED = \033[0;31m
DARK_GREEN = \033[0;32m
DARK_YELLOW = \033[0;33m
DARK_BLUE = \033[0;34m
DARK_MAGENTA = \033[0;35m
DARK_CYAN = \033[0;36m
DARK_GRAY = \033[0;90m
LIGHT_GRAY = \033[0;37m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = minishell
FLAGS = -Wall -Wextra -Werror -g $(HEADERS)
HEADERS = -I ./includes/ # -I ~/.brew/opt/readline/include

LIBS = $(READLINE) $(LIBFT)
READLINE = -lreadline  -L ~/.brew/opt/readline/lib
LIBFT = libft/libft.a

FILES = main.c init.c signals.c args.c cmds.c handle_env.c list_creation.c parsing.c

SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(addprefix objs/, $(FILES:.c=.o))

all: folders comp_libft $(NAME)
	@echo "$(GREEN)- - - - - - - - - - - - - - - - - - - - - - -$(X)"
	@echo "$(GREEN)Run the program with ./$(NAME)$(X)"

objs/%.o: srcs/%.c
	@cc $(FLAGS) -c $< -o $@ && echo "$(DARK_GRAY)Compiled: $@ $(X)"

$(NAME): $(OBJS)
	@cc $(OBJS) $(LIBS) $(FLAGS) -o $(NAME)
	@echo "$(DARK_MAGENTA)- - - - - ✨ Minishell compiled ✨ - - - - - -$(X)"


folders:
	@echo "$(DARK_MAGENTA)- - - - - 📦 Creating folders 📦 - - - - - -$(X)"
	@mkdir -p objs/
	@mkdir -p libft/objs/

comp_libft:
	@echo "$(DARK_MAGENTA)- - - - - 📦 Compiling libft 📦 - - - - - -\n$(X)"
	@make -C ./libft

clean:
	@rm -rf objs/
	@make clean  -C ./libft
	@echo "$(DARK_CYAN)- - - - -❗All object files cleaned❗- - - - -$(X)"
	
fclean: clean
	@rm -f $(NAME)
	@make fclean -C  ./libft
	@echo "$(DARK_CYAN)- - - -❗All executable files cleaned❗- - - -$(X)"
	
re: fclean all
	@echo "$(GREEN)Sucessfully cleaned and rebuilt everything$(X)"

test: # remove this
	@mkdir -p example/ example/example2 example/example2/example3
	@touch example/file1 example/file2 example/example2/file3 example/example2/file4 example/example2/example3/file5
	@echo "$(DARK_MAGENTA)- - - - - test folders and files created - - - - - -\n$(X)"

.PHONY: all clean fclean re
