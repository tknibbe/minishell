INCLUDE		=	-I includes -I lib/includes -I $(shell brew --prefix readline)/include
CFLAGS		=	#-Wall -Werror -Wextra
READLINE	=	-lreadline  -L $(shell brew --prefix readline)/lib
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell
LIBFT		=	lib/libft.a
SRC			=	cris_main.c \
				exit_funcs.c \
				built_ins/env.c \
				built_ins/unset.c \
				built_ins/export.c \
				built_ins/env_utils.c \
				built_ins/cd.c \
				built_ins/echo.c \
				utils/double_array_utils.c \
				utils/utils1.c \
				parse/parse.c \
				parse/tokenize/token.c \
				parse/tokenize/token_utils.c \
				parse/tokenize/syntax.c \
				parse/parse/make_list.c \
				parse/parse/list_utils.c \
				parse/parse/list_utils2.c \
				parse/parse/heredoc.c \
				parse/expansion/expander_wildcard.c \
				parse/expansion/expander.c \
				parse/expansion/expander_utils.c \
				parse/test_functions.c \
				signals/signals.c \
				exit_funcs.c \
				# parse/tokenize/make_list.c \
				# built_ins/cd.c \

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	@make -C lib
	$(CC)  $(CFLAGS) $(LIBFT) $(READLINE) $^ -o $@ -fsanitize=address

obj/%.o : src/%.c
	@mkdir -p obj
	@mkdir -p obj/utils
	@mkdir -p obj/built_ins
	@mkdir -p obj/parse/tokenize
	@mkdir -p obj/parse/parse
	@mkdir -p obj/parse/expansion
	@mkdir -p obj/execution
	@mkdir -p obj/signals
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