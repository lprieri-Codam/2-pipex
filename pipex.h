/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 12:55:23 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:34:20 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ---------- HEADERS ---------- */

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

/* ------------ STRUCTS ------------ */

typedef struct s_cmds
{
	char			*cmd_name;
	char			*pathname;
	char			**cmd_vector;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_info
{
	char	*infile;
	char	*outfile;
	char	**paths;
	int		pipefd[2];
	int		cmds_nbr;
	int		status;
	t_cmds	*cmds;
}	t_info;

/* ------------ CMDS ------------ */
t_cmds	*px_cmds_new(t_info *info, char *fullcmd);
char	**get_cmd_vector(t_info *info, char *fullcmd);
int		px_cmds_init(t_info *info, int argc, char *argv[]);
void	px_cmds_print(t_cmds *cmds);

/* ------------ ERRORS ------------ */
void	px_exit(t_info *info, int rvalue);
void	px_exit_msg(t_info *info, char *msg, int rvalue);
void	px_exit_error(t_info *info, char *msg, int rvalue);
int		px_status(t_info *info, int status);

/* ------------ FIRST CHILD ------------ */
void	first_child(t_info **info, char *envp[]);
void	px_open_infile(t_info **info, int *infilefd);
void	px_check_command(t_info **info, char *cmd_pathname);

/* ------------ FREE ------------ */
char	*px_free(void **var);
char	*px_free_2d_arr(char ***arr);
char	*px_free_cmds(t_cmds **cmds);
char	*px_free_info(t_info **info);

/* ------------ INFO ------------ */
int		px_info_init(t_info **info, int argc, char *argv[], char *envp[]);
// void	px_info_print(t_info *info);

/* ------------ LAST CHILD ------------ */
void	second_child(t_info **info, char *envp[]);
void	px_open_outfile(t_info **info, int *outfilefd);

/* ------------ PATHS ------------ */
int		get_envp_paths(t_info *info, char **envp);
char	*get_pathname(t_info *info, char *cmdname);

/* ------------ UTILS ------------ */
char	**px_strjoin_arr(char **arr, char *s);
int		px_arr_len(const char **arr);
void	px_print_arr(char **arr);

#endif