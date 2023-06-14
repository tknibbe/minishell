SRC			=	cris_main.c
INCLUDE		=	-I includes
CFLAGS		=	-Wall -Werror -Wextra
READLINE	=	-lreadline
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
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