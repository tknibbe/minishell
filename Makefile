# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:11:29 by tknibbe           #+#    #+#              #
#    Updated: 2023/06/28 15:26:52 by tknibbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE		=	-I includes -I lib/includes
#CFLAGS		=	-Wall -Werror -Wextra
READLINE	=	-lreadline
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell
LIBFT		=	lib/libft.a
SRC			=	cris_main.c \
				parse_and_exec.c \
				history.c \
				built_ins/cd.c 
				token.c \
				token_funcs.c \
				exit_funcs.c \

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	make -C lib
	$(CC) $(CFLAGS) $(LIBFT) $(READLINE) $^ -o $@

obj/%.o : src/%.c
	mkdir -p obj
	mkdir -p obj/built_ins
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