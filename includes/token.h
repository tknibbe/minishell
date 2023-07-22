
#ifndef TOKEN_H
# define TOKEN_H

# include <minishell.h>

typedef struct s_exec		t_exec;
typedef struct s_rdr		t_rdr;
typedef struct s_minishell	t_ally;

typedef struct s_rdr
{
	char			*file; // file name
	int				type; // <, >, <<, >>
	t_rdr			*next;
}					t_rdr;

typedef struct s_exec
{
	char			**cmd;
	t_rdr			*rdr;
	t_exec			*next;
}					t_exec;

typedef struct s_list
{
	int				*token;
	char			*input;
	int				and_or;
	t_exec			*exec;
	struct s_list	*next;
}					t_list;

# define TAB '	'
# define SPACE ' '

enum	e_token
{
	BLANK,
	WORD,
	REDIRLEFT,
	REDIRRIGHT,
	APPLEFT,
	APPRIGHT,
	PIPESYMBOL,
	BRACE_OPEN,
	BRACE_CLOSE,
	AND,
	OR,
};

//PARSE.C
void	parse_input(char **input, t_ally *all);

//TOKEN.C
void	tokenize(char *input, t_list **list);
//TOKEN_UTILS.C
int		whitespace(char c);
int		set_rdr_pipe_amp(t_list *list, char *input, int *i);
void	left(t_list *list, char *input, int *i);
void	right(t_list *list, char *input, int *i);
//MAKE_LIST.c
void	parse(char *input, t_list **list);

//SYNTAX.C
int		check_syntax(t_list *list, char **input);

//LIST_FUNCTIONS.C
void	exec_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*exec_lstnew(void);

void	rdr_lstadd_back(t_rdr **lst, t_rdr *new);
t_rdr	*rdr_lstnew(void);

//SPLIT_ARGS.C
char	**split_args(char *input, t_list *list);

//SET_RDRS.C
void	set_rdrs(t_list **list, char *input, int nodes);

//SET_CMDS.C
void	set_cmds(t_list **list, char *input, int node_amount);
char	*trim_quotes(char *str);

//TEST_FUNCTIONS.C
void	print_class(int num);
void	print_test(t_list *list, char *input);
void	print_tokens(t_list *list, char *input);
void	print_whole_list(t_list *list, char *input);

void	list_addback(t_list **head, t_list *new);
t_list	*list_new(int len	);

#endif