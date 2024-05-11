/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_open_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lprieri <lprieri@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:00:46 by lprieri       #+#    #+#                 */
/*   Updated: 2024/04/16 14:41:40 by lprieri       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* ---------- PROTOTYPES ---------- */

void	px_open_infile(t_info *info);
void	px_open_outfile(t_info *info);

/* ---------- FUNCTIONS ---------- */

/*	OPEN INFILE
*	If hdoc is false it will check if there's an infile which can be read.
*	Then it will open it on READ mode, storing the fildes in the info struct.
*/
void	px_open_infile(t_info *info)
{
	if (access(info->infile, R_OK) == -1)
		px_exit_error(info, "Infile access error", 1);
	info->infilefd = open(info->infile, O_RDONLY);
	if (info->infilefd == -1)
		px_exit_error(info, "Infile open error", 1);
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
	info->outfilefd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->outfilefd == -1)
		px_exit_error(info, "Outfile open error", 1);
}
