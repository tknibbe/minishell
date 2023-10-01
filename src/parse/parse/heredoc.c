/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:05:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/01 13:58:17 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static char	*get_delimiter(char *input, int *i);
static int	set_expand(char *delimiter);
static void	heredoc(t_heredoc *doc);

void	init_struct_and_fork(t_heredoc *doc, char *input, int *i)
{
	doc->delimiter = get_delimiter(input, i);
	doc->expand = set_expand(doc->delimiter);
	doc->status = 0;
	doc->line = "";
	if (doc->expand == HEREDOC_NO_EXP)
		doc->delimiter = ft_strdel(doc->delimiter, "\"\'");
	if (pipe(doc->pipefd) < 0)
		ft_exit("Error creating pipe", errno);
	doc->pid = fork();
	if (doc->pid < 0)
		ft_exit("Error creating child process", errno);
}

void	add_heredoc(char *input, t_list *list, int *i)
{
	t_heredoc	doc;
	t_rdr		*rdr_node;
	t_exec		*cur_node;

	init_struct_and_fork(&doc, input, i);
	cur_node = exec_lstlast(list->exec);
	rdr_node = rdr_lstnew(NULL, doc.expand, 1);
	rdr_lstadd_back(&cur_node->rdr, rdr_node);
	if (doc.pid == 0)
		heredoc(&doc);
	wait(&doc.status);
	if (WIFSIGNALED(doc.status) && WEXITSTATUS(doc.status) != 0) // TODO :add exit code in here if heredoc is terminated with CTRL+C
	{
		free(doc.delimiter);
		// list->exit_code = 1; // make env exit code 130 here
		return ;
	}
	close(doc.pipefd[1]);
	while (doc.line)
	{
		doc.line = get_next_line(doc.pipefd[0]);
		if (doc.line)
			t_str_lstadd_back(&rdr_node->file, t_str_lstnew(doc.line));
	}
	free(doc.delimiter);
}

static void	heredoc(t_heredoc *doc)
{
	unset_echo();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(doc->pipefd[0]);
	doc->line = NULL;
	while (1)
	{
		write(1, "> ", 2);
		doc->line = get_next_line(STDIN_FILENO);
		if (!doc->line)
			break ;
		if (!ft_strncmp(doc->delimiter, doc->line, ft_strlen(doc->delimiter)))
			break ;
		write(doc->pipefd[1], doc->line, ft_strlen(doc->line));
	}
	close(doc->pipefd[1]);
	free(doc->line);
	exit(0);
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
