INCLUDE		=	-I includes -I lib/includes -I $(shell brew --prefix readline)/include
CFLAGS		=	-Wall -Werror -Wextra 
CFLAGS		+=	-g -fsanitize=address 
READLINE	=	-lreadline  -L $(shell brew --prefix readline)/lib
OBJ_F		=	$(SRC:%.c=obj/%.o)
MINISHELL	=	minishell
LIBFT		=	lib/libft.a
SRC			=	cris_main.c \
				exit_funcs.c \
				built_ins/env_builtins.c \
				built_ins/env_export_unset.c \
				built_ins/env_init.c \
				built_ins/env_utils.c \
				built_ins/cd.c \
				built_ins/exit.c \
				built_ins/echo.c \
				utils/double_array_utils.c \
				utils/t_char_utils.c \
				utils/utils1.c \
				utils/free_structs.c \
				parse/split_pipelines/split_pipelines.c \
				parse/split_pipelines/list_utils.c \
				parse/tokenize/token.c \
				parse/tokenize/token_utils.c \
				parse/tokenize/subshell.c \
				parse/syntax/syntax.c \
				parse/syntax/syntax_utils.c \
				parse/syntax/syntax_utils2.c \
				parse/parse_main.c \
				parse/make_structs/make_list.c \
				parse/make_structs/list_utils.c \
				parse/make_structs/list_utils2.c \
				parse/make_structs/heredoc.c \
				parse/expansion/expander_wildcard.c \
				parse/expansion/expander.c \
				parse/expansion/expander_wordsplit.c \
				parse/expansion/expander_utils.c \
				parse/expansion/expander_ws_utils.c \
				parse/expansion/expander_wc_utils.c \
				signals/interactive.c \
				signals/non_interactive.c \
				exit_funcs.c \
				execution/executor.c \
				execution/redirect.c \
				execution/pathfinder.c \
				execution/executor_utils.c \
				parse/test_functions.c \
				#test.c \
				# parse/tokenize/make_list.c \
				# built_ins/cd.c \

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	@make -C lib
	$(CC)  $(CFLAGS) $(READLINE) $^ -o $@ $(LIBFT)

obj/%.o : src/%.c
	@mkdir -p obj
	@mkdir -p obj/utils
	@mkdir -p obj/built_ins
	@mkdir -p obj/parse/split_pipelines
	@mkdir -p obj/parse/tokenize
	@mkdir -p obj/parse/make_structs
	@mkdir -p obj/parse/expansion
	@mkdir -p obj/parse/syntax
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
