# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/03 14:41:58 by fnancy            #+#    #+#              #
#    Updated: 2019/12/06 11:18:29 by fnancy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re, make_lft

# ************************************************************************** #
#                           colors                                           #
# ************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
AQUA = \033[36m
GREY = \033[37m
UNDERLINE = \033[4m
ESCN = \033[0m

# ************************************************************************** #
#                           Configuration                                    #
# ************************************************************************** #
NAME = minishell
FLAGS = -Wall -Wextra

WS_PATH = $(shell pwd)
SRC_PATH = $(WS_PATH)/sources/
OBJ_PATH = $(WS_PATH)/objs/
INC_PATH = $(WS_PATH)/includes/
LIB_PATH = $(WS_PATH)/Libft/
LIB_INC_PATH = $(LIB_PATH)includes/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
INC = $(addprefix -I, $(INC_PATH))
INC_LIB = $(addprefix -I, $(LIB_INC_PATH))

SRC_FILES = sh_main.c frees.c ft_flagsparser.c env/env_init.c env/env_get_variable.c\
			bltns/bltn_echo.c bltns/bltn_env.c bltns/bltn_exit.c bltns/bltn_help.c\
			bltns/bltn_setenv.c bltns/bltn_unsetenv.c bltns/bltn_pwd.c\
			readline/read_line.c\
			lex/tokenizer.c lex/findbin.c\
			exe/exe_init.c exe/exe_launch.c exe/exe_parsecmd.c\
			bltns/bltn_cd/bltn_cd_parser.c bltns/bltn_cd/bltn_cd_pathfuncs.c bltns/bltn_cd/bltn_cd.c bltns/bltn_cd/bltn_cd_helps.c\
			bltns/bltn_cd/bltn_cd_home.c bltns/bltn_cd/bltn_cd_oldpwd.c bltns/bltn_cd/bltn_cdpath_help.c\
			sys_tool/sys_tool_files.c\

ADD_OBJ = $(addprefix $(OBJ_PATH), env bltns exe lex readline bltns/bltn_cd sys_tool)


OBJ_FILES = $(SRC_FILES:.c=.o)

# ************************************************************************** #
#                                   Rules                                    #
# ************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@make make_lft
	@gcc $(FLAGS) -o $(NAME) $(INC) $(INC_LIB) $(OBJ) -L $(LIB_PATH) -lft -lncurses -g

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "$(GREY)$(UNDERLINE)CREATING >> $@$(ESCN)"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(ADD_OBJ)
	@gcc $(INC) $(INC_LIB) -o $@ -c $<

make_lft:
	@echo "$(GREEN)$(UNDERLINE)COMPILING LIBFT$(ESCN)"
	@make -C $(LIB_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)

re: fclean all

ex:
	gcc exmpl.c -lcurses -g -o 42sh -L libft -lft -I libft/includes

appc: $(OBJ)
	@make make_lft
	@gcc $(FLAGS) -o $(NAME) $(INC) $(INC_LIB) $(OBJ) -L $(LIB_PATH) -lft -L /usr/lib/x86_64-linux-gnu/libncurses.so -lncurses
