/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:30:46 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/31 16:50:00 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <strings.h>
#include <string.h>

#define INVALID_ROOM "Invalid Room\n"
#define INVALID "Invalid input\n"
#define WOW() printf("->%s\n", __func__)

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_list
{
	void			*data;
	size_t			size;
	struct s_list	*next;
}					t_list;

typedef struct		s_adj
{
	struct s_room	*room;
	int 			direction:1; //1 for forward, 0 for blocked
	struct s_adj	*next;
}					t_adj;

typedef struct		s_room
{
	char			*name;
	unsigned		occupied;
	unsigned		significance:2; // 1 for start, 2 for end
	unsigned		distance;
	unsigned		visited:1;
	t_point			coordinates;
	t_adj			*adjacent;
}					t_room;

void			print_rooms(t_list *rooms);
void			print_room(t_room *room);
void			lem_in(void);

#endif
