/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 12:56:52 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/03 16:06:27 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	*info;
	pid_t	parent1;
	pid_t	parent2;

	if (argc < 5)
		return (ft_putstr_fd("Incorrect number of args.\n", 2), EXIT_FAILURE);
	if (px_info_init(&info, argc, argv, envp) == -1)
		return (perror("Failed to init the info struct."), EXIT_FAILURE);
	if (pipe(info->pipefd) == -1)
		px_exit_error(info, "Failed to pipe", 1);
	parent1 = fork();
	if (parent1 == -1)
		px_exit_error(info, "Failed to fork", 1);
	if (!parent1)
		first_child(&info, envp);
	parent2 = fork();
	if (parent2 == -1)
		px_exit_error(info, "Failed to fork", 1);
	if (!parent2)
		second_child(&info, envp);
	if (close(info->pipefd[0]) == -1 || close(info->pipefd[1]) == -1)
		px_exit_error(info, "Failed to close pipefd in parent", 1);
	waitpid(parent1, &info->status, 0);
	waitpid(parent2, &info->status, 0);
	return (px_free_info(&info), px_status(info, info->status));
}
