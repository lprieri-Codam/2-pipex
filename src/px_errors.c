/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_errors.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/18 14:35:37 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:33:22 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

void	px_exit(t_info *info, int rvalue);
void	px_exit_msg(t_info *info, char *msg, int rvalue);
void	px_exit_error(t_info *info, char *msg, int rvalue);
int		px_status(t_info *info, int status);

/* ---------- FUNCTIONS ---------- */

/*	EXIT
*	Frees the info structure and exits with the value passed as 'rvalue'.
*/
void	px_exit(t_info *info, int rvalue)
{
	if (info != NULL)
		px_free_info(&info);
	exit(rvalue);
}

/*	EXIT MESSAGE
*	Frees the info structure, prints a message on STD_ERR
*	And exits with 'rvalue'.
*/
void	px_exit_msg(t_info *info, char *msg, int rvalue)
{
	if (info != NULL)
		px_free_info(&info);
	ft_putstr_fd(msg, 2);
	exit(rvalue);
}

/*	EXIT ERROR
*	Frees the info structure, prints a message with perror,
*	which also prints the errno message, and exits with 'rvalue'.
*/
void	px_exit_error(t_info *info, char *msg, int rvalue)
{
	if (info != NULL)
		px_free_info(&info);
	perror(msg);
	exit(rvalue);
}

/*	PX_STATUS
*	If the child terminated normally it returns the exit status of the child.
*	If the child was terminated by a signal it returns the nbr of the signal
*	that caused the child process to terminate.
*	Returns 'weird error' message on any other case.
*/
int	px_status(t_info *info, int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		px_exit_error(info, "Weird error: ", 127);
	return (127);
}
