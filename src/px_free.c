/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 13:48:55 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/16 13:43:00 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

char	*px_free(void **var);
char	*px_free_2d_arr(char ***arr);
char	*px_free_cmds(t_cmds **cmds);
char	*px_free_info(t_info **info);

/* ---------- FUNCTIONS ---------- */

/*	PX_FREE
*	Frees a variable and sets the pointer to NULL.
*/
char	*px_free(void **var)
{
	free(*var);
	*var = NULL;
	return (NULL);
}

/*	PX_FREE 2D ARRAY
*	Frees each element of an array.
*	At the end it frees the array itself and sets the ptr of the array to NULL.
*/
char	*px_free_2d_arr(char ***arr)
{
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	arr = NULL;
	return (NULL);
}

/*	PX_FREE COMMANDS
*	Frees recursively the commands stored in the linked list.
*	It frees the string that stores the command name,
*	and it frees the command vector array (that holds the pathname and the flags)
*/
char	*px_free_cmds(t_cmds **cmds)
{
	if ((*cmds) == NULL)
		return (NULL);
	px_free_cmds(&(*cmds)->next);
	px_free((void **) &(*cmds)->cmd_name);
	px_free_2d_arr(&(*cmds)->cmd_vector);
	px_free((void **) cmds);
	return (NULL);
}

/*	PX_FREE INFO
*	Frees the info structure by freeing the paths array,
*	the commands linked list,
*	and ultimately the info struct itself.
*/
char	*px_free_info(t_info **info)
{
	if (!(*info))
		return (NULL);
	px_free_2d_arr(&(*info)->paths);
	px_free_cmds(&(*info)->cmds_ptr);
	return (px_free((void **) info));
}
