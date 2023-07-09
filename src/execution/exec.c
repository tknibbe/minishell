#include <minishell.h>
#include <token.h>
#include <env.h>

t_rdr	*rdr_new(char *file, int type)
{
	t_rdr	*new;

	new = malloc(sizeof(t_rdr));
	if (!new)
		ft_exit("Error: malloc failure\n", errno);
	new->file = file;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	rdr_addback(t_rdr **head, t_rdr *new)
{
	t_rdr	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
	1 = <
	2 = >
	3 = <<
	4 = >>
*/

t_rdr	*get_some_rdr(void)
{
	t_rdr *head;

	head = rdr_new("input1", 1);
	rdr_addback(&head, rdr_new("output", 2));
	rdr_addback(&head, rdr_new("output1", 2));
	rdr_addback(&head, rdr_new("output2", 2));
	rdr_addback(&head, rdr_new("output3", 2));
	return (head);
}

/*

first step in execution is redirecting as dictated by the rdr linked list

*/

void	open_file_and_dup(char *file, int flag, int to_dup)
{
	int	fd;

	if (flag == (O_WRONLY | O_CREAT | O_TRUNC))
		fd = open(file, flag, 0644);
	else
		fd = open(file, flag);
	if (fd < 0)
	{
		write(2, "bash: ", 7);
		perror(file);
		exit(errno);
	}
	if (dup2(fd, to_dup) < 0)
	{
		perror("bash: dup2()");
		exit(errno);
	}
}

void	redirection(t_rdr *r)
{
	while (r)
	{
		if (r->type == 1) // <
			open_file_and_dup(r->file, O_RDONLY, STDIN_FILENO);
		else if (r->type == 2) // >
			open_file_and_dup(r->file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		r = r->next;
	}
}

void	execute_command(t_exec *t)
{
	redirection(t->rdr);
	printf("yo\n");
	execve(t->cmd[0], t->cmd, NULL);
	exit(1);
	//printf("did it work?\n");
}

void	test_exec(char **env)
{
	
	pid_t pid = fork();
	if (pid == 0)
	{
		t_exec	*t = ft_lstnew();
		t->cmd = ft_split("program", ' ');
		t->env = env;
		t->rdr = get_some_rdr();
		execute_command(t);
	}
	wait(NULL);
	return ;
}