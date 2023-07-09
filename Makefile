# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:11:29 by tknibbe           #+#    #+#              #
#    Updated: 2023/07/08 17:01:24 by tknibbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


INCLUDE		=	-I includes -I lib/includes
CFLAGS		=	#-Wall -Werror -Wextra
READLINE	=	-lreadline
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell
LIBFT		=	lib/libft.a
SRC			=	cris_main.c \
				parse_and_exec.c \
				exit_funcs.c \
				built_ins/env.c \
				built_ins/unset.c \
				built_ins/export.c \
				built_ins/cd.c \
				utils/double_array_utils.c \
				utils/env_utils.c \
				parse/tokenize/token.c \
				parse/tokenize/token_funcs.c \
				parse/tokenize/token_funcs2.c \
				parse/tokenize/define.c \
				parse/tokenize/syntax.c \
				parse/parse/make_list.c \
				parse/parse/list_functions.c \
				parse/parse/split_args.c \
				parse/test_functions.c \
				exit_funcs.c \
				# parse/tokenize/make_list.c \
				# built_ins/cd.c \

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	@make -C lib
	$(CC) -fsanitize=address $(CFLAGS) $(LIBFT) $(READLINE) $^ -o $@

obj/%.o : src/%.c
	@mkdir -p obj
	@mkdir -p obj/utils
	@mkdir -p obj/built_ins
	@mkdir -p obj/parse/tokenize
	@mkdir -p obj/parse/parse
	@mkdir -p obj/parse/expansion
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean :
	make -C lib clean
	rm -rf obj

fclean : clean
	rm -f $(LIBFT)
	rm -f $(MINISHELL)

re: fclean all

git :
	git add .
	git commit -m "automatic push"
	git push