#include "../../include/minishell.h"

int	ft_strlen_v2(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_v2(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*str;

	if (!s1)
		return (NULL);
    if (!s2)
        return (s1);
	i1 = ft_strlen_v2(s1);
	i2 = ft_strlen_v2(s2);
	str = malloc(sizeof(char) * (i1 + i2 + 1));
	if (!(str))
		return (NULL);
	i1 = 0;
	i2 = 0;
	while (s1[i1])
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
		str[i1++] = s2[i2++];
	str[i1] = 0;
    free(s1);
	return (str);
}

int	lstsize(t_lst **s)
{
	int	    nb;
    t_lst   *lst;

    lst = *s;
	nb = 0;
	while (lst)
	{
		nb++;
		lst = lst->next;
	}
	return (nb);
}


int lst_del(t_lst **s, int pos)
{
    int     i;
    t_lst   *lst;
    t_lst   *to_del;

    lst = *s;
    i = 0;
    if (lstsize(s) == 0)
        return (-1);
    if (pos == 1)
    {
        to_del = lst;
        lst = lst->next;
        *s = lst;
    }
    else if (pos == lstsize(s))
    {
        while (lst->next)
            lst = lst->next;
        to_del = lst;
        lst->prev->next = NULL;
    }
    else 
    {
        while (++i < pos)
            lst = lst->next;
        to_del = lst;
        lst->prev->next = lst->next;
        lst->next->prev = lst->prev;
    }
    free(to_del->data);
    free(to_del);
    get_lst_pos(s);
    return (0);
}

t_lst   **get_lst_pos(t_lst **s)
{
    t_lst   *lst;
    int     i;

    i = 1;
    lst = *s;
    while (lst)
    {
        lst->pos = i++;
        lst = lst->next;
    }
    return (s);
}

void    del_prev(t_lst *lst, t_lst **s)
{
    lst = lst->next;
    lst_del(s, lst->pos - 1);
}

void    free_lst(t_lst **s)
{
    t_lst  *lst;

    while (*s)
    {
        lst = (*s)->next;
        if ((*s)->data)
            free((*s)->data);
        free(*s);
        *s = lst;
    }
    free(*s);
    free(lst);
    *s = NULL;
}

void    add_lst(t_lst *lst)
{
    t_lst   *tmp;

    tmp = malloc(sizeof (t_lst));
    tmp->prev = lst;
    tmp->next = NULL;
}