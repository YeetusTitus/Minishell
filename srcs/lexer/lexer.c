#include "../../include/minishell.h"

// decouper la chaine de characteres tapee apres le prompt
int  *get_enum_data(char *str)
{
    int *array;
    int i;

    array = malloc(sizeof(int) * ft_strlen(str) + 1);
    i = -1;
    while (str[++i])
    {
        if (str[i] == '|')
            array[i] = CHAR_PIPE;
        else if (str[i] == '&')
            array[i] = CHAR_AMPERSAND;
        else if (str[i] == '\'')
            array[i] = CHAR_QOUTE;
        else if (str[i] == '\"')
            array[i] = CHAR_DQUOTE;
        else  if (str[i] == ';')
            array[i] = CHAR_SEMICOLON;
        else  if (str[i] == ' ')
            array[i] = CHAR_WHITESPACE;
        else  if (str[i] == '\\')
            array[i] = CHAR_ESCAPESEQUENCE;
        else if (str[i] == '>')
            array[i] = CHAR_GREATER;
        else if (str[i] == '<')
            array[i] = CHAR_LESSER;
        else if (str[i] == '*')
            array[i] = CHAR_WILDCART;
        else if (str[i] == '(')
            array[i] = CHAR_LPARENTHESIS;
        else if (str[i] == ')')
            array[i] = CHAR_RPARENTHESIS;
        else if (str[i] == '$')
            array[i] = CHAR_RPARENTHESIS;
        else if (str[i] == '=')
            array[i] = CHAR_RPARENTHESIS;
        else
           array[i] = CHAR_GENERAL;
    }
    array[i] =  CHAR_NULL;
    return (array);
}

// mettre les token dans une liste chainee 
t_lst  **get_data_in_lst(char *str)
{
    t_lst  *lst;
    t_lst  *tmp;
    t_lst  **first;
    int     *array;
    int     i;
    int     start;
    int     pos;

    pos = 1;
    start = 0;
    i = 0;
    array = get_enum_data(str);
    lst = malloc(sizeof(t_lst));
    lst->next = NULL;
    lst->prev = NULL;
    first = malloc(sizeof(t_lst *));
    *first = lst;
    while(array[i])
    {
        while (array[i] == array[i + 1] && (array[i] == -1 || array[i] == ' '))
            i++;
        i++;
        lst->data = ft_substr(str, start, i - start);
        lst->pos = pos++;
        lst->type = array[i];
        tmp = malloc(sizeof(t_lst));
        tmp->prev = lst;
        tmp->next = NULL;
        lst->next = tmp;
        lst = lst->next;
        start = i;
    }
    free(array);
    return (first);
}

void    free_lst(t_lst **s)
{
    t_lst  *lst;

    while (*s)
    {
        lst = (*s)->next;
        free((*s)->data);
        free(*s);
        *s = lst;
    }
    free(*s);
    free(lst);
    *s = NULL;
}

// la loop qui permet d afficher le prompt et de garder l historique des commandes tapees
void    ft_loop(char **envp)
{
    char    *str;
    t_lst   **s;
    t_lst   *lst;
    char    *tmp;
    tmp = envp[0];

    str = readline("$> ");
    if (ft_strlen(str) > 1)
        add_history(str);
    s = get_data_in_lst(str);
    get_token_in_qoute(s);
    lst = *s;
    while (lst->next)
    {
        printf("%s--   %d\n", lst->data, lst->pos);
        lst = lst->next;
    }
 //   tmp = get_command(envp, s);
 //   lst = *s;
    free_lst(s);
    free(s);
    free(str);
}
