/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:05:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/08 12:30:08 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

static char	*get_delimiter(char *input, int *i);
static int	set_expand(char *delimiter);
void		heredoc(char *input, t_exec *node, int *i, t_heredoc *doc);

void	init_struct(t_heredoc *doc, char *input, int *i)
{
	doc->delimiter = get_delimiter(input, i); // TODO figure out cleaner way to get delimiter and expand to be able to insert it in node in parent
	doc->expand = set_expand(doc->delimiter);
	if (doc->expand == HEREDOC_NO_EXP)
		doc->delimiter = ft_strdel(doc->delimiter, "\"\'");
	if (pipe(doc->pipefd) < 0)
		ft_exit("Error creating pipe", errno);
	doc->pid = fork();
	if (doc->pid < 0)
		ft_exit("Error creating child process", errno);
}

void	add_heredoc(char *input, t_exec *node, int *i)
{
	t_heredoc	doc;
	t_rdr		*rdr_node;

	init_struct(&doc, input, i);
	rdr_node = rdr_lstnew(NULL, doc.expand, 1);
	if (doc.pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		heredoc(input, node, i, &doc); // get exit status
		exit(9);
	}
	close(doc.pipefd[1]);
	doc.line = "";
	while (doc.line)
	{
		doc.line = get_next_line(doc.pipefd[0]);
		if (doc.line)
			char_lstadd_back(&rdr_node->file, char_lstnew(doc.line));
	}
	//wait(NULL);
	//rdr in exec;
	//free_struct
	rdr_lstadd_back(&node->rdr, rdr_node);
	//wexitstatus
}

void	heredoc(char *input, t_exec *node, int *i, t_heredoc *doc) // int *i can be int i
{
	close(doc->pipefd[0]);
	doc->line = NULL;
	while (1)
	{
		write(1, ">", 1);
		doc->line = get_next_line(STDIN_FILENO);
		if (!doc->line)
			break ;
		if (!ft_strncmp(doc->delimiter, doc->line, ft_strlen(doc->delimiter)))
			break ;
		write(doc->pipefd[1], doc->line, ft_strlen(doc->line));
	}
	close(doc->pipefd[1]);
	free(doc->line);
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

	while (ft_whitespace(input[*i]) || input[*i] == '<')
		*i += 1;
	start = *i;
	while (!ft_whitespace(input[*i]) && input[*i])
		*i += 1;
	temp = ft_substr(input, start, *i - start);
	if (temp == NULL)
		ft_exit("Malloc fail\n", errno);
	str = ft_strjoin(temp, "\n");
	free (temp);
	return (str);
}
