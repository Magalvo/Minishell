# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/06/27 18:26:35 by cjoao-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
include include/pretty_colors_ANSI

# Project files
BUILTINS =	builtins.c cd_cmd.c echo_cmd.c env_cmd.c \
			exit_cmd.c export_cmd.c pwd_cmd.c unset_cmd.c \
			export_print.c export_aux.c export_update.c\

EXECUTOR =	executor.c ast.c \

# EXECUTOR =	executor.c

PARSER =	aux.c	expand_tilde.c	expand_vars.c	expand_vars2.c \
			get_expanded.c	init_cmd.c	init_heredoc.c	init_heredoc_aux.c \
			parse_exec.c	parse_prechecks.c	parse_quotes.c	parse_redir.c \
			parse.c	syntax_tests.c	tokens.c


AUX = aux1.c env_aux.c env_aux2.c pipe_exec.c redir_exec.c \
		free.c	ft_ms_aux.c env_aux3.c	env_aux4.c

SIG = signals.c	signals_type.c

AST = ast_print.c ast_print_types.c


SRC_DIR = ./source/
BUILTINS_DIR = $(SRC_DIR)builtins/
EXECUTOR_DIR = $(SRC_DIR)executor/
PARSER_DIR 	= $(SRC_DIR)parser/
AUX_DIR 	= $(SRC_DIR)aux/
AST_DIR 	= $(SRC_DIR)ast/
SIG_DIR 	= $(SRC_DIR)signals/


SRC = 	$(SRC_DIR)minishell.c \
		$(SRC_DIR)minishell_aux.c \
		$(SRC_DIR)errors.c \
		$(addprefix $(BUILTINS_DIR), $(BUILTINS)) \
		$(addprefix $(EXECUTOR_DIR), $(EXECUTOR)) \
		$(addprefix $(PARSER_DIR), $(PARSER)) \
		$(addprefix $(AUX_DIR), $(AUX)) \
		$(addprefix $(AST_DIR), $(AST)) \
		$(addprefix $(SIG_DIR), $(SIG)) \

OBJ_DIR = ./object/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = -I ./include/
LIBFT_DIR = ./libs/libft/
LIBFT = $(LIBFT_DIR)libft.a
INC_LIB = ./libs/

LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Project settings
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I${LIBFT_DIR} #-fsanitize=address  #-O3
debug: CFLAGS += -g3 #-fPIE #-fsanitize=address #-pg   #-fsanitize=address
MAKEFLAGS += --no-print-directory #  --silent
.SILENT: $(OBJ) $(NAME) clean fclean
ARFLAGS = rvs
RM = rm -rf
CC = cc #-ggdb -fsanitize=address -fno-omit-frame-pointer
# AR = ar


all: $(NAME)


libft: $(LIBFT)

.: fclean $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

# $(NAME): $(LIBFT) $(OBJ)
$(NAME): $(OBJ)
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

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --trace-children=yes --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all ./${NAME}
#valgrind --suppressions=readline.supp --tool=memcheck --tool=callgrind  --track-fds=yes ./${NAME}


re: fclean all
