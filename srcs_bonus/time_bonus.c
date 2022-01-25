/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 16:54:15 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"
#include	"cub3d_time_bonus.h"

//typedef struct timeval		t_time;

long long	time_to_long(t_time time)
{
	long long	n;

	n = (time.tv_sec * 1000000) + time.tv_usec;
	return (n);
}

long long	get_cur_time(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (time_to_long(now));
}

long long	get_time_between(t_time early, t_time later)
{
	long long	time_early;
	long long	time_later;

	time_early = time_to_long(early);
	time_later = time_to_long(later);
	return (time_later - time_early);
}

double	get_frame_time(void)
{
	static long long	time_last = -1;
	static long long	time_current = 0;
	long long			frame_diff;

	if (time_last == -1)
		time_last = get_cur_time();
	time_current = (long long)get_cur_time();
	frame_diff = time_current - time_last;
	time_last = time_current;
	return ((double)frame_diff / 1000000.0);
}
