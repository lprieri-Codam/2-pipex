/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_cmds_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 15:30:12 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:01:29 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

/* ---------- PROTOTYPES ---------- */

t_cmds			*px_cmds_new(t_info *info, char *fullcmd);
char			**get_cmd_vector(t_info *info, char *fullcmd);
int				px_cmds_init(t_info *info, char *argv[]);
static t_cmds	*px_cmds_list_create(t_info *info,
					char *argv[], int cmd_i, int argv_pos);
void			px_check_command(t_info **info, char *cmd_pathname);
// void	px_cmds_print(t_cmds *cmds);

/* ---------- FUNCTIONS ---------- */

/*	NEW COMMAND (NODE)
*	It creates a new commands node with initialized variables.
*/
t_cmds	*px_cmds_new(t_info *info, char *fullcmd)
{
	t_cmds	*new;

	new = (t_cmds *) malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd_name = ft_substr(fullcmd, 0, (ft_strchr(fullcmd, ' ') - fullcmd));
	if (new->cmd_name)
	{
		new->cmd_vector = get_cmd_vector(info, fullcmd);
		if (new->cmd_vector)
			new->pathname = new->cmd_vector[0];
		else
			new->pathname = NULL;
	}
	else
	{
		new->cmd_vector = NULL;
		new->pathname = NULL;
	}
	new->next = NULL;
	return (new);
}

/*	GET COMMAND VECTOR
*	Takes a full command as a parameter (meaning the command name and its flags).
*	Returns an array in which the first element is the command's pathname,
*	and the rest of the elements are its flags.
*	This cmd_vector is needed for execve.
*/
char	**get_cmd_vector(t_info *info, char *fullcmd)
{
	char	**cmd_vector;
	char	*pathname;

	cmd_vector = ft_split(fullcmd, ' ');
	if (!cmd_vector)
		return (NULL);
	pathname = get_pathname(info, cmd_vector[0]);
	if (!pathname)
		return (px_free_2d_arr(&cmd_vector), NULL);
	px_free((void **) &cmd_vector[0]);
	cmd_vector[0] = pathname;
	return (cmd_vector);
}

/*	COMMANDS INIT
*	It initializes the commands structure/linked list.
*/
int	px_cmds_init(t_info *info, char *argv[])
{
	int		i;
	int		j;

	i = 2;
	if (info->hdoc)
		i++;
	j = 0;
	info->cmds = px_cmds_list_create(info, argv, j, i);
	return (1);
}

/*	CREATE CMDS LINKED LIST
*	CMDS[0] Stands for the first node.
*	CMDS[1] Stands for a new node.
*	CMDS[2] Stands for the current node.
*	It creates new cmds nodes and appends them to the cmds linked list.
*/
static t_cmds	*px_cmds_list_create(t_info *info,
					char *argv[], int cmd_i, int argv_pos)
{
	t_cmds	*cmds[3];

	cmds[0] = NULL;
	cmds[1] = NULL;
	cmds[2] = NULL;
	while (cmd_i < info->cmds_nbr && argv[argv_pos])
	{
		cmds[1] = px_cmds_new(info, argv[argv_pos]);
		if (cmds[1] == NULL)
			return (px_free_cmds(&info->cmds), NULL);
		if (cmds[0] == NULL)
		{
			cmds[0] = cmds[1];
			cmds[2] = cmds[0];
		}
		else
		{
			cmds[2]->next = cmds[1];
			cmds[2] = cmds[2]->next;
		}
		argv_pos++;
		cmd_i++;
	}
	return (cmds[0]);
}

/*	CHECK COMMAND
*	It checks whether a command's path exists,
*	and it checks whether it is possible to execute it.
*	It exits the process on failure with exit code: 127.
*/
void	px_check_command(t_info **info, char *cmd_pathname)
{
	if (!cmd_pathname || !cmd_pathname[0])
		px_exit_msg(*info, "Command not found\n", 127);
	if (access(cmd_pathname, X_OK) == -1)
		px_exit_msg(*info, "Command not found\n", 127);
}

/*	PRINT COMMANDS 
*	Prints each element of the commands structure.
*	It also iterates through each command in the linked list.
*/
// void	px_cmds_print(t_cmds *cmds)
// {
// 	ft_printf("CMD Name: %s\n", cmds->cmd_name);
// 	ft_printf("CMD Pathname: %s\n", cmds->pathname);
// 	ft_printf("CMD Vector: \n");
// 	px_print_arr(cmds->cmd_vector);
// 	if (cmds->next != NULL)
// 		px_cmds_print(cmds->next);
// }
