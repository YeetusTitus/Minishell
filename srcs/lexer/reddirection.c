#include "../../include/minishell.h"

int check_ambigous_redirect(t_red **s)
{
    t_red   *red;
    int     i;
    int     j;

    red = *s;
    i = 0;
    j = 0;
    while (red)
    {
        while (red->file[i])
        {
            if (ft_strlen(red->file[i]) < 1)
            {
                ft_putstr_fd(" : ambigous redirect\n", 1);
                return(1);
            }
            while(red->file[i][j])
            {
                while (red->file[i][j] == ' ')
                    j++;
                while (red->file[i][j] != ' ' && red->file[i][j])
                    j++;
                if (red->file[i][j] == ' ')
                {
                    ft_putstr_fd(red->file[i], 1);
                    ft_putstr_fd(" : ambiguous redirect\n", 1);
                    return (1);
                }
                j++;
            }
        j = 0;
        i++;
        }
        red = red->next;
    }
    return (0);
}

void    ft_exec(t_red **s, char **simple_cmd, char **envp)
{
    int     i;
    t_red   *red;
    int     save_out;
    int     save_in;

    red = *s;
    i = 0;
    save_out = dup(1);
    save_in = dup(0);
    while (simple_cmd[i])
    {
        if (i == 0 && !simple_cmd[i + 1]) 
            case_1_ft_exec(red, simple_cmd, i, envp, save_out);
        else if (i == 0 && simple_cmd[i])
            case_2_ft_exec(red, simple_cmd, i, envp, save_out);
        else if (i > 0 && !simple_cmd[i + 1])
            case_3_ft_exec(red, simple_cmd, i, envp, save_out);
        else if (i > 0 && simple_cmd[i + 1])
            case_4_ft_exec(red, simple_cmd, i, envp, save_out);
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
    pid = fork();
    if (pid == 0)
    {
        dup_mannager_out(red, 1);
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
}

void    case_2_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out)
{
    int     pid;
    char    *path;
    char    **cmd;
    int     fd[2];
    t_red   *tmp;


    tmp = red;
    pipe(fd);
    dup2(fd[1], 1);
    close(fd[1]);
    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        close(fd[0]);
        dup_mannager_out(red, 1);
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
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
    }
}

void    case_3_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out)
{
    int     pid;
    char    *path;
    char    **cmd;
    t_red   *tmp;

    tmp = red;
    dup2(save_out, 1);
    close(save_out);
    pid = fork();
    if (pid == 0)
    {
        dup_mannager_out(red, 1);
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
        close(0);
}

void    case_4_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out)
{
    int     pid;
    char    *path;
    char    **cmd;
    int     fd[2];
    t_red   *tmp;

    tmp = red;
    pipe(fd);
    dup2(fd[1], 1);
    close(fd[1]);
    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        close(fd[0]);
        dup_mannager_out(red, 1);
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
        dup2(fd[0], 0);
        close(fd[0]);
    }
}


void    dup_mannager_out(t_red *red, int i)
{
    int j;
    int fd;
    int fdpipe[2];

    fd = -1;
    j = 0;
    while (red->type[j] != -1)
    {
        if (red->type[j] == '>')
        {
            fd = open(red->file[j], O_TRUNC | O_CREAT | O_RDWR, 0644);
            dup2(fd, 1);
            close(fd);
        }
        else if (red->type[j] == '>' * -1)
        {
            fd = open(red->file[j],  O_APPEND | O_CREAT | O_RDWR, 0644);
            dup2(fd, 1);
            close(fd);
        }
        else if (red->type[j] == '<')
        {
            fd = open(red->file[j], O_RDONLY);
            if (fd < 0)
            {
                ft_putstr_fd(red->file[j], 1);
                ft_putstr_fd(" : No such file or directory\n", 1);
                if (i == 0)
                    return ;
                else
                    exit(1);
            }
        }
/*        else if (red->type[j] == '<' * -1)
        {
            pipe(fdpipe);

        }
*/        j++;
    }
}


int red_dup_mannager(t_red *red, int fd_ret, int i)
{
    int j;
    int fd;

    fd = -1;
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
            fd = open(red->file[j],  O_APPEND | O_TRUNC | O_CREAT | O_RDWR, 0644);
            dup2(fd, 1);
            close(fd);
        }
        // faire aussi pour '<<'
        j++;
    }
    return(fd_ret);
}