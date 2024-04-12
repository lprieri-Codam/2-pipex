/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_info.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 14:27:59 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:34:08 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

int		px_info_init(t_info **info, int argc, char *argv[], char *envp[]);
// void	px_info_print(t_info *info);

/* ---------- FUNCTIONS ---------- */

/*	INFO INIT
*	Initializes an info structure.
*	It assigns heap memory, and it initializes each variable within the structure
*/
int	px_info_init(t_info **info, int argc, char *argv[], char *envp[])
{
	*info = malloc(sizeof(t_info));
	if (!*info)
		return (-1);
	if (argv[1] && argv[argc - 1] && argv[1] != argv[argc - 1])
	{
		(*info)->infile = argv[1];
		(*info)->outfile = argv[argc - 1];
	}
	if (get_envp_paths(*info, envp) == -1)
		return (px_free((void **) info), -1);
	if (px_cmds_init(*info, argc, argv) == -1)
		return (perror("Cmds init error"), px_free_2d_arr(&(*info)->paths),
			px_free((void **) info), -1);
	(*info)->pipefd[0] = -1;
	(*info)->pipefd[1] = -1;
	(*info)->cmds_nbr = argc - 3;
	(*info)->status = -1;
	return (1);
}

// void	px_info_print(t_info *info)
// {
// 	ft_printf("Infile: %s\n", info->infile);
// 	ft_printf("Infile: %s\n", info->outfile);
// 	ft_printf("\n");
// 	ft_printf("Paths:\n");
// 	px_print_arr(info->paths);
// 	ft_printf("\n");
// 	px_cmds_print(info->cmds);
// }
