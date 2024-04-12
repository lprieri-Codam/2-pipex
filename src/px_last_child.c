/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_last_child.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 12:59:39 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:28:50 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

void	second_child(t_info **info, char *envp[]);
void	px_open_outfile(t_info **info, int *outfilefd);

/* ---------- FUNCTIONS ---------- */

void	second_child(t_info **info, char *envp[])
{
	int	outfile;

	px_open_outfile(info, &outfile);
	px_check_command(info, (*info)->cmds->next->pathname);
	if (close((*info)->pipefd[1]) == -1)
		px_exit_error(*info, "Closing pipefd[1] error", -1);
	if (dup2((*info)->pipefd[0], STDIN_FILENO))
		px_exit_error(*info, "Dup error", -1);
	if (close((*info)->pipefd[0]) == -1)
		px_exit_error(*info, "Closing pipefd[0] error", -1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		px_exit_error(*info, "Dup error", -1);
	if (close(outfile) == -1)
		px_exit_error(*info, "Closing outfile error", -1);
	if (execve((*info)->cmds->next->pathname,
			(*info)->cmds->next->cmd_vector, envp) == -1)
		px_exit_error(*info, "Execve error in second child", -1);
}

void	px_open_outfile(t_info **info, int *outfilefd)
{
	if (access((*info)->outfile, F_OK) == 1
		&& access((*info)->outfile, W_OK) == -1)
		px_exit_error(*info, "Outfile access error", 1);
	*outfilefd = open((*info)->outfile, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (*outfilefd == -1)
		px_exit_error(*info, "Outfile open error", 1);
}
