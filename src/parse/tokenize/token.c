
#include <minishell.h>
#include <parsing.h>

static void	set_token(t_list **head, t_list *list, char *input);

int	len_until_next_list(char *input)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (input[i])
	{
		if (!state && ft_isinset(input[i], "'\""))
			state = input[i];
		else if (state && input[i] == state)
			state = 0;
		if (!state && ((input[i] == '|' && input[i + 1] == '|') ||\
			(input[i] == '&' && input[i + 1] == '&')))
			return (i);
		i++;
	}
	return (i);
}

/*sets tokens according to the ENUMs defined in the header. 
returns 0 on succes.*/
void	tokenize(char *input, t_list **list)
{
	int		len;
	t_list	*new;

	len = len_until_next_list(input);
	new = list_new(len);
	list_addback(list, new);
	set_token(list, new, input);
	//print_tokens(*list, input);
}

int	is_rdr_pipe_amp(char *c)
{
	return (*c == '|' || *c == '<' || *c == '>' || (*c == '&' && *(c + 1) == '&'));
}

static int	is_closed_quote(char *input, int i)
{
	char	quote;
	int		end_quote;

	end_quote = i + 1;
	quote = input[i];
	while (input[end_quote])
	{
		if (input[end_quote] == quote)
			return (end_quote);
		end_quote += 1;
	}
	return (i + 1);
}

static void	set_token(t_list **head, t_list *list, char *input)
{
	int	i;
	int	end_quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			end_quote = is_closed_quote(input, i);
			while (i < end_quote)
				list->token[i++] = WORD;
			continue ;
		}
		else if (is_rdr_pipe_amp(input + i))
		{
			if (set_rdr_pipe_amp(list, input, &i))
			{
				list->input = ft_substr(input, 0, i);
				list->token[i] = BLANK;
				if (!list->input)
					return ;
				return (tokenize(input + i + 2, head));
			}
		}
		else if (!ft_whitespace(input[i]))
			list->token[i] = WORD;
		else
			list->token[i] = BLANK;
		i++;
	}
}
