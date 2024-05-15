# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/05/09 19:10:30 by cjoao-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
include include/pretty_colors_ANSI

# Project files
#
SRC =	ft_isalpha.c	ft_isdigit.c	ft_tolower.c	ft_isalnum.c \
		ft_isascii.c	ft_isprint.c	ft_toupper.c	ft_strchr.c \
		ft_strrchr.c	ft_strlen.c		ft_strncmp.c	ft_memset.c \
		ft_bzero.c		ft_memchr.c		ft_memcpy.c		ft_memcmp.c \
		ft_strnstr.c	ft_strlcpy.c	ft_strlcat.c 	ft_atoi.c \
		ft_calloc.c		ft_strdup.c 	ft_putchar_fd.c	ft_itoa.c\
		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_strmapi.c\
		ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_striteri.c \
		ft_memmove.c	ft_split.c 		ft_isspace.c	ft_atol.c \
		ft_issignal.c 	ft_abs.c		ft_ismax.c		ft_atof.c \
		ft_printf.c		ft_printf_format.c	ft_sprintf.c \
		get_next_line.c	get_next_line_utils.c 	ft_free_dptr.c \
		ft_strcount.c \
		ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c \
		ft_lstadd_back.c	ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c \
		ft_lstmap.c
SRC_DIR = ./source/
OBJ_DIR = ./object/
INC_DIR = -I ./include/
OBJECTS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Build settings
#
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -O3
debug: CFLAGS += -g3 -fPIE
MAKEFLAGS += --no-print-directory #  --silent
.SILENT:  clean fclean debug $(OBJECTS) $(NAME)
ARFLAGS = rvs
RM = rm -rf
# CC = cc
# AR = ar

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(YELLOW)** linking objects **	"$(NAME)"$(RST)\n"
	tput setaf 3; $(AR) $(ARFLAGS) $(NAME) $? >/dev/null; tput setaf 9
	@printf "$(GREEN_B)LIBFT.A created $(RST)\n"

$(OBJECTS):
	@printf "$(CYAN_I)** compiling **		"$@"$(RST)\n"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $(SRC_DIR)$(*F).c -o $@

debug: fclean $(OBJECTS) $(NAME)
	@printf "$(GREEN_B)** LIBFT.A DEBUG created ** $(RST)\n"

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJ_DIR)
	@printf "$(RED)[All libft objects deleted]    $(RST)\n"

fclean: clean
	$(RM) $(NAME)
	@printf "$(RED)[libft.a deleted]    $(RST)\n"

re: fclean all
