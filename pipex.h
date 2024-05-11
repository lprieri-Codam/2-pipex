/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 12:55:23 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/16 14:39:56 by lprieri       ########   odam.nl         */
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
# include <stdbool.h>
# include "libft/libft.h"

/* ---------- MACROS ---------- */

# define TRUE 1
# define FALSE 0
# define READ_END 0
# define WRITE_END 1

/* ---------- STRUCTS ---------- */

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
	int		infilefd;
	char	*outfile;
	int		outfilefd;
	char	**paths;
	int		pipefd[2];
	int		read_end;
	int		status;
	int		cmds_nbr;
	int		pipes_nbr;
	pid_t	parent;
	t_cmds	*cmds;
	t_cmds	*cmds_ptr;
}	t_info;

/* ---------- CHILDREN ---------- */
void	px_pipeline(t_info *info, char **envp);

/* ---------- CMDS ---------- */
t_cmds	*px_cmds_new(t_info *info, char *fullcmd);
char	**get_cmd_vector(t_info *info, char *fullcmd);
int		px_cmds_init(t_info *info, char *argv[]);
void	px_check_command(t_info **info, char *cmd_pathname);

/* ---------- ERRORS ---------- */
void	px_exit(t_info *info, int rvalue);
void	px_exit_msg(t_info *info, char *msg, int rvalue);
void	px_exit_error(t_info *info, char *msg, int rvalue);
void	px_exit_status(t_info *info, int rvalue);
int		px_status(t_info *info, int status);

/* ---------- FREE ---------- */
char	*px_free(void **var);
char	*px_free_2d_arr(char ***arr);
char	*px_free_cmds(t_cmds **cmds);
char	*px_free_info(t_info **info);

/* ---------- INFO ---------- */
int		px_info_init(t_info **info, int argc, char *argv[], char *envp[]);
void	px_info_print(t_info *info);

/* ---------- OPEN UTILS ---------- */
void	px_open_infile(t_info *info);
void	px_open_outfile(t_info *info);

/* ---------- PATHS ---------- */
int		get_envp_paths(t_info *info, char **envp);
char	*get_pathname(t_info *info, char *cmdname);

/* ---------- UTILS ---------- */
char	**px_strjoin_arr(char **arr, char *s);
int		px_arr_len(const char **arr);
void	px_print_arr(char **arr);

#endif