/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_paths_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 13:12:45 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/03 15:37:31 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

/* ---------- PROTOTYPES ---------- */

int		get_envp_paths(t_info *info, char **envp);
char	*get_pathname(t_info *info, char *cmdname);

/* ---------- FUNCTIONS ---------- */

/*	GET ENVP PATHS
*	Sets an array with all the possible paths, each path ending with the char '/'
*	Returns 1 on success and -1 on failure.
*/
int	get_envp_paths(t_info *info, char **envp)
{
	int		i;
	char	*envp_path;
	char	**paths;

	i = 0;
	envp_path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			envp_path = envp[i];
			break ;
		}
		i++;
	}
	if (envp_path == NULL)
		return (-1);
	paths = ft_split(&envp_path[5], ':');
	if (paths == NULL)
		return (-1);
	info->paths = px_strjoin_arr(paths, "/");
	px_free_2d_arr(&paths);
	if (!info->paths)
		return (ft_printf("Failed to get paths\n"), -1);
	return (1);
}

/*	GET PATHNAME
*	The function takes a parameter the command name (the name of the binary file)
*	Compares each path until it finds the first path that has the command binary.
*	On success it returns the full path, on failure it returns NULL.
*/
char	*get_pathname(t_info *info, char *cmdname)
{
	char	*pathname;
	int		i;

	if (!info->paths || !info->paths[0] || !cmdname)
		return (NULL);
	i = 0;
	while (info->paths && info->paths[i])
	{
		pathname = ft_strjoin(info->paths[i], cmdname);
		if (!pathname)
			return (NULL);
		if (access(pathname, X_OK) == 0)
			return (pathname);
		px_free((void **) &pathname);
		i++;
	}
	if (access(cmdname, X_OK) == 0)
		return (ft_strdup(cmdname));
	return (NULL);
}
