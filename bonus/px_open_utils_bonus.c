/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_open_utils_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:00:46 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/11 15:22:58 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

/* ---------- PROTOTYPES ---------- */

void	px_hdoc_in(t_info *info);
void	px_open_infile(t_info *info);
void	px_open_outfile(t_info *info);

/* ---------- FUNCTIONS ---------- */

/*	HERE_DOC INPUT
*	This function is called when info->hdoc is TRUE.
*	It reads input from STD_IN until the limiter is written on a new line.
*	It writes the input on STD_OUT (which has already been redirected
*	to the pipe[WRITE_END]).
*	When the limiter is read it exits the process.
*/
void	px_hdoc_in(t_info *info)
{
	char	*buffer;

	while (TRUE)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			px_exit_error(info, "Failed to read input", 1);
		if (ft_strncmp(buffer, info->limiter, ft_strlen(info->limiter)) == 0
			&& (buffer[ft_strlen(info->limiter)] == '\n'))
		{
			free(buffer);
			px_exit_status(info, 0);
		}
		write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		free(buffer);
	}
}

/*	OPEN INFILE
*	If hdoc is false it will check if there's an infile which can be read.
*	Then it will open it on READ mode, storing the fildes in the info struct.
*/
void	px_open_infile(t_info *info)
{
	if (info->hdoc == FALSE)
	{
		if (access(info->infile, R_OK) == -1)
			px_exit_error(info, "Infile access error", 1);
		info->infilefd = open(info->infile, O_RDONLY);
		if (info->infilefd == -1)
			px_exit_error(info, "Infile open error", 1);
	}
}

/*	OPEN OUTFILE
*	Returns error if the file exists but it's not possible to write on it.
*	If the outfile doesn't exist it creates it.
*	It also distinguishes when here_doc is true which would open the file
*	in append mode, from when it's false which it would open in truncate mode.
*/
void	px_open_outfile(t_info *info)
{
	if (access(info->outfile, F_OK) == 1 && access(info->outfile, W_OK) == -1)
		px_exit_error(info, "Outfile access error", 1);
	if (info->hdoc)
		info->outfilefd = open(info->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		info->outfilefd = open(info->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->outfilefd == -1)
		px_exit_error(info, "Outfile open error", 1);
}
