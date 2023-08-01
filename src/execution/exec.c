#include <minishell.h>
#include <token.h>
#include <built_ins.h>

// t_rdr	*get_some_rdr(void)
// {
// 	t_rdr *head;

// 	head = rdr_new("program.c", 1);
// 	rdr_addback(&head, rdr_new("output", 2));
// 	rdr_addback(&head, rdr_new("output1", 2));
// 	rdr_addback(&head, rdr_new("output2", 2));
// 	rdr_addback(&head, rdr_new("output3", 2));
// 	rdr_addback(&head, rdr_new("Makefile", 1));
// 	return (head);
// }

/*

first step in execution is redirecting as dictated by the rdr linked list

*/

void	open_file_and_dup(char *file, int flag, int to_dup)
{
	int	fd;

	if (flag == (O_WRONLY | O_CREAT | O_TRUNC))
		fd = open(file, flag, 0644);
	else if (flag == (O_RDONLY))
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
		if (r->type == REDIRLEFT) // <
		{
			//printf("type = <\n");
			open_file_and_dup(r->file, O_RDONLY, STDIN_FILENO);
		}
		else if (r->type == REDIRRIGHT) // >
		{
			//printf("type = >\n");
			open_file_and_dup(r->file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		}
		r = r->next;
	}
}

void	execute_command(t_exec *t)
{
	int	i = 0;
	int	node_amnt = 0;
	//t_exec *list = t;
	//while (list)
	//{
	//	t_rdr	*rdr = list->rdr;
	//	printf("\nnode %d\n", node_amnt);
	//	printf("[\n");
	//	printf("CMD: ");
	//	// while (list->cmd[i])
	//	// {
	//	// 	printf("%s, ", list->cmd[i]);
	//	// 	i++;
	//	// }
	//	i = 0;
	//	printf("\n");
	//	printf("RDR: ");
	//	while (rdr)
	//	{
	//		printf("{%s} [%d], ", rdr->file, rdr->type);
	//		rdr = rdr->next;
	//	}
	//	node_amnt++;
	//	printf("\n]\n\n");
	//	list = list->next;
	//}
	redirection(t->rdr);
	// write(2, "redirection succesfull?\n", 25);
	execve(t->cmd[0], t->cmd, NULL);
	//write(2, "execve failed\n", 15);
	exit(1);
	//printf("did it work?\n");
}

// void	test_exec(char **env)
// {
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		t_exec	*t = ft_lstnew();
// 		t->cmd = ft_split("/bin/cat", ' ');
// 		t->env = env;
// 		t->rdr = get_some_rdr();
// 		execute_command(t);
// 	}
// 	wait(NULL);
// 	return ;
// }