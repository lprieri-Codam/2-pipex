/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_info.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 14:27:59 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/16 14:40:00 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

int			px_info_init(t_info **info, int argc, char *argv[], char *envp[]);
static int	px_info_init_nhdoc(t_info *info,
				int argc, char *argv[], char *envp[]);
static int	px_init_common_vars(t_info *info,
				int argc, char *argv[], char *envp[]);

/* ---------- FUNCTIONS ---------- */

/*	INFO INIT
*	Initializes an info structure.
*	It assigns heap memory, and it initializes each variable within the structure
*/
int	px_info_init(t_info **info, int argc, char *argv[], char *envp[])
{
	*info = (t_info *) malloc(sizeof(t_info));
	if (!(*info))
		return (ft_putstr_fd("Failed to malloc info\n", 2), EXIT_FAILURE);
	return (px_info_init_nhdoc(*info, argc, argv, envp));
}

/*	INIT INFO NHDOC
*	Initializes the info struct variables for a infile program.
*/
static int	px_info_init_nhdoc(t_info *info,
				int argc, char *argv[], char *envp[])
{
	if (argc < 5)
		return (free(info), -1);
	if (argv[1] && argv[argc - 1] && argv[1] != argv[argc - 1])
	{
		info->infile = argv[1];
		info->outfile = argv[argc - 1];
	}
	return (px_init_common_vars(info, argc, argv, envp));
}

/*	INIT COMMON VARIABLES
*	Initializes the common variables that hdoc and nhdoc programs share.
*/
static int	px_init_common_vars(t_info *info,
				int argc, char *argv[], char *envp[])
{
	info->cmds_nbr = argc - 3;
	if (get_envp_paths(info, envp) == -1)
		return (px_free((void **) &info), -1);
	if (px_cmds_init(info, argv) == -1)
		return (perror("Cmds init error"), px_free_2d_arr(&info->paths),
			px_free((void **) info), -1);
	info->pipefd[0] = -1;
	info->pipefd[1] = -1;
	info->status = -1;
	info->cmds_ptr = info->cmds;
	info->pipes_nbr = info->cmds_nbr - 1;
	info->parent = -1;
	info->infilefd = -1;
	info->outfilefd = -1;
	info->read_end = -1;
	return (1);
}
