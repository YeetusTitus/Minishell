#include "../../include/minishell.h"

void    dup_mannager(char **simple_cmd, t_red **s, char **envp)
{
    t_red   *red;
    int     i;
    int     j;
    int     save_out;
    int     save_in;

    red = *s;
    i = 0;
    j = 0;
    save_out = dup(1);
    save_in = dup(0);
    while (simple_cmd[i] && )
    {
        while (red->type[j] != -1)
        {
            if (red->type[j] == '>')
                greater_red();
            else if (red->type[j] == '<')
                smaller_red();
            else if (red->type[j] == '>' * -1)
                great_greater_red();
            else if (red->type[j] == '<' * -1)
                small_smaller_red();
            j++;
        }
        if (simple_cmd[i + 1])
            ft_exec_pipe(simple_cmd[i], envp);
        else if (simple_cmd[i + 1] == NULL)
            ft_exec();
        if (simple_cmd[i] == NULL)
            break ;
        j = 0;
        red = red->next;
        i++;
    }
    restore_fd();
}

void    greater_red(t_red *red, int j)
{
    int fd;

    fd = open(red->file[j], O_TRUNC | O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        ft_putstr_fd(red->file[j], 1);
        ft_putstr_fd(" : Can't open file or directory", 1);
    }
    dup2(fd, 1);
    close(fd);
}

void    smaller_red(t_red *red, int j)
{
    int fd;

    fd = open(red->file[j], O_RDWR);
    if (fd == -1)
    {
        ft_putstr_fd(red->file[j], 1);
        ft_putstr_fd(" : Can't open file or directory", 1);
    }
    dup2(fd, 0);
    close(fd);
}

void    great_greater_red(t_red *red, int j)
{
    int fd;

    fd = open(red->file[j], O_APPEND | O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        ft_putstr_fd(red->file[j], 1);
        ft_putstr_fd(" : Can't open file or directory", 1);
    }
    dup2(fd, 1);
    close(fd);
}

////////////////////////////////////////////////////////////

void    small_smaller_red()
{

}

void    restore_fd(int  save)
{

}

void    ft_exec_pipe(int save, char *cmd, char **envp)
{
    int     fd[2];
    int     pid;
    int     pid2;
    char    *tmp;
    char    **cmd;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        cmd = ft_split(cmd, ' ');
        close(fd[0]);
        tmp = get_cmd(envp, cmd[0]);
	    if (!tmp)
	    {
	    	ft_putstr_fd(lst->data, 1);
	    	ft_putstr_fd(" : command not found\n", 1);
		    return ; // ?? return ou continue?
	    }
        execve(tmp, ft_split(cmd, ' '), envp);
    }
    else
    {
        pid2 = fork();
        dup2(1, save);
        close(save);
    }
    if (pid2 == 0)
    {
        close(fd[0]);
        execve();
    }
}


void    ft_exec(void)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        execve();
    }
    else
    {

    }
}