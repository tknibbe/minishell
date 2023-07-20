
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
	char			**env;
	char			*and_or; // "&&" > "||" > "$OR" > "$AND"
	t_exec			*next;
}					t_exec;

typedef struct s_data
{
	int		*token;
	t_exec	*list;
}			t_data;

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
	OR,
	AND,
};

//PARSE.C
void	parse_input(char **input, t_ally *all);

//TOKEN.C
int		tokenize(char *input, t_data **data);
//TOKEN_UTILS.C
int		whitespace(char c);
void	set_rdr_pipe_amp(t_data *data, char *input, int *i);
void	left(t_data *data, char *input, int *i);
void	right(t_data *data, char *input, int *i);
int		is_alphanumeric(char c);
//MAKE_LIST.c
void	parse(char *input, t_data **data);

//SYNTAX.C
int		check_syntax(t_data *data, char **input);

//LIST_FUNCTIONS.C
void	exec_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*exec_lstnew(void);

void	rdr_lstadd_back(t_rdr **lst, t_rdr *new);
t_rdr	*rdr_lstnew(void);

//SPLIT_ARGS.C
char	**split_args(char *input, t_data *data);

//SET_RDRS.C
void	set_rdrs(t_data **data, char *input, int nodes);

//SET_CMDS.C
void	set_cmds(t_data **data, char *input, int node_amount);
char	*trim_quotes(char *str);

//TEST_FUNCTIONS.C
void	print_class(int num);
void	print_test(t_data *data, char *input);
void	print_tokens(t_data *data, char *input);
void	print_whole_list(t_data *data, char *input);
#endif