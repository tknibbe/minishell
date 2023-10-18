/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/18 12:24:24 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_new_input(t_list *list, t_env_info *env)
{
	char	*new_str;
	char	*str;

	str = readline("> ");
	if (!str)
		return (ft_syntax_error(' ', -1));
	new_str = ft_strjoin(list->input, str);
	free(list->input);
	free(str);
	free(list->token);
	free(list->exec);
	list->input = new_str;
	tokenize(list);
	check_syntax(list, env);
	return (EXIT_SUCCESS);
}

static int	control_op_check(t_list *list, int *i, t_env_info *env)
{
	int	j;
	int	token;

	j = *i;
	token = list->token[*i];
	if (!list->input[*i + 1])
		return (add_new_input(list, env));
	if (op_amount_check(list, *i))
		return (ft_syntax_error(' ', list->token[*i]));
	while (list->token[*i] == token && list->input[*i + 1])
		*i += 1;
	while (list->token[*i] == BLANK && list->input[*i + 1])
		*i += 1;
	if (list->token[*i] == WORD || is_redirect(list->token[*i]) \
		|| list->token[*i] == BRACE_OPEN)
	{
		return (EXIT_SUCCESS);
	}
	return (ft_syntax_error(' ', list->token[*i]));
}

static int	rdr_check(t_list *list, int *i)
{
	int	temp;

	temp = *i;
	while (list->token[temp] == list->token[*i] && list->input[*i])
		*i += 1;
	while (list->token[*i] == BLANK && list->input[*i])
		*i += 1;
	if (!list->input[*i])
	{
		return (ft_syntax_error(list->input[*i], 0));
	}
	if (list->token[*i] != WORD)
	{
		return (ft_syntax_error(' ', list->token[*i]));
	}
	return (EXIT_SUCCESS);
}

static int	syntax_loop(t_list *list, int *i, t_env_info *env)
{
	if (is_redirect(list->token[*i]))
	{
		if (rdr_check(list, i))
			return (EXIT_FAILURE);
	}
	else if (is_control_op(list->token[*i]))
	{
		if (control_op_check(list, i, env))
			return (EXIT_FAILURE);
	}
	else if (list->token[*i] == BRACE_OPEN)
	{
		if (brace_check(list, i))
			return (EXIT_FAILURE);
		*i += 1;
	}
	else
		*i += 1;
	return (EXIT_SUCCESS);
}

int	check_syntax(t_list *list, t_env_info *env)
{
	int	i;
	int	prev_token;

	i = 0;
	prev_token = 0;
	if (no_valid_token(list))
	{
		env->last_exit_status = 0;
		return (EXIT_FAILURE);
	}
	if (start_check(list))
	{
		env->last_exit_status = 2;
		return (EXIT_FAILURE);
	}
	while (list->input[i])
	{
		if (syntax_loop(list, &i, env))
		{
			env->last_exit_status = 2;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}