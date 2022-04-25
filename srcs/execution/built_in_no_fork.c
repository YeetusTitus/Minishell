#include "../../include/minishell.h"

int unset_no(t_built b, t_env **env)
{
    b.ret = unset_no_fork(b, env);
	free_tab(b.table);
	return (0);
}

int export_no(t_built b, t_env **env)
{
    b.ret = export_no_fork(b, env);
	free_tab(b.table);
	return (b.ret);
}

int cd_no(t_built b, char *simple_cmd, t_env **env)
{
    b.ret = cd_no_fork(b, env, simple_cmd);
    free_tab(b.table);
	return (b.ret);
}

int exit_no(t_built b)
{
    ms_exit(b.table + 1);
	free_tab(b.table);
	return (0);
}