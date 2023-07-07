/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:40 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/07 11:37:31 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_exec	t_exec;

typedef struct s_exec
{
	char 	**cmd;
	int		rd; // -1 : no- redirection | 0 outgoing rd | 1 ingoing
	char	*file;
	t_exec	*next;
}			t_exec;

typedef struct s_data
{
	int		*token;
	t_exec	*list;
}		t_data;

# define TAB '	'
# define SPACE ' '

enum	e_token
{
	UNDEFINED,
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
void	trim_undefined(t_data *data, char *input);

//DEFINE.C
void	find_define(t_data *data, char *input);

//MAKE_LIST.c
void	parse(char *input, t_data **data);

#endif