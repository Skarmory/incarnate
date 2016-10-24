#include "entity_manager.h"

using namespace std;

int EntityManager::NEXT_ID = 0;

shared_ptr<Entity> EntityManager::create_entity(string entity_type)
{
	shared_ptr<Entity> e(move(_factory.create(NEXT_ID, entity_type)));
	_entities[NEXT_ID] = e;

	if (entity_type == "player")
		_player_id = NEXT_ID;

	NEXT_ID++;

	_event_manager.broadcast<EntityCreated>(e);

	return e;
}

shared_ptr<Entity> EntityManager::create_entity_at_loc(string entity_type, int x, int y)
{
	shared_ptr<Entity> e = create_entity(entity_type);
	shared_ptr<Location> loc = e->get_component<Location>();
	loc->x = x;
	loc->y = y;

	return e;
}

void EntityManager::update(void)
{
	for(map<int, shared_ptr<Entity>>::iterator it = _entities.begin(); it !=_entities.end();)
	{
		if(it->second->obsolete)
		{
			it = _entities.erase(it);
			continue;
		}

		it++;
	}	
}

const Entity& EntityManager::get_player(void) const
{
	return *_entities.at(_player_id);
}
