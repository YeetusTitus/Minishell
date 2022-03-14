#include "../../include/minishell.h"

void    get_token_in_qoute(t_lst **s)
{
    t_lst   *lst;

    lst = *s;
    while (lst->data != 0 || lst->next)
    {
       if (lst->data[0] == '\'')
        {
            lst = lst->next;
            lst_del(s, lst->pos - 1);
            while (lst->next->data[0] != '\'')
            {
                if (lst->type == 0)
                    break ;
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst_del(s, lst->next->pos);
            }
            lst_del(s, lst->pos + 1);
        }
        else if (lst->data[0] == '\"')
        {
            lst = lst->next;
            lst_del(s, lst->pos - 1);
            while (lst->next->data[0] != '\"')
            {
                if (lst->type == 0)
                    break ;
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst_del(s, lst->next->pos);
            }
            lst_del(s, lst->pos + 1);
        }
        if (lst->type == 0)
            break ;
        lst = lst->next;
    }
    return ;
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	free_tab(char **path_tab)
{
	int	i;

	i = 0;
	while (path_tab[i])
	{
		free(path_tab[i]);
		i++;
	}
	free(path_tab);
}

char	*get_command(char *path, char *cmd)
{
	char	**path_tab;
	char	*tmp;
	char	*command;
	int		i;

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
