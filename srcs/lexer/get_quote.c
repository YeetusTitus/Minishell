#include "../../include/minishell.h"

// lire les data entre quote et les enleve si necessaire (ex : '' '')
void    get_qoute(t_lst **s)
{
    t_lst   *lst;
    int     pos;

    lst = *s;
    pos = 1;
    while (lst->next)
    {
        if (lst->type == '"' && lst->next->type != '"' && lst->next->type != 0)
        {

            lst = lst->next;
            lst_del(s, lst->pos - 1);
            while (lst->next->data)
            {
                if (lst->next->type == '"')
                    break ;
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst->type = -2;
                lst_del(s, lst->pos + 1);
            }
            if (lst->next->type != 0)
                lst_del(s, lst->pos + 1);
            lst = lst->next;
        }
        else if (lst->type == '"' && lst->next->type == '"')
        {
            lst = lst->next;
            lst_del(s, lst->pos - 1);
            if (lst->next->type == 0)
            {
                lst_del(s, lst->pos);
                break ;
            }
            else
            {
                lst = lst->next;
                lst_del(s, lst->pos - 1);
            }
        }
        else if (lst->type == '\'' && lst->next->type != '\'' && lst->next->type != 0)
        {
            lst = lst->next;
            lst_del(s, lst->pos - 1);
            while (lst->next->data)
            {
                if (lst->next->type == '\'')
                    break ;
                lst->data = ft_strjoin_v2(lst->data, lst->next->data);
                lst->type = -1;
                lst_del(s, lst->pos + 1);
            }
            if (lst->next->type != 0)
                lst_del(s, lst->pos + 1);
            lst = lst->next;
        }
        else if (lst->type == '\'' && lst->next->type == '\'')
        {
            lst = lst->next;
            lst_del(s, lst->pos - 1);
            if (lst->next->type == 0)
            {
                lst_del(s, lst->pos);
                break ;
            }
            else
            {
                lst = lst->next;
                lst_del(s, lst->pos - 1);
            }
        }
        else if ((lst->type == '\'' || lst ->type == '"') && lst->next->type == 0)
        {
            lst_del(s, lst->pos);
            break ;
        }
        else if (lst->type == '\'')
        {
            if (lst->next->type == 0)
            lst_del(s, lst->pos);
            else
            {
                lst = lst->next;
                lst_del(s, lst->pos - 1);
            }
        }
        else if (lst->type == '"')
        {
            if (lst->next->type == 0)
            lst_del(s, lst->pos);
            else
            {
                lst = lst->next;
                lst_del(s, lst->pos - 1);
            }
        }
        while (lst->next)
        {
            if (lst->type == '\'')
                break ;
            if (lst->type == '"')
                break ;
            lst = lst->next;
        }
    }    
}


