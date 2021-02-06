
#include <stdlib.h>

#include "cities.h"
#include "pipes.h"


/*
** retourne un nouvel id de ville
*/
static size_t city_get_id()
{
	static size_t next_id = 0;
	return next_id++;
}

/*
** Crée une nouvelle structure de groupe de villes city_grp_t
*/
city_grp_t* city_grp_create()
{
	city_grp_t* ret = malloc(sizeof(city_grp_t));

	if (ret != NULL)
	{
		ret->size = 1;
		ret->next = NULL;
	}
	return ret;
}

/*
** Crée une nouvelle structure city_t
*/
city_t *city_create(char *name, size_t population, float longitude, float latitude)
{
	city_t *ret = malloc(sizeof(city_t));

	if (ret != NULL)
	{
		ret->group = city_grp_create();
		if (ret->group == NULL)
			return NULL;
		ret->id = city_get_id();
		ret->name = name;
		ret->population = population;
		ret->longitude = longitude;
		ret->latitude = latitude;
		ret->next = NULL;
	}
	return ret;
}

/*
** detruit un grp de ville
*/
void city_grp_destroy_all(city_grp_t* grp)
{
	city_grp_t* tmp = grp;

	while (grp != NULL)
	{
		grp = tmp->next;
		free(tmp);
		tmp = grp;
	}
}

/*
** detruit une ville
*/
void city_destroy(city_t *city)
{
	if (city == NULL)
		return;
	city_leave_grp(city);
	if (city->name != NULL)
		free(city->name);
	free(city);
}
