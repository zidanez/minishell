/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:45:53 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:38:07 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define MSH_RL_BUFSIZE 1024

# include "libft.h"
# include "ft_avl_tree.h"
# include "dstring.h"
# include <unistd.h>

static char	*g_bltns_str[] = {"echo", "cd", "setenv", "unsetenv", "env",\
	"exit", "help", "pwd"};

t_dyn_string		*g_pwd;
t_dyn_string		*g_oldpwd;
t_dyn_string		*g_cd_pwd;
t_dyn_string		*g_cd_oldpwd;

typedef struct		s_env
{
	t_avl_tree		*globals;
	t_avl_tree		*builtns;
	t_avl_tree		*cmds;
}					t_env;

typedef struct		s_flags
{
	char			first;
	char			second;
}					t_flags;

int					bltn_echo(char **arg, t_env *env);
int					bltn_cd(char **args, t_env *env);
int					bltn_cd_loop(char *args, t_env *env, t_flags *fl);
int					bltn_cd_parser(t_env *env, t_dlist **path);
DSTRING				*bltn_cd_pathtostr(t_dlist *path);
void				bltn_cd_destroy_path(t_dlist **path);
void				bltn_cd_freepaths(DSTRING **oldpath, \
						DSTRING **newpath, t_dlist	**path);
int					bltn_cd_error(DSTRING **oldpath, \
						DSTRING **newpath, t_dlist	**path);
void				bltn_cd_concat(char **path);
int					bltn_cd_countargs(char **args);
void				bltn_cdpath_remslash(char **str);
int					bltn_cd_argrec_ret(char ***path, int status, t_env *env);
int					bltn_cd_home(t_env *env);
int					bltn_cd_oldpwd(t_env *env);
void				bltn_cd_parse_flgs(char *str, t_flags *flgs);
int					bltn_cd_flgspath(DSTRING **newpath);
int					bltn_cd_argrec(char **str, char **str2,\
									t_env *env, t_flags *fl);
int					bltn_cd_cdpath(char *str, t_env *env, t_flags *fl);
int					bltn_cdpath_setgl(t_env *env, DSTRING **newpath);
int					bltn_setenv(char **arg, t_env *env);
int					bltn_unsetenv(char **arg, t_env *env);
int					bltn_env(char **arg, t_env *env);
int					bltn_exit(char **arg, t_env *env);
int					bltn_help(char **arg, t_env *env);
int					bltn_pwd(char **arg, t_env *env);
int					env_init(char **en, t_env *env);
char				*find_bin(t_env *env, char *name);
void				et_rm_clear_env(t_env *env);
int					bltn_count_builtins(void);
void				free_spl(char ***spl);
char				*read_line();
char				**ft_tokenizer(char *str);
int					sh_execute(char **argv, t_env *env);
int					bltn_cd_countargs(char **arg);
void				et_rm_warr(char **args);
char				*ft_parse_flags(char **argc);
DSTRING				*env_get_variable(const char *key, t_env *enviroment);
int					exe_launch(char **argv, t_env *env);
char				*exe_findpath(char *name, t_env *env);
int					exe_parsecmd(char *str, t_env *env, char **path);
void				et_rm_str(void *cont, size_t ske);

static int	(*g_bltns_func[]) (char **, t_env *) = {&bltn_echo,\
	&bltn_cd, &bltn_setenv, &bltn_unsetenv, &bltn_env,\
	&bltn_exit, &bltn_help, &bltn_pwd};

#endif
