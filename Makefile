# **************************************************************************** #
#                                                                              #
<<<<<<< HEAD
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tknibbe <tknibbe@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/14 15:11:29 by tknibbe       #+#    #+#                  #
#    Updated: 2023/06/29 16:32:17 by cvan-sch      ########   odam.nl          #
=======
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:11:29 by tknibbe           #+#    #+#              #
#    Updated: 2023/06/30 14:18:15 by tknibbe          ###   ########.fr        #
>>>>>>> 3e07408d06511042916c526588c5790e525f29fe
#    Updated: 2023/07/03 14:16:07 by tknibbe          ###   ########.fr        #
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
<<<<<<< HEAD
				exit_funcs.c \
				built_ins/cd.c \
				built_ins/env.c \
				built_ins/unset.c \
				utils/double_array_utils.c \
				built_ins/export.c
=======
				tokenize/token.c \
				tokenize/token_funcs.c \
				tokenize/token_funcs2.c \
				tokenize/define.c \
				tokenize/make_list.c \
				exit_funcs.c \
				#built_ins/cd.c \
>>>>>>> 3e07408d06511042916c526588c5790e525f29fe

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	@make -C lib
	$(CC) -fsanitize=address $(CFLAGS) $(LIBFT) $(READLINE) $^ -o $@

obj/%.o : src/%.c
<<<<<<< HEAD
	mkdir -p obj
	mkdir -p obj/built_ins
	mkdir -p obj/utils
=======
	@mkdir -p obj
	@mkdir -p obj/built_ins
	@mkdir -p obj/tokenize
>>>>>>> 3e07408d06511042916c526588c5790e525f29fe
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