#include "../../include/minishell.h"




// concatener les $ avec le texte qui le suit
void    get_variable(t_lst **s)
{
    t_lst   *lst;

    lst = *s;
    while (lst)
    {
        if (lst->type == '$') // && lst->next->data[0] != '\0' && lst->next)
        {
            if (lst->next->type == -1)
            { 
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst_del(s, lst->pos + 1);
                lst->type = '$';
            }
            else
            {
                lst->type = -1;
            }
        }
        lst = lst->next;
    }
}

// utils du fichier
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

//pour les variables entre double quote (avec et sans texte avant le $variable)
void    translate_variable(t_lst **s, t_env **env)
{
    t_lst   *lst;
    t_env   *tmp;
    char    *tmp2;
    int     i;

    i = 0;
    lst = *s;
    tmp2 = NULL;
    tmp = *env;
    while (lst)
    {
        if (lst->type == '$')
            get_variable_case_1(lst, tmp, s);
        else if (lst->type == -2)
            get_variable_case_2(lst, tmp, tmp2, i);
        i = 0;
        tmp = *env;
        lst = lst->next;
    }
}

// loop de la fonction du dessus pour la norme
void    get_variable_case_1(t_lst *lst, t_env *tmp, t_lst **s)
{
    while (tmp)
    {
        if (ft_strcmp(lst->data + 1, tmp->name) == 0)
        {
            if (tmp->content[0] == '\0')
                lst_del(s, lst->pos);
            else
            {
                free(lst->data);
                lst->data = ft_strdup(tmp->content);
                lst->type = -1;
            }
            break ;
        }
                tmp = tmp->next;
            }
    if (!tmp)
    {
        lst_del(s, lst->pos);
    }
}

// idem que case 1
void    get_variable_case_2(t_lst *lst, t_env *env, char *tmp2, int i)
{
    int     j;
    char    *tmp;
    
    tmp = NULL;
    j = -1;
    while (lst->data[i] != '$' && lst->data[i])
        i++;
    if (i < ft_strlen_v2(lst->data))
    {
       while (env)
        {
            if (ft_strcmp(lst->data + i + 1, env->name) == 0)
            {    
                tmp2 = malloc(sizeof(char) * i + 1);
                while(++j < i)
                    tmp2[j] = lst->data[j];
                tmp2[j] = '\0';
                free(lst->data);
                lst->data = ft_strjoin_v2(tmp2, env->content);
                break ;
            }
            env = env->next;
        }
        if (!env)
        {
            tmp = ft_strndup(lst->data, i);
            while (lst->data[++i])
            {
                if (lst->data[i] == ' ' || lst->data[i] == '$')
                    break ;
            }
            tmp2= ft_strdup(lst->data + i);
            free(lst->data);
            lst->data = ft_strjoin(tmp, tmp2);
            free(tmp);
            free(tmp2);
        }
    }
        lst->type = -1;
}

void    get_variable_in_quote(t_lst **s, t_env **envp)
{
    t_env   *env;
    t_lst   *lst;
    int     i;
    int     j;
    int     len;
    char    *tmp;
    
    env = *envp;
    lst = *s;
    i = -1;
    j = -1;
    len = 0;
    tmp = NULL;
    while (lst)
    {
        if (lst->type == -2)
        {
            while (lst->data[++j])
            {
                if (lst->data[j] == '$')
                    break ;
            }
            if (j < ft_strlen_v2(lst->data))
            {
                while (lst->data[++i])
                {
                    if (lst->data[i] == '$')
                    {
                        while (lst->data[++i])
                        {
                            if (lst->data[i] == ' ' || lst->data[i] == '$')
                                break ;
                            len++;
                        }
                        while (env)
                        {
                            if (ft_strncmp(lst->data + (i - len), env->name, len) == 0 && ft_strlen_v2(env->name) == len)
                            {
                                tmp = ft_strndup(lst->data, i - (len + 1));
                                tmp = ft_strjoin_v2(tmp, env->content);
                                tmp = ft_strjoin_v2(tmp, lst->data + i);
                                free(lst->data);
                                lst->data = ft_strdup(tmp);
                                free(tmp);
                                tmp = NULL;
                                break ;
                            }
                            else if (ft_strncmp(lst->data + (i - len), env->name, len) != 0 && env->next == NULL)
                            {
                                tmp = ft_strndup(lst->data, i - (len + 1));
                                tmp = ft_strjoin_v2(tmp, lst->data + i);
                                free(lst->data);
                                lst->data = ft_strdup(tmp);
                                free(tmp);
                                tmp = NULL;
                            }
                            env = env->next;
                        }
                        env = *envp;
                        i = -1;
                        len = 0;
                    }
                }
            }
            else
                lst->type = -1;
        }
        lst = lst->next;
    }
}

char *ft_strndup(const char *s, int n)
{
    char* new;
    
    new = malloc(sizeof(char) * (n+1));
    if (new) 
    {
        ft_strncpy(new, s, n);
        new[n] = '\0';
    }
    return (new);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}