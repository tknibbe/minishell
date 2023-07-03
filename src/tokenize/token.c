/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:18:15 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/30 16:05:13 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

static void	init_token(t_data *data, int len);
static void	find_squote(t_data *data, char *input);
static void	find_dquote(t_data *data, char *input);
static void	find_dollar(t_data *data, char *input);

void	print_class(int	num)
{
	//norm error not to forget to remove
	if (num == SQUOTE)
		printf("single quote: ");
	else if (num == DQUOTE)
		printf("double quote: ");
	else if (num == DOLLO)
		printf("Dollarsign  : ");
	else if (num == REDIRLEFT)
		printf("redir left  : ");
	else if (num == REDIRRIGHT)
		printf("redirright  : ");
	else if (num == APPLEFT)
		printf("append left : ");
	else if (num == APPRIGHT)
		printf("append right: ");
	else if (num == PIPESYMBOL)
		printf("pipe        : ");
	else if (num == EXEC)
		printf("executable  : ");
	else if (num == OPTION)
		printf("option      : ");
	else if (num == INPUT)
		printf("input       : ");
	else if (num == EQUALS)
		printf("equals      : ");
	else if (num == VARIABLE)
		printf("variable    : ");
	else if (num == STRING)
		printf("string      : ");
	else
		printf("undefined %d: ", num);
}

void print_test(t_data *data, char *input)
{
	int	i = 0; //remove func later
	int	num;

	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		num = data->token[i];
		print_class(data->token[i]);
		while (data->token[i] == num && input[i])
		{
			printf("%c", input[i]);
			i++;
		}
		printf("\n");
	}
}
//cat -e  "hallo $variable" | ls -la | << < >> > 'hallo $variable'

/*sets tokens according to the ENUMs defined in the header. 
returns 0 on succes.*/
int	set_tokens(char *input, t_data *data)
{
//loops through string EVERY function. could be faster :/
//still needs to find "= signs on define and make sure the variable name is valid
	int	i;

	i = 0;
	init_token(data, ft_strlen(input));
	find_squote(data, input);
	find_dquote(data, input);
	find_dollar(data, input);
	find_pipe(data, input);
	find_append_redirect(data, input);
	find_exec(data, input, 0);
	find_options(data, input);
	set_rest_to_str(data, input);
	find_define(data, input);
	print_test(data, input); // test ONLY
	return (0);
}

/*finds and replaces everything after $ 
(until whitepace or end quote (")) with DOLLO variable*/
static void	find_dollar(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && data->token[i] != SQUOTE)
		{
			while (input[i] != TAB && input[i] != SPACE && input[i] != '"' && input[i])
			{
				data->token[i] = DOLLO;
				i++;
			}
		}
		i++;
	}
}

/*finds and replaces everything in " " with DQUOTE variable
will not do anything on a single quote or quote that is not in a pair*/
static void	find_dquote(t_data *data, char *input)
{
	int	i;
	int	open;
	int	numquote;

	i = 0;
	open = 0;
	numquote = count_quote(input, data, '"');
	if (numquote % 2 == 1)
		numquote -= 1;
	while (input[i] && numquote)
	{
		if (input[i] == '"' && open == 0)
			open = 1;
		if (open && data->token[i] == UNDEFINED)
			data->token[i] = DQUOTE;
		i++;
		if (input[i] == '"' && open == 1 && data->token[i] == UNDEFINED)
		{
			data->token[i] = DQUOTE;
			open = 0;
			numquote -= 2;
			i++;
		}
	}
}

/*finds and replaces everything in ' ' with SQUOTE variable
will not do anything on a single quote or quote that is not in a pair*/
static void	find_squote(t_data *data, char *input)
{
	int	i;
	int	open;
	int	numquote;

	i = 0;
	open = 0;
	numquote = count_quote(input, data, 39);
	if (numquote % 2 == 1)
		numquote -= 1;
	while (input[i] && numquote)
	{
		if (input[i] == 39 && open == 0)
			open = 1;
		if (open)
			data->token[i] = SQUOTE;
		i++;
		if (input[i] == 39 && open == 1)
		{
			data->token[i] = SQUOTE;
			open = 0;
			numquote -= 2;
			i++;
		}
	}
}

static void	init_token(t_data *data, int len)
{
	int	i;

	data->token = malloc(sizeof(int) * len);
	if (!data->token)
		ft_exit("Malloc error\n", errno);
	i = 0;
	while (i < len)
	{
		data->token[i] = UNDEFINED;
		i++;
	}
}
