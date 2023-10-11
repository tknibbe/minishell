
#ifndef PARSING_H 
# define PARSING_H

# include <minishell.h>

typedef struct s_exec		t_exec;
typedef struct s_rdr		t_rdr;
typedef struct s_minishell	t_ally;
typedef struct s_str		t_str;
typedef struct s_list		t_list;
typedef struct s_env_info	t_env_info;

typedef struct s_rdr
{
	t_str			*file;
	int				type;
	t_rdr			*next;
}					t_rdr;

typedef struct s_exec
{
	t_list			*subshell;
	t_str			*cmd;
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

typedef struct s_heredoc
{
	int		pid;
	int		expand;
	int		status;
	int		pipefd[2];
	char	*line;
	char	*delimiter;
}				t_heredoc;

//# define TAB '	'
# define SPACE ' '

enum	e_token
{
	BLANK,
	WORD,
	REDIRLEFT,
	REDIRRIGHT,
	APPEND,
	HEREDOC,
	HEREDOC_NO_EXP,
	PIPESYMBOL,
	BRACE_OPEN,
	BRACE_CLOSE,
	AND,
	OR,
};

//PARSE.C
t_list	*parse_input(char *input, t_env_info *env);

//TOKEN.C
void	tokenize(t_list *list);
//TOKEN_UTILS.C
void	set_rdr_pipe_amp(t_list *list, char *input, int *i);
void	left(t_list *list, char *input, int *i);
void	right(t_list *list, char *input, int *i);
//MAKE_LIST.c
int		parse(char *input, t_list *list, t_env_info *env);
int		ft_whitespace(char c);

//SYNTAX.C
//int		check_syntax(t_list *list, char **input);
int		check_syntax(t_list *list, t_env_info *env);

//LIST_utils.C
void	exec_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*exec_lstnew(void);
t_exec	*exec_lstlast(t_exec *lst);
void	rdr_lstadd_back(t_rdr **lst, t_rdr *new);

//LIST_UTILS2.c
t_rdr	*rdr_lstnew(char *str, int type, int heredoc);
void	t_str_lstadd_back(t_str **lst, t_str *new);
t_str	*t_str_lstnew(char *str);

//HEREDOC.C
int		add_heredoc(char *input, t_list *list, int *i, t_env_info *env);

//SPLIT_PIPELINES.C
int		split_pipelines(char *input, t_list **list);

//SPLIT_UTILS
void	t_listadd_back(t_list **lst, t_list *new);
t_list	*t_listnew(void);

//subshell.c
void	set_subshell(t_list *list, char *input);
int		sub_count(char c, int want);
int		is_subshell(int token);
t_list	*add_subshell(char *input, t_list *list, int *i, t_env_info *env);

//SYNTAX
int		is_redirect(int c);
int		is_control_op(int token);
int		no_valid_token(t_list *list);
int		ft_syntax_error(char c, int token);
int		op_amount_check(t_list *list, int i);
int		start_check(t_list *list);
int		brace_check(t_list *list, int *i);

//TEST_FUNCTIONS.C
void	print_class(int num);
void	print_test(t_list *list, char *input);
void	print_tokens(t_list *list, int len);
void	print_t_exec(t_list *list);
void 	print_whole_list(t_list *list);
#endif