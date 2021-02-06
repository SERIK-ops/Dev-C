
#include <stdlib.h>
#include <stdio.h>

#include "cities.h"
#include "pipes.h"

/*
**separe une villes de son group
*/
void city_leave_grp(city_t* city)
{
	if (city == NULL || city->group == NULL)
		return;
	city->group->size -= 1;
	city->group = NULL;
}

/*
** ajoute une ville dans  un grp
*/
void city_join_grp(city_t* city, city_grp_t* grp)
{
	if (city == NULL || grp == NULL)
		return;
	if (city->group != NULL)
		city_leave_grp(city);
	city->group = grp;
	grp->size += 1;
}

/*
** Déplace toutes les villes d'un groupe à un autre
*/
void city_merge_grp(city_t* cities, city_grp_t* leave, city_grp_t* join)
{
	while (cities != NULL && leave->size > 0)
	{
		if (cities->group == leave)
			city_join_grp(cities, join);
		cities = cities->next;
	}
}

/*
** affiche des informations des villes
*/
void city_dump_all(city_t* c)
{
	while (c != NULL)
	{
		printf("%s[%lu]:\tin the group %p (%lu)\n", c->name, c->id, c->group, c->group->size);
		c = c->next;
	}
}

/*
** Ajoute une ville dans un groupe de ville
*/
void city_grp_append(city_grp_t* grp, city_t* city, city_t* all)
{
	if (grp == NULL || city == NULL)
		return;
	if (all == NULL)
		city_join_grp(city, grp);
	else
		city_merge_grp(all, city->group, grp);
}
