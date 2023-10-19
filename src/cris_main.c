#include <minishell.h>
#include <built_ins.h>
#include <exec.h>

void	leaks(void)
{
	system("leaks -q minishell");
}

t_ally	*minishell_init(char *envp[])
{
	t_ally	*all;

	all = malloc(sizeof(t_ally));
	if (!all)
		ft_exit("Malloc error\n", errno);
	all->list = NULL;
	all->env = env_init(envp);
	return (all);
}

void	run_single_command(t_ally *all)
{
	char *string;

	string = get_next_line(STDIN_FILENO);
	if (!string)
		exit(0);
	if (strncmp(string, "", 1))
	{
		add_history(string);
		all->list = parse_input(string, all->env);
		if (all->list)
			executor(all->list, all->env);
	}
	free(string);
}

void	run_shell(t_ally *all)
{
	char	*string;

	set_signals_inter();
	string = readline(PROMPT);
	set_signals_non_inter();
	if (!string)
		exit(0);
	if (strncmp(string, "", 1))
	{
		add_history(string);
		all->list = parse_input(string, all->env);
		if (all->list)
			executor(all->list, all->env);
	}
	free(string);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ally	*all;

	if (argc != 1)
		ft_exit("just ./minishell is enough\n", 1);
	argv = NULL;
	all = minishell_init(envp);
	if (!isatty(STDIN_FILENO))
	{
		run_single_command(all);
		exit(all->env->last_exit_status);
	}
	while (1)
		run_shell(all);
	return (EXIT_FAILURE);
}
