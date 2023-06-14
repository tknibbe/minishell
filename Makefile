# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:11:29 by tknibbe           #+#    #+#              #
#    Updated: 2023/06/14 16:09:37 by tknibbe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE		=	-I includes
#CFLAGS		=	-Wall -Werror -Wextra
READLINE	=	-lreadline
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell
SRC			=	cris_main.c \
				parse_and_exec.c \

$(MINISHELL) : $(OBJ_F)
	@echo ""
	$(CC) $(CFLAGS) $(READLINE) $^ -o $@

obj/%.o : src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean :
	rm -rf obj

fclean : clean
	rm $(MINISHELL)

git :
	git add .
	git commit -m "automatic push"
	git push