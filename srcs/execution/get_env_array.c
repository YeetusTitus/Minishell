#include "../../include/minishell.h"

int get_env_array_size(t_env **env)
{
    t_env   *tmp;
    int     i;

    i = 0;
    tmp = *env;
    while (tmp)
    {
        if (tmp->content)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

char    **get_env_array(t_env **env)
{
    t_env   *tmp;
    char    **envp;
    int     i;

    i = 0;
    tmp = *env;
    envp = malloc(sizeof(char *) * (get_env_array_size(env) + 1));
    while (tmp)
    {
        envp[i] = ft_strdup(tmp->name);
        envp[i] = ft_strjoin_v2(envp[i], tmp->content);
        i++;
        tmp = tmp->next;
    }
    envp[i] = NULL;
    return (envp);
}