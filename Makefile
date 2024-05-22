# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/05/21 12:46:18 by dde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
# Pretty colors
include include/pretty_colors_ANSI

# Project files
BUILTINS =	builtins.c cd_cmd.c echo_cmd.c env_cmd.c \
			exit_cmd.c export_cmd.c pwd_cmd.c unset_cmd.c \

EXECUTOR =	executor.c

SRC_DIR = ./source/
BUILTINS_DIR = $(SRC_DIR)builtins/
EXECUTOR_DIR = $(SRC_DIR)executor/

SRC = 	$(SRC_DIR)minishell.c \
		$(SRC_DIR)signals.c \
		$(SRC_DIR)errors.c \
		$(addprefix $(BUILTINS_DIR), $(BUILTINS)) \
		$(addprefix $(EXECUTOR_DIR), $(EXECUTOR)) \

OBJ_DIR = ./object/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = -I ./include/
LIBFT_DIR = ./libs/libft/
LIBFT = $(LIBFT_DIR)libft.a
INC_LIB = ./libs/

LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Project settings
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I${LIBFT_DIR} #-O3
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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(CYAN_I)** compiling **		"$<"$(RST)\n"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

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
