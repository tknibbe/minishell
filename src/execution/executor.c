#include <minishell.h>
#include <expansion.h>
#include <built_ins.h>
#include <parsing.h>

	// big loop that loops through all conditionals
		// we can ignore token and input so best to free and set to null as soon as possible
		// after execution depending of the and_or variable continue or not
		// we store latest exit number ^
		// t_list = next
	// for every big loop we need a pipeline executor
		// set up pipes redirects
		// then check for subshell and cmd
	// the expanding happens always in the childprocess

#define OR 0
#define AND 1

t_list	*next_pipe_line(t_list *current)
{
	printf("free current node");
	if (!current->next)
		return (NULL);
	if (!(!current->exit_code && current->and_or || current->exit_code && !current->and_or))
	{
		printf("and next node\n");
		return (current->next->next);
	}
	printf("\n");
	return (current->next);
}

int	exec_pipe_line(t_exec *exec)
{
	int	p[2];
	int	fd;
	int	pid;

	while (exec)
	{
		set_pipe(p);
		pid = fork();
		execute_child(pid, exec, p);
		execute_parrent(p);
	}
	// create a pipe
	// fork process
	// child
		//execute process
	// parrent
		//close everything dup and start exec next
	// repeat
}

void	executor(t_ally *all)
{
	t_list	*pipe_line;

	pipe_line = all->list;
	while (pipe_line)
	{
		printf("free and nullify token and input variable.\n");
		pipe_line->exit_code = exec_pipe_line(pipe_line->exec);
		pipe_line = next_pipeline(pipe_line);
	}
}
