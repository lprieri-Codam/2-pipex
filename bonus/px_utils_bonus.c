/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_utils_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 13:42:54 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:34:43 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

/* ---------- PROTOTYPES ---------- */

char	**px_strjoin_arr(char **arr, char *s);
int		px_arr_len(const char **arr);
void	px_print_arr(char **arr);

/* ---------- FUNCTIONS ---------- */

/*	ARRAY STRING JOIN 
*	Appends a string 's' to each string in an array.
*/
char	**px_strjoin_arr(char **arr, char *s)
{
	char	*temp;
	char	**new_arr;
	int		arr_len;
	int		i;

	if (!s || !*arr || !(*arr)[0])
		return (NULL);
	arr_len = px_arr_len((const char **) arr);
	new_arr = ft_calloc(sizeof(char *), arr_len + 1);
	i = 0;
	while (arr[i])
	{
		temp = ft_strjoin(arr[i], s);
		if (!temp)
			return (ft_printf("Arr strjoin error\n"), NULL);
		new_arr[i] = ft_strdup(temp);
		if (!(new_arr)[i])
			return (ft_printf("Arr strdup error \n"),
				px_free_2d_arr(&new_arr), px_free((void **) &temp), NULL);
		px_free((void **) &temp);
		i++;
	}
	return (new_arr);
}

/*	ARRAY LENGTH
*	Returns the number of strings in a char array.
*/
int	px_arr_len(const char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return (i);
	while (arr[i])
		i++;
	return (i);
}

/*	PRINT ARRAY
*	Prints each string of an array, separated by a new line.
*/
void	px_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}
