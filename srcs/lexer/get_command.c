#include "../../include/minishell.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	free_tab(char **path_tab)
{
	int	i;

	if (!path_tab)
		return ;
	i = 0;
	while (path_tab[i])
	{
		free(path_tab[i]);
		i++;
	}
	free(path_tab);
}

char	*get_cmd(char **envp, char *cmd)
{
    char    *path;
	char	**path_tab;
	char	*tmp;
	char	*command;
	int		i;

    path = find_path(envp);
	path_tab = ft_split(path, ':');
	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			free_tab(path_tab);
			return (command);
		}
		free(command);
		i++;
	}
	free_tab(path_tab);
	return (NULL);
}

char	**get_array_execve(t_lst *lst, t_lst **s)
{
	char	**array;
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	if (!lst || !s)
	{
		array = NULL;
		return (array);
	}
	while (lst->type == 32 && lst->next)
		lst = lst->next;
	if (lst->type != -1)
		return (NULL);
	pos = lst->pos;
	while (lst->type == -1 || lst->type == 32)
	{
		if (lst->type == -1)
			i++;
		lst = lst->next;
	}
	array = malloc(sizeof(char *) * (i + 1)); //derniere case tab NULL ?  -> d ou le +1;
	lst = *s;
	while (lst->pos != pos)
		lst = lst->next;
	while (j < i)
	{
		if (lst->type == -1)
		{
			array[j] = ft_strdup(lst->data);
			j++;
		}
		lst = lst->next;
	}
	array[j] = NULL;
	return (array);
}

//concatenner les - ? pas util je pense;


void	ft_exec_cmd(t_lst *lst, char **envp, char **cmd)
{
	char	*tmp;
	int		pid;
	if (cmd == NULL || !lst)
		return ;	
	while (lst->type == 32 && lst->next && lst)
        lst = lst->next;
	tmp = get_cmd(envp, lst->data);
	if (!tmp)
	{
		ft_putstr_fd(lst->data, 1);
		ft_putstr_fd(" : command not found\n", 1);
		return ;
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("fork error\n", 1);
			return ;
		}
		if (pid == 0)
			execve(tmp, cmd, envp);
		waitpid(pid, NULL, 0);
		free(tmp);
	}
}