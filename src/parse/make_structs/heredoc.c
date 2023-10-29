/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:05:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/27 17:56:18 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static char	*get_delimiter(t_list *list, int *i);
static int	set_expand(char *delimiter);
static void	heredoc(t_heredoc *doc);

void	init_struct_and_fork(t_heredoc *doc, t_list *list, int *i)
{
	doc->delimiter = get_delimiter(list, i);
	doc->expand = set_expand(doc->delimiter);
	doc->line = "";
	if (doc->expand == HEREDOC_NO_EXP)
		doc->delimiter = ft_strdel(doc->delimiter, "\"\'");
	if (pipe(doc->pipefd) < 0)
		ft_minishell_error("pipe()", "creating the pipe for heredoc", strerror(errno), errno);
	doc->pid = fork();
	if (doc->pid < 0)
		ft_minishell_error("fork()", "forking for heredoc", strerror(errno), errno);
}

int	add_heredoc(t_list *list, int *i, t_env_info *env)
{
	t_heredoc	doc;
	t_rdr		*rdr_node;
	t_exec		*cur_node;

	init_struct_and_fork(&doc, list, i);
	cur_node = exec_lstlast(list->exec);
	rdr_node = rdr_lstnew(NULL, doc.expand, 1);
	rdr_lstadd_back(&cur_node->rdr, rdr_node);
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
	return (EXIT_SUCCESS);
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
	char	*str;

	while (ft_whitespace(list->input[*i]) || list->input[*i] == '<')
		*i += 1;
	start = *i;
	while ((list->token[*i] == WORD || list->input[*i] == '\'' || list->input[*i] == '"') \
			&& list->input[*i])
		*i += 1;
	temp = ft_substr(list->input, start, *i - start);
	if (temp == NULL)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	str = ft_strjoin(temp, "\n");
	if (str == NULL)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	free (temp);
	return (str);
}
