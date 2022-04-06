#include "../../include/minishell.h"

void    ft_exec(t_red **s, char **simple_cmd, char **envp)
{
    int     i;
    t_red   *red;
    int     save_out;
    int     save_in;
    int     fd;

    red = *s;
    i = 0;
    save_out = dup(1);
    save_in = dup(0);
    while (simple_cmd[i])
    {
        if (i == 0 && !simple_cmd[i + 1]) 
            case_1_ft_exec(red, simple_cmd, i, envp, save_out);
        else if (i == 0 && simple_cmd[i])
            fd = case_2_ft_exec(red, simple_cmd, i, envp, save_out);
        else if (i > 0 && !simple_cmd[i + 1])
            case_3_ft_exec(red, simple_cmd, i, envp, fd, save_out);
        else if (i > 0 && simple_cmd[i + 1])
            fd = case_4_ft_exec(red, simple_cmd, i, envp, fd, save_out);
        i++;
    }
    while (wait(NULL) != -1)
        ;
    dup2(save_out, 1);
    dup2(save_in, 0);
    close(save_out);
    close(save_in);
}

void    case_1_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out)
{
    char    *path;
    char    **cmd;
    int     pid;
    int     fd;
    t_red   *tmp;

    tmp = red;
    fd = 0;
//    red_dup_mannager(red, fd, 2);
    pid = fork();
    if (pid == 0)
    {
        cmd = ft_split(simple_cmd[i], ' ');
        path = get_cmd(envp, cmd[0]);
	    if (!path)
	    {
            dup2(save_out, 1);
            close(save_out);            
	    	ft_putstr_fd(cmd[0], 1);
	    	ft_putstr_fd(" : command not found\n", 1);
	        exit(1);
	    }
        else
            execve(path, cmd, envp);
    }
    else
        waitpid(pid, NULL, 0);
}

int case_2_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out)
{
    int     ret;
    int     pid;
    char    *path;
    char    **cmd;
    int     fd[2];
    t_red   *tmp;

    tmp = red;
    pipe(fd);
    ret = fd[0];
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
//        red_dup_mannager(red, fd[0], 0);
        cmd = ft_split(simple_cmd[i], ' ');
        path = get_cmd(envp, cmd[0]);
	    if (!path)
	    {
            dup2(save_out, 1);
            close(save_out);
	    	ft_putstr_fd(cmd[0], 1);
	    	ft_putstr_fd(" : command not found\n", 1);
	        exit(1);
	    }
       else
           execve(path, cmd, envp);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
//        waitpid(pid, NULL, 0);
    }
    return(ret);
}

void    case_3_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int fd_ret, int save_out)
{
    int     pid;
    char    *path;
    char    **cmd;
    t_red   *tmp;

    tmp = red;
    dup2(fd_ret, 0);
    close(fd_ret);
    pid = fork();
    if (pid == 0)
    {
//        fd = red_dup_mannager(red, fd, 1);
        cmd = ft_split(simple_cmd[i], ' ');
        path = get_cmd(envp, cmd[0]);
        if (!path)
        {
            dup2(save_out, 1);
            close(save_out);            
        	ft_putstr_fd(cmd[0], 1);
        	ft_putstr_fd(" : command not found\n", 1);
            exit(1);
        }
        else
            execve(path, cmd, envp);
    }
//    else
//        waitpid(pid, NULL, 0);
}

int case_4_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int fd_ret, int save_out)
{
    int     ret;
    int     pid;
    char    *path;
    char    **cmd;
    int     fd[2];
    t_red   *tmp;

    tmp = red;
//    fd_ret = red_dup_mannager(red, fd_ret, 0);
    dup2(fd_ret, 0);
    close(fd_ret);
    pipe(fd);
    ret = fd[0];
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        cmd = ft_split(simple_cmd[i], ' ');
        path = get_cmd(envp, cmd[0]);
        if (!path)
        {
            dup2(save_out, 1);
            close(save_out);            
        	ft_putstr_fd(cmd[0], 1);
        	ft_putstr_fd(" : command not found\n", 1);
            exit(1);
        }
        else
            execve(path, cmd, envp); 
    }
    else
    {
        close(fd[1]);
        close(fd[0]);
//        waitpid(pid, NULL, 0);
    }
    return (ret);
}

int red_dup_mannager(t_red *red, int fd_ret, int i)
{
    int j;
    int fd;

    j = 0;
    while (red->type[j] != -1)
    {
        if (red->type[j] == '>')
        {
            fd = open(red->file[j], O_TRUNC | O_CREAT | O_RDWR, 0644);
            if (i == 1)
                fd_ret = fd;
            dup2(fd, 1);
            close(fd);
        }
        else if (red->type[j] == '<')
        {
            if (i == 0)
                fd_ret = fd;
            fd = open(red->file[j], O_RDONLY);
            dup2(fd, 0);
            close(fd);
        }
        else if (red->type[j] == '>' * -1)
        {
            if (i == 1)
                fd_ret = fd;
            fd = open(red->file[j],  O_APPEND | O_CREAT | O_RDWR, 0644);
            dup2(fd, 1);
            close(fd);
        }
        // faire aussi pour '<<'
        j++;
    }
    return(fd_ret);
}