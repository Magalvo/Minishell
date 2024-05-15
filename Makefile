# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/05/15 13:10:06 by cjoao-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
include include/pretty_colors_ANSI

# Project files
SOURCE	= 	minishell.c

SRC		= $(addprefix source/,$(SOURCE))
SRC_DIR = ./source/

OBJ_DIR = ./object/
OBJ		= $(patsubst source/%.c,$(OBJ_DIR)%.o,$(SRC))

INC_DIR = -I ./include/
LIBFT_DIR=./libs/libft/
LIBFT= $(LIBFT_DIR)libft.a
INC_LIB=./libs/

LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Project settings
#
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I${LIBFT_DIR}  #-O3
debug: CFLAGS += -g3 #-fPIE #-fsanitize=address #-pg   #-fsanitize=address
MAKEFLAGS += --no-print-directory #  --silent
.SILENT: $(OBJ) $(NAME) clean fclean
ARFLAGS = rvs
RM = rm -rf
CC = cc
# AR = ar

all: $(NAME)

libft: $(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@printf "$(YELLOW)** compiling **		"$(NAME)"$(RST)\n"
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "$(GREEN_B)$(NAME) created\n$(RST)"

$(OBJ):
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN_I)** compiling **		"$@"$(RST)\n"
	$(CC) $(CFLAGS) $(INC_DIR) -c $(SRC_DIR)$(*F).c -o $@

debug: clean $(LIBFT) $(OBJ)
	@printf "$(YELLOW)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "$(RST)$(GREEN_B)[Debug version created]\n$(RST)"

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	@printf "$(RED)[All $(NAME) objects deleted]    $(RST)\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BNS_NAME)
	$(RM) $(LIBFT)
	@printf "$(RED)[All binaries deleted]    $(RST)\n"

re: fclean all
