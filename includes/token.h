/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 16:08:40 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/09 17:40:38 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

// typedef struct s_exec	t_exec;

// typedef struct s_exec
// {
// 	char	**cmd;
// 	int		rd; // -1 : no- redirection | 0 outgoing rd | 1 ingoing | 2 ingoing && outgoing
// 	char	*file;
// 	t_exec	*next;
// }			t_exec;

typedef struct s_rdr
{
	char			*file; // file name
	int				type; // <, >, <<, >>
	struct s_rdr	*next;
}					t_rdr;

typedef struct s_exec
{
	char			**cmd;
	char			**env;
	t_rdr			*rdr;
	struct s_exec	*next;
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
	SQUOTE,
	DQUOTE,
	DOLLO,
	REDIRLEFT,
	REDIRRIGHT,
	APPLEFT,
	APPRIGHT,
	PIPESYMBOL,
	EXEC,
	OPTION,
	INPUT,
	VARIABLE,
	EQUALS,
	STRING,
	SEMICOLON,
};

//TOKEN.C
int		set_tokens(char *input, t_data **data);
//TOKEN_FUNCS.C
int		count_quote(char *input, t_data *data, char c);
void	find_pipe_and_semicolon(t_data *data, char *input);
void	find_append_redirect(t_data *data, char *input);

//TOKEN_FUNCS2.C
void	find_exec(t_data *data, char *input, int i);
void	find_options(t_data *data, char *input);
void	set_rest_to_str(t_data *data, char *input);
int		whitespace(char c);
void	trim_BLANK(t_data *data, char *input);

//DEFINE.C
void	find_define(t_data *data, char *input);

//MAKE_LIST.c
void	parse(char *input, t_data **data);

//SYNTAX.C
int		check_syntax(t_data *data, char *input);

//TEST_FUNCTIONS.C
void	print_class(int	num);
void 	print_test(t_data *data, char *input);
void	print_tokens(t_data *data, char *input);

//LIST_FUNCTIONS.C
void	ft_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*ft_lstnew(void);

//SPLIT_ARGS.C
char	**split_args(char *input, t_data *data);

#endif