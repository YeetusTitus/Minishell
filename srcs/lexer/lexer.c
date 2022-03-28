#include "../../include/minishell.h"

// decouper la chaine de characteres tapee apres le prompt
int  *get_enum_data(char *str)
{
    int *array;
    int i;

    array = malloc(sizeof(int) * (ft_strlen_v2(str) + 1));
    i = 0;
    while (str[i])
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
            array[i] = CHAR_DOLLAR;
        else if (str[i] == '=')
            array[i] = CHAR_RPARENTHESIS;
        else
           array[i] = CHAR_GENERAL;
        i++;
    }
    array[i] =  CHAR_NULL;
    return (array);
}


// mettre les token dans une liste chainee 
t_lst  **get_data_in_lst(char *str)
{
    t_lst  *lst;
    t_lst  **first;
    int     *array;
    int     i;
    int     start;
    int     pos;

    pos = 1;
    start = 0;
    i = 0;
    array = get_enum_data(str);
    lst = ft_calloc(1, sizeof(t_lst));
    /*lst = malloc(sizeof(t_lst));
    lst->next = NULL;
    lst->prev = NULL;
*/    first = malloc(sizeof(t_lst *));
    *first = lst;
    while(array[i])
    {
        while (array[i] == array[i + 1] && (array[i] == -1 || array[i] == ' '))
            i++;
            lst->type = array[i];
            if (array[i] == '|' && array[i + 1] == '|')
            {
                i++;
                lst->type = '|' * -1;
            }
            else if (array[i] == '&' && array[i + 1] == '&')
            {
                i++;
                lst->type = '&' * -1;
            }
            else if (array[i] == '<' && array[i + 1] == '<')
            {
                i++;
                lst->type = '<' * -1;
            }
            else if (array[i] == '>' && array[i + 1] == '>')
            {
                i++;
                lst->type = '>' * -1;
            }
            if (array[i] == 0)
            {
                lst->type = 0;
                lst->data = ft_strdup("\0");
                lst->next = NULL;
                break ;
            }
            else
            {
                i++;
                lst->data = ft_substr(str, start, i - start);
                lst->pos = pos++;
                lst->next = ft_calloc(1, sizeof(t_lst));
                lst->next->prev = lst;
                lst = lst->next;
                lst->next = NULL;
                start = i;
            }
    }
    free(array);
    return (first);
}



// la loop qui permet d afficher le prompt et de garder l historique des commandes tapees
void    ft_loop(char **envp)
{
/*    
    envp[0] = NULL;
    char *str = readline("$> ");
    int *arr = get_enum_data(str);
    int i = 0;

    while (arr[i])
    {
        printf("%d\n", arr[i]);
        i++;
    }
        printf("%d\n", arr[i]);
*/    

     
    
    char    *str;
    t_lst   **s;
    t_lst   *lst;
    int     i = 0;
    t_env   *env[2];
    char **tempo;
    create_env(env, envp);
    while (1)
    {
        str = readline("$> ");
        if (ft_strlen(str) > 0)
            add_history(str);
        s = get_data_in_lst(str);
        lst = *s;
        get_qoute(s);
        get_variable(s);
        get_variable_in_quote(s, env);
        translate_variable(s, env);
        lst = *s;
        tempo = get_array_execve(lst, s);
        ft_exec_cmd(lst, envp, tempo);
        i = 0;
        if (ft_strlen(str) > 0)
        {
            free(str);
            if ((*s))
                free_lst(s);
            free(s);
        }
        if (tempo)
            free_tab(tempo);
    }
    free_env(env);
	system("leaks minishell");
}
