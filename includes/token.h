/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:08:40 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/30 16:04:48 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_data
{
	int	*token;
}		t_data;

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
};

//TOKEN.C
int		set_tokens(char *input, t_data *data);
//TOKEN_FUNCS.C
int		count_quote(char *input, t_data *data, char c);
void	find_pipe(t_data *data, char *input);
void	find_append_redirect(t_data *data, char *input);

//TOKEN_FUNCS2.C
void	find_exec(t_data *data, char *input, int i);
void	find_options(t_data *data, char *input);
void	set_rest_to_str(t_data *data, char *input);
int		whitespace(char c);

//DEFINE.C
void	find_define(t_data *data, char *input);


#endif