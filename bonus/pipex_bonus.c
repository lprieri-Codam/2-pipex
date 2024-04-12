/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 12:56:52 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/03 15:35:44 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	*info;

	if (argc < 2)
		return (1);
	if (px_info_init(&info, argc, argv, envp) == -1)
		return (ft_putstr_fd("Failed to init info struct.\n", 2), EXIT_FAILURE);
	px_pipeline(info, envp);
	px_exit_status(info, WEXITSTATUS(info->status));
}
