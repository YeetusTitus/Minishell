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
        else  if (str[i] == ' ')
            array[i] = CHAR_WHITESPACE;
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
//        else if (str[i] == '=')
//            array[i] = CHAR_RPARENTHESIS;
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
    char    *str;
    t_lst   **s;
    t_env   *env[2];
    t_red   **red;
    char    **truc;
    int     save;
    int     i;
    int     pid;

    create_env(env, envp);
    while (1)
    {
        truc = NULL;
        red = NULL;
        s = NULL;
        i = 0;
        str = readline("$> ");
        if (ft_strlen(str) > 0)
            add_history(str);
                                 // lexer
        s = get_data_in_lst(str);
        get_qoute(s);
        get_variable(s);
        get_variable_in_quote(s, env);
        translate_variable(s, env);
                                //parsing
        i += check_pipe_place(s);
        if (i == 0)
        {
            i += get_redirection_with_file(s);
            if_only_red(s);
            red = get_red_array(s);
            truc = get_simple_cmd_array(s);
        }
        if (i == 0)
        {
            if (truc[0])
                ft_exec(red, truc, envp);
            else
            {
                wait(NULL);
                pid = fork();
                if (pid == 0)
                {
                    save = dup(1);
                    dup_mannager_out(*red, 1, save, NULL);
                    exit(0);
                }
                else
                    wait(NULL);
            }
        }
        free(str);
        free_lst(s);
        free_tab(truc);
        free_red(red);
    }
    free_env(env);
	system("leaks minishell");
}
