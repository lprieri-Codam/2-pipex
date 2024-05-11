/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_children.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 14:58:18 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/16 14:40:55 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

void		px_pipeline(t_info *info, char **envp);
static void	px_run_child(t_info *info, int i, char **envp);
static void	px_do_parent_duties(t_info *info, int current_child);
static void	px_redirect_io(t_info *info, int io_fd, int std_io_target);
static void	px_execute_cmd(t_info *info, char **envp);

/* ---------- FUNCTIONS ---------- */

/*	PIPELINE
*	Forks the process for every command passed to the program.
*	It also creates a pipe for the (cmd_nbr - 1)
*	to intercommunicate between processes.
*	The child process runs the command and exits.
*	The parent process waits for the children to die
*	and updates the status based on the last child's exit status.
*/
void	px_pipeline(t_info *info, char **envp)
{
	int	i;

	i = 0;
	while (i < info->cmds_nbr)
	{
		if (i < info->pipes_nbr && pipe(info->pipefd) == -1)
			px_exit_error(info, "Pipe failure", 1);
		info->parent = fork();
		if (info->parent == -1)
			px_exit_error(info, "Fork failure", 1);
		else if (!info->parent)
			px_run_child(info, i, envp);
		px_do_parent_duties(info, i);
		i++;
	}
	waitpid(info->parent, &info->status, 0);
	while (wait(NULL) != -1)
		;
}

/*	RUN CHILD
*	At i == 0 it processes input either from an infile or from STDIN,
*	otherwise it reads input from the pipe[READ_END].
*	The 2nd thing it does is open the outfile if it's the last process,
*	Otherwise it redirects output to the pipe[WRITE_END].
*	Lastly, it executes the command, replacing the process.
*/
static void	px_run_child(t_info *info, int i, char **envp)
{
	if (i < info->pipes_nbr)
	{
		if (close(info->pipefd[READ_END]) == -1)
			px_exit_error(info, "Close failure pipe\n", 1);
		px_redirect_io(info, info->pipefd[WRITE_END], STDOUT_FILENO);
	}
	else
	{
		px_open_outfile(info);
		px_redirect_io(info, info->outfilefd, STDOUT_FILENO);
	}
	if (i == 0)
	{
		px_open_infile(info);
		px_redirect_io(info, info->infilefd, STDIN_FILENO);
	}
	else
		px_redirect_io(info, info->read_end, STDIN_FILENO);
	px_execute_cmd(info, envp);
}

/*	REDIRECT INPUT/OUTPUT
*	Redirects an input/output file descriptor to STDIN/STDOUT respectively.
*	If the redirection is successful it closes the I/O file descriptor.
*/
static void	px_redirect_io(t_info *info, int io_fd, int std_io_target)
{
	if (dup2(io_fd, std_io_target) == -1)
		px_exit_error(info, "Dup error", -1);
	if (close(io_fd) == -1)
		px_exit_error(info, "Closing I/O fildes", -1);
}

/*	EXECUTE CMD
*	It executes the current command (stored as a cmd struct in the info struct).
*	Exits with exit value of 127 on error.
*/
static void	px_execute_cmd(t_info *info, char **envp)
{
	if (!info->cmds || !info->cmds->pathname || !info->cmds->cmd_vector)
		px_exit_error(info, "Command not found", 127);
	if (execve(info->cmds->pathname, info->cmds->cmd_vector, envp) == -1)
		px_exit_error(info, "Execve error", 127);
}

/*	DO PARENT DUTIES
*	It closes the READ_END stored from a previous pipe.
*	It also closes the unused end of the pipe (pipe[WRITE_END]).
*	It updates the READ_END in the info structure with the new value.
*	It moves to the next command in the cmd linked list (in the info struct).
*/
static void	px_do_parent_duties(t_info *info, int current_child)
{
	if (current_child > 0)
	{
		if (close((info->read_end)) == -1)
			px_exit_error(info, "Close failure in parent", 1);
	}
	if (current_child < info->pipes_nbr)
	{
		if (close(info->pipefd[WRITE_END]) == -1)
			px_exit_error(info, "Close failure pipe\n", 1);
		info->read_end = info->pipefd[READ_END];
	}
	info->cmds = info->cmds->next;
}
