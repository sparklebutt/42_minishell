# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 15:15:31 by vkettune          #+#    #+#              #
#    Updated: 2024/08/08 21:37:02 by vkettune         ###   ########.fr        #
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

NAME = libft.a
FLAGS = -g -Wall -Wextra -Werror $(HEADERS)

HEADERS = -I ../incs/
SRCS_DIR = srcs/
OBJS_DIR = objs/

# SRC FILES
LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_lstadd_back.c \
		ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c ft_lstsize.c \
		ft_strcpy.c ft_strncpy.c ft_get_next_line.c
PRINTF = ft_printf.c ft_print.c ft_utils.c
SOURCES = $(addprefix $(SRCS_DIR), $(LIBFT)) \
		$(addprefix $(SRCS_DIR), $(PRINTF)) \

# OBJECT FILES
LIBFT_OBJ = $(addprefix $(OBJS_DIR), $(LIBFT:.c=.o))
PRINTF_OBJ = $(addprefix $(OBJS_DIR), $(PRINTF:.c=.o))
OBJECTS = $(LIBFT_OBJ) $(PRINTF_OBJ)

all: libft ft_printf $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ && echo "$(DARK_GRAY)Compiled: $(notdir $@) $(X)"

$(NAME): $(OBJECTS)

libft: $(LIBFT_OBJ)
	@ar -rc $(NAME) $(LIBFT_OBJ)
	@echo "$(DARK_CYAN)- - - - - - ✨ Libft compiled! ✨ - - - - - -$(X)"

ft_printf: $(PRINTF_OBJ)
	@ar -rc $(NAME) $(PRINTF_OBJ)
	@echo "$(DARK_CYAN)- - - - - - ✨ Printf compiled! ✨  - - - - -$(X)"

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
	@echo "$(GREEN)Sucessfully cleaned and rebuilt everything$(X)"
