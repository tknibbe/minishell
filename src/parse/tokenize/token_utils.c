
#include <parsing.h>

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	set_rdr_pipe_amp(t_list *list, char *input, int *i)
{
	if (input[*i] == '&' && input[*i + 1] == '&')
		return (1);
	else if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
			return (1);
		list->token[*i] = PIPESYMBOL;
	}
	else
	{
		if (input[*i] == '<')
			left(list, input, i);
		else if (input[*i] == '>')
			right(list, input, i);
	}
	return (0);
}

void	left(t_list *list, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		list->token[*i] = HEREDOC;
		list->token[*i + 1] = HEREDOC;
		*i += 1;
	}
	else
		list->token[*i] = REDIRLEFT;
}

void	right(t_list *list, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		list->token[*i] = APPEND;
		list->token[*i + 1] = APPEND;
		*i += 1;
	}
	else
		list->token[*i] = REDIRRIGHT;
}
