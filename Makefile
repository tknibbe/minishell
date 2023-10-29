
INCLUDE			=	-I includes -I lib/includes -I $(shell brew --prefix readline)/include
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS			+=	-g -fsanitize=address
READLINE		=	-lreadline -L $(shell brew --prefix readline)/lib
MINISHELL		=	minishell
LIBFT			=	lib/libft.a

#----------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#	SOURCE FILES AND OBJECT DIRECTORIES
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------#

OBJ_DIR			=	obj obj/utils obj/built_ins obj/execution obj/signals \
					obj/parse obj/parse/expansion obj/parse/make_structs obj/parse/split_pipelines \
					obj/parse/syntax obj/parse/tokenize
BUILTINS		=	cd.c echo_pwd_exit.c env_builtins.c env_export_unset.c env_init.c env_utils.c
EXECUTION		=	executor_utils.c executor.c heredoc_expansion.c pathfinder.c redirect.c
SIGNALS			=	interactive.c non_interactive.c
UTILS			=	double_array_utils.c free_structs.c t_char_utils.c utils1.c
EXPANSION		=	expander_utils.c expander_wc_utils.c expander_wildcard.c expander_wordsplit.c expander_ws_utils.c expander.c
MAKE_STRUCTS	=	heredoc.c list_utils.c list_utils2.c make_list.c
SPLIT_PIPELINES	=	list_utils.c split_pipelines.c
SYNTAX			=	syntax_utils.c syntax_utils2.c syntax.c
TOKENIZE		=	subshell.c token_utils.c token.c
PARSE			=	parse_main.c test_functions.c $(addprefix tokenize/, $(TOKENIZE)) $(addprefix syntax/, $(SYNTAX)) $(addprefix make_structs/, $(MAKE_STRUCTS)) \
					$(addprefix split_pipelines/, $(SPLIT_PIPELINES)) $(addprefix expansion/, $(EXPANSION))
SRC				=	super_duper_awesome_tymon_and_cris_main.c $(addprefix parse/, $(PARSE)) $(addprefix utils/, $(UTILS)) \
					$(addprefix signals/, $(SIGNALS)) $(addprefix execution/, $(EXECUTION)) $(addprefix built_ins/, $(BUILTINS))
OBJ_F			=	$(SRC:%.c=obj/%.o)

#----------------------------------------------------------------------------------------------------------------------------------------------------------------------#

all : $(MINISHELL)

$(MINISHELL) : $(OBJ_F)
	@make -C lib
	$(CC)  $(CFLAGS) $(READLINE) $^ -o $@ $(LIBFT)

obj/%.o : src/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean :
	make -C lib clean
	rm -rf obj

fclean : clean
	rm -f $(LIBFT)
	rm -f $(MINISHELL)

re: fclean all
