/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:05:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/28 17:46:45 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delimiter(t_list *list, int *i);
static int	set_expand(char *delimiter);
static void	heredoc(t_heredoc *doc);

void	init_struct_and_fork(t_heredoc *doc, t_list *list, int *i)
{
	char	*swapstring;

	doc->delimiter = get_delimiter(list, i);
	doc->expand = set_expand(doc->delimiter);
	swapstring = ft_strdel(doc->delimiter, "\'\"()");
	if (!swapstring)
		ft_minishell_error("Malloc()", NULL, strerror(errno), errno);
	free (doc->delimiter);
	doc->delimiter = ft_strjoin(swapstring, "\n");
	if (!doc->delimiter)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	free(swapstring);
	doc->line = "";
	if (pipe(doc->pipefd) < 0)
		ft_minishell_error("pipe()", "creating the pipe for heredoc", \
			strerror(errno), errno);
	doc->pid = fork();
	if (doc->pid < 0)
		ft_minishell_error("fork()", "forking for heredoc", \
			strerror(errno), errno);
}

int	add_heredoc(t_list *list, int *i, t_env_info *env)
{
	t_heredoc	doc;
	t_rdr		*rdr_node;

	init_struct_and_fork(&doc, list, i);
	rdr_node = rdr_lstnew(NULL, doc.expand, 1);
	rdr_lstadd_back(&exec_lstlast(list->exec)->rdr, rdr_node);
	if (doc.pid == 0)
		heredoc(&doc);
	wait(&doc.status);
	if (WIFSIGNALED(doc.status))
	{
		env->last_exit_status = 130;
		return (free(doc.delimiter), EXIT_FAILURE);
	}
	close(doc.pipefd[1]);
	while (doc.line)
	{
		doc.line = get_next_line(doc.pipefd[0]);
		if (doc.line)
			t_str_lstadd_back(&rdr_node->file, t_str_lstnew(doc.line));
	}
	free(doc.delimiter);
	close(doc.pipefd[0]);
	return (EXIT_SUCCESS);
}

static void	heredoc(t_heredoc *doc)
{
	unset_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
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
		free(doc->line);
	}
	close(doc->pipefd[1]);
	exit(0);
}

static int	set_expand(char *d)
{
	int		i;
	int		quote;

	i = 0;
	while (d[i])
	{
		while (d[i] && d[i] != '\'' && d[i] != '"')
			i++;
		if (!d[i])
			break ;
		quote = i++;
		while (d[i] && d[i] != d[quote])
			i++;
		if (d[i] == d[quote])
			return (HEREDOC_NO_EXP);
		i = quote + 1;
	}
	return (HEREDOC_EXP);
}

static char	*get_delimiter(t_list *list, int *i)
{
	int		start;
	char	*temp;

	while (list->token[*i] == BLANK || list->input[*i] == '<')
		*i += 1;
	start = *i;
	while ((list->token[*i] == WORD || list->input[*i] == '\'' \
	|| list->input[*i] == '"' || list->input[*i] == '(' || \
	list->input[*i] == ')') && list->input[*i])
		*i += 1;
	temp = ft_substr(list->input, start, *i - start);
	if (temp == NULL)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	return (temp);
}
