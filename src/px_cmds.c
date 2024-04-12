/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_cmds.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 15:30:12 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:32:43 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

t_cmds			*px_cmds_new(t_info *info, char *fullcmd);
char			**get_cmd_vector(t_info *info, char *fullcmd);
int				px_cmds_init(t_info *info, int argc, char *argv[]);
static t_cmds	*px_cmds_list_create(t_info *info,
					int argc, char *argv[], int i);
void			px_cmds_print(t_cmds *cmds);

/* ---------- FUNCTIONS ---------- */

/*	NEW COMMAND (NODE)
*	It creates a new commands node with initialized variables.
*/
t_cmds	*px_cmds_new(t_info *info, char *fullcmd)
{
	t_cmds	*new;

	new = malloc (sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd_name = ft_substr(fullcmd, 0, (ft_strchr(fullcmd, ' ') - fullcmd));
	if (new->cmd_name)
	{
		new->cmd_vector = get_cmd_vector(info, fullcmd);
		if (new->cmd_vector)
			new->pathname = new->cmd_vector[0];
	}
	else
	{
		new->cmd_vector = NULL;
		new->pathname = NULL;
	}
	new->next = NULL;
	return (new);
}

/*	GET_CMD_VECTOR
*	Takes a full command as a parameter (meaning the command name and its flags).
*	Returns a cmd vector that is needed for execve command.
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
int	px_cmds_init(t_info *info, int argc, char *argv[])
{
	int		i;

	i = 2;
	info->cmds = px_cmds_list_create(info, argc, argv, i);
	return (1);
}

/*	CREATE CMDS LINKED LIST
*	CMDS[0] Stands for the first node.
*	CMDS[1] Stands for a new node.
*	CMDS[2] Stands for the current node.
*	It creates new cmds nodes and appends them to the cmds linked list.
*/
static t_cmds	*px_cmds_list_create(t_info *info,
					int argc, char *argv[], int i)
{
	t_cmds	*cmds[3];

	cmds[0] = NULL;
	cmds[1] = NULL;
	cmds[2] = NULL;
	while (i <= argc - 2 && argv[i])
	{
		cmds[1] = px_cmds_new(info, argv[i]);
		if (cmds[0] == NULL)
			return (px_free_cmds(&cmds[0]), NULL);
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
		i++;
	}
	return (cmds[0]);
}

/*	PRINT COMMANDS 
*	Prints each element of the commands structure.
*	It also iterates through each command in the linked list.
*/
void	px_cmds_print(t_cmds *cmds)
{
	ft_printf("CMD Name: %s\n", cmds->cmd_name);
	ft_printf("CMD Pathname: %s\n", cmds->pathname);
	ft_printf("CMD Vector: \n");
	px_print_arr(cmds->cmd_vector);
	if (cmds->next != NULL)
		px_cmds_print(cmds->next);
}
