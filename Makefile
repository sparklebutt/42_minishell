# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaboom <shaboom@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 12:56:28 by vkettune          #+#    #+#              #
#    Updated: 2025/07/09 14:35:07 by shaboom          ###   ########.fr        #
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
HEADERS = -I ./incs/

LIBS = $(READLINE) $(LIBFT)
READLINE = -lreadline  -L ~/.brew/opt/readline/lib
LIBFT = libft/libft.a

OBJS_DIR = objs/
SRCS_DIR = srcs/

FILES = main.c init.c handle_line.c forking.c forking_utils.c redirects.c \
redir_helper.c heredoc.c testing_functions.c

CMD_FILES = cd.c echo.c env.c exit.c export.c pwd.c unset.c

ENV_FILES = find_from_env.c list_manipulation.c variable_expansions.c

PAR_FILES = parsers.c parsing_not.c pipe_parsing.c quotes_parsing.c check_path.c \
parsing_helpers.c stupid_functions.c

UTIL_FILES = utils.c error_handling.c free_things.c ft_split_adv.c signals.c \
ft_split_expansions.c check_dir.c exit_code.c string_loopers.c string_loopers_2.c \
string_loopers_3.c ft_split_adv_helpers.c forking_utils_2.c

CMD = $(addprefix cmds/, $(CMD_FILES))
ENV = $(addprefix env/, $(ENV_FILES))
PAR = $(addprefix parsing/, $(PAR_FILES))
UTIL = $(addprefix utils/, $(UTIL_FILES))

SOURCES = $(addprefix $(SRCS_DIR), $(FILES)) \
		$(addprefix $(SRCS_DIR), $(CMD)) \
		$(addprefix $(SRCS_DIR), $(ENV)) \
		$(addprefix $(SRCS_DIR), $(UTIL_FILES)) \
		$(addprefix $(SRCS_DIR), $(PAR)) \

OBJ = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))
CMD_OBJ = $(addprefix $(OBJS_DIR), $(CMD:.c=.o))
ENV_OBJ = $(addprefix $(OBJS_DIR), $(ENV:.c=.o))
UTIL_OBJ = $(addprefix $(OBJS_DIR), $(UTIL:.c=.o))
PAR_OBJ = $(addprefix $(OBJS_DIR), $(PAR:.c=.o))

OBJECTS = $(OBJ) $(CMD_OBJ) $(ENV_OBJ) $(UTIL_OBJ) $(PAR_OBJ)

all: folders comp_libft $(NAME)
	@echo "$(GREEN)- - - - - - - - - - - - - - - - - - - - - - -$(X)"
	@echo "$(GREEN)Run the program with ./$(NAME)$(X)"

objs/%.o: srcs/%.c
	@cc $(FLAGS) -c $< -o $@ && echo "$(DARK_GRAY)Compiled: $@ $(X)"

$(NAME): $(OBJECTS)
	@cc $(OBJECTS) $(LIBS) $(FLAGS) -o $(NAME)
	@echo "$(DARK_MAGENTA)- - - - -  ✨ Minishell compiled ✨ - - - - -$(X)"

folders:
	@echo "$(DARK_MAGENTA)- - - - -  📦 Creating folders 📦 - - - - - -$(X)"
	@mkdir -p objs/cmds objs/env objs/utils objs/parsing
	@mkdir -p libft/objs/

comp_libft:
	@echo "$(DARK_MAGENTA)- - - - - - 📦 Compiling libft 📦 - - - - - -$(X)"
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

.PHONY: all clean fclean re
