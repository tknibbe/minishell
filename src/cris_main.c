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

/*	create everything that needs to be initialized here and store it in all	*/

	all = malloc(sizeof(t_ally));
	if (!all)
		ft_exit("Malloc error\n", errno);
	all->list = malloc(sizeof(t_list));
	if (!all->list)
		ft_exit("Malloc error\n", errno);
	all->list->next = NULL;
	all->list->exit_code = 0;
	all->list->exec = NULL;
	all->env = env_init(envp);
	return (all);
}

void	tymon(t_ally *all, char *input)
{
	//pre_parse(input, all);
	all->list = parse_input(input);
	//executor(all->list, all->env);
	int i = 0;
	//env(all->env->head);
	//while (all->env->head)
	//	printf("%s\n", all->env->env[i++]);
	//char *path = get_env("PATH", all->env);
	//printf("path: %s\n", path);
	// print_whole_list(all->list);
	//printf("pipeline exited with code : %d\n", all->list->exit_code);
	//free (*input);
	// exit(0);
	//leaks();
}

void	run_shell(t_ally *all, char *prompt)
{
	char	*string;

	set_signals_inter();
	string = readline(prompt);
	set_signals_non_inter();
	if (!string)
		exit(0);
	if (*string)
	{
		add_history(string);
		if (ft_strncmp(string, "exit", 4) == 0)
			exit(0);
		tymon(all, string);
	}
	free(string);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ally	*all;

	if (argc != 1)
		ft_exit("just ./minishell is enough\n", 1);
	all = minishell_init(envp);
	while (1)
		run_shell(all, PROMPT);
	//free(prompt);
}
