/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:05:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/25 11:44:23 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

//i needs to be set to the end of the delimiter
static char	*get_delimiter(char *input, int *i);
static int	set_expand(char *delimiter);
static char	*trim_char(char *line, char *c);
static char *backslash_check(char *line);

void	add_heredoc(char *input, t_exec *node, int *i)
{
	char	*delimiter;
	char	*line;
	int		expand;

	delimiter = get_delimiter(input, i);
	expand = set_expand(delimiter);
	if (expand == HEREDOC_NO_EXP)
		delimiter = ft_strdel(delimiter, "\"\'");
	line = NULL;
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		line = backslash_check(line);
		if (!ft_strncmp(delimiter, line, ft_strlen(delimiter)))
			break ;
		line = trim_char(line, "\n");
		rdr_lstadd_back(&node->rdr, rdr_lstnew(line, expand));
	}
	free(line);
}

static int	set_expand(char *d)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (d[i])
	{
		if (d[i] == '"' || d[i] == '\'')
		{
			quote = d[i];
			while (d[i + j])
			{
				j++;
				if (d[i + j] == quote)
					return (HEREDOC_NO_EXP);
			}
		}
		j = 0;
		i++;
	}
	return (HEREDOC);
}

static char	*get_delimiter(char *input, int *i)
{
	int		start;
	char	*temp;
	char	*str;

	while (whitespace(input[*i]) || input[*i] == '<')
		*i += 1;
	start = *i;
	while (!whitespace(input[*i]) && input[*i])
		*i += 1;
	temp = ft_substr(input, start, *i - start);
	if (temp == NULL)
		ft_exit("Malloc fail\n", errno);
	str = ft_strjoin(temp, "\n");
	free (temp);
	return (str);
}
static char *backslash_check(char *line)
{
	char *str;
	char *temp;

	if (line[ft_strlen(line) - 2] == '\\')
	{
		line = trim_char(line, "\\\n");
		write(1, ">", 1);
		str = get_next_line(STDIN_FILENO);
		temp = ft_strjoin(line, str);
		free (line);
		free (str);
		return (temp);
	}
	return (line);
}

static char	*trim_char(char *line, char *c)
{
	char	*ret;

	ret = ft_strtrim(line, c);
	free(line);
	return (ret);
}
