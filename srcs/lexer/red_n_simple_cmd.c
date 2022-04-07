#include "../../include/minishell.h"

// init le tableau de simple cmd et le tableau de redirection associe;

int    get_redirection_with_file(t_lst **s)
{
    t_lst  *lst;

    lst = *s;
    // concatener les '>' avec son fichier (sans espace)
    while (lst)
    {
        if (lst->type == '<' || lst->type == '>' || lst->type == '<' * -1 || lst->type == '>' * -1)
        {
            while (lst->next->type == 32 && lst->next)
                lst_del(s, lst->pos + 1);
            if (!lst->next || lst->next->type != -1) // check que le token qui suit le '>' soit bien un nom de fichier (qui existe ou pas)
            {
                ft_putstr_fd("syntax error near unexpected token : ", 2);
                ft_putstr_fd(lst->data, 2);
                ft_putstr_fd("\n", 2);
                return (1);
            }
            else
            {
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst_del(s, lst->pos + 1);
            }
        }
        lst = lst->next;
    }
    return (0);
}

int get_nb_red_lst(t_lst **s)
{
    t_lst   *lst;
    int     nb;

    lst = *s;
    nb = 1;
    while (lst)
    {
        if (lst->type == '|')
            nb++;
    }
    return (nb);
}

t_red   **get_red_array(t_lst **s)
{
    t_lst   *lst;
    int     size;
    t_red   **first;
    t_red   *red;

    first = ft_calloc(1, sizeof(t_red));
    red = ft_calloc(1, sizeof(t_red));
    *first = red;
    size = 0;
    lst = *s;
    while (lst)
    {
        if (lst->type == '>' || lst->type == '<' || lst->type == '<' * -1 || lst->type == '>' * -1)
            size++;
        else if (lst->type == '|')
        {
            red->type = ft_calloc(1, sizeof(int) * (size + 1));
            red->file = ft_calloc(1, sizeof(char *) * (size + 1));
            size = 0;
            red->next = ft_calloc(1, sizeof(t_red));
            red = red->next;
            red->next = NULL;
        }
        else if (lst->type == 0)
        {
            red->type = ft_calloc(1, sizeof(int) * (size + 1));
            red->file = ft_calloc(1, sizeof (char *) * (size + 1));
            size = 0;
            red->next = NULL;
        }
        lst = lst->next;
    }
    get_red_array_data(s, first);
    return (first);
}

t_red    **get_red_array_data(t_lst **s, t_red **f)
{
    t_lst   *lst;
    t_red   *red;
    int     i;

    lst = *s;
    red = *f;
    i = 0;
    while (lst)
    {
        if (lst->type == '>')
        {
            red->type[i] = lst->type;
            red->file[i] = ft_strdup(&lst->data[1]);
            i++;
            lst = lst->next;
        }
        else if (lst->type == '<')
        {
            red->type[i] = lst->type;
            red->file[i] = ft_strdup(lst->data + 1);
            i++;
            lst = lst->next;
        }
        else if (lst->type == '<' * -1)
        {
            red->type[i] = lst->type;
            red->file[i] = ft_strdup(lst->data + 2);
            i++;
            lst = lst->next;
        }
        else if (lst->type == '>' * -1)
        {
            red->type[i] = lst->type;
            red->file[i] = ft_strdup(lst->data + 2);
            i++;
            lst = lst->next;
        }
        else if(lst->type == '|' )
        {
            red->type[i] = -1;
            red->file[i] = NULL;
            i = 0;
            red = red->next;
            lst = lst->next;
        }
        else if (lst->type == 0)
        {
            red->type[i] = -1;
            red->file[i] = NULL;
            red = red->next;
            lst = lst->next;
        }
        else
            lst = lst->next;
    }
    return (f);
}

int    get_simple_cmd_array_size(t_lst **s)
{
    t_lst   *lst;
    int     size;

    size = 1;
    lst = *s;
    while (lst)
    {
        if (lst->type == '|')
            size++;
        lst = lst->next;
    }
    return (size);
}

char    **get_simple_cmd_array(t_lst **s)
{
    t_lst   *lst;
    int     size;
    char    **sc_array;
    int     i;

    lst = *s;
    size = get_simple_cmd_array_size(s) + 1; // +1 pour lq derniere case NULL du tab
    sc_array = malloc(sizeof(char *) * size);
    i = 0;
    while (lst)
    {
        if (lst->type == -1)
        {
            sc_array[i] = ft_strdup(lst->data);
            lst = lst->next;
            while (lst->type == -1 || lst->type == 32)
            {
                sc_array[i] = ft_strjoin_v2(sc_array[i], lst->data);
                lst = lst->next;
            }
            i++;
        }
        lst = lst->next;
    }
    sc_array[i] = NULL;
    return (sc_array);
}

int check_red_token(t_lst **s)
{
    t_lst *lst;

    lst = *s;
    while (lst)
    {
        if (lst->type == '|' || lst->type == '<' || lst->type == '>' || lst->type == '<' * -1 || lst->type == '>' * -1)
        {
            if (lst->next->type == '|' || lst->next->type == '<' || lst->next->type == '>' || lst->next->type == '<' * -1 || lst->next->type == '>' * -1)
            {
                ft_putstr_fd(lst->data, 1);
                ft_putstr_fd(" : syntax error near unexpected token\n", 1);
                return (1);
            }
            if (lst->next->type == 0 || lst->next == NULL)
               {
                ft_putstr_fd(lst->data, 1);
                ft_putstr_fd(" : syntax error near unexpected token\n", 1);
                return (1);
            } 
        }
        lst = lst->next;
    }
    return (0);
}

void    free_red(t_red **s)
{
    t_red   *red;

    while (*s)
    {
        red = (*s)->next;
        if ((*s)->type)
            free((*s)->type);
        if ((*s)->file)
            free((*s)->file);
        free(*s);
        *s = red;
    }
    free(*s);
    free(red);
    *s = NULL;
}