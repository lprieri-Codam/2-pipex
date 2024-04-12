/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_first_child.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 11:51:58 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:28:05 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

void	first_child(t_info **info, char *envp[]);
void	px_open_infile(t_info **info, int *infilefd);
void	px_check_command(t_info **info, char *cmd_pathname);

/* ---------- FUNCTIONS ---------- */

void	first_child(t_info **info, char *envp[])
{
	int	infile;

	px_open_infile(info, &infile);
	px_check_command(info, (*info)->cmds->pathname);
	if (close((*info)->pipefd[0]) == -1)
		px_exit_error(*info, "Closing read end (pipefd[0]) in first child", 1);
	if (dup2(infile, STDIN_FILENO) == -1)
		px_exit_error(*info, "Dup error", -1);
	if (close(infile) == -1)
		px_exit_error(*info, "Closing infile error", -1);
	if (dup2((*info)->pipefd[1], STDOUT_FILENO) == -1)
		px_exit_error(*info, "Dup error", -1);
	if (close((*info)->pipefd[1]) == -1)
		px_exit_error(*info, "Closing write end (pipefd[1]) error", -1);
	if (execve((*info)->cmds->pathname, (*info)->cmds->cmd_vector, envp) == -1)
		px_exit_error(*info, "Execve error in first child", 127);
}

void	px_open_infile(t_info **info, int *infilefd)
{
	if (access((*info)->infile, R_OK) == -1)
		px_exit_error(*info, "Infile access error", 1);
	*infilefd = open((*info)->infile, O_RDONLY);
	if (*infilefd == -1)
		px_exit_error(*info, "Infile open error", 1);
}

void	px_check_command(t_info **info, char *cmd_pathname)
{
	if (!cmd_pathname || !cmd_pathname[0])
		px_exit_msg(*info, "Command not found\n", 127);
	if (access(cmd_pathname, X_OK) == -1)
		px_exit_msg(*info, "Command not found\n", 127);
}
