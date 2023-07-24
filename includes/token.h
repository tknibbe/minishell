
#ifndef TOKEN_H
# define TOKEN_H

# include <minishell.h>

typedef struct s_exec		t_exec;
typedef struct s_rdr		t_rdr;
typedef struct s_minishell	t_ally;
typedef struct s_char		t_char;

typedef struct s_rdr
{
	char			*file;
	int				type;
	t_rdr			*next;
}					t_rdr;

typedef struct s_exec
{
	t_char			*cmd;
	t_rdr			*rdr;
	t_exec			*next;
}					t_exec;

typedef struct s_list
{
	int				*token;
	char			*input;
	char			*and_or;
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
	APPRIGHT,
	HEREDOC,
	HEREDOC_NO_EXP,
	PIPESYMBOL,
	BRACE_OPEN,
	BRACE_CLOSE,
	AND,
	OR,
};

//PARSE.C
void	parse_input(char **input, t_ally *all);

//TOKEN.C
int		tokenize(char *input, t_list **list);
//TOKEN_UTILS.C
int		whitespace(char c);
void	set_rdr_pipe_amp(t_list *list, char *input, int *i);
void	left(t_list *list, char *input, int *i);
void	right(t_list *list, char *input, int *i);
int		is_alphanumeric(char c);
//MAKE_LIST.c
void	parse(char *input, t_list *list);

//SYNTAX.C
int		check_syntax(t_list *list, char **input);

//LIST_utils.C
void	exec_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*exec_lstnew(void);

void	rdr_lstadd_back(t_rdr **lst, t_rdr *new);

//LIST_UTILS2.c
t_rdr	*rdr_lstnew(char *str, int type);
void	char_lstadd_back(t_char **lst, t_char *new);
t_char	*char_lstnew(char *str);

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
#endif