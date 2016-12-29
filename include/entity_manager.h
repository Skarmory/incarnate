#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
#include <string>

#include <rapidxml-1.13\rapidxml.hpp>
#include <rapidxml-1.13\rapidxml_utils.hpp>
#include <rapidxml-1.13\rapidxml_iterators.hpp>

#include "entity.h"
#include "components.h"
#include "entity_factory.h"
#include "events.h"
#include "loaders.h"

using namespace std;
using namespace sov;

// Temporary loading code

class EntityLoader
{
public:
	EntityLoader(void)
	{
		_file = new rapidxml::file<>(_file_path);
		_xml_data.parse<0>(_file->data());
	}

	~EntityLoader(void)
	{
		//delete _file;
		/*for (auto& loader : _component_loaders)
			delete loader.second;*/
	}

	unique_ptr<Entity> load(string entity_id);

private:
	const char _file_path[28] = "resources/data/entities.xml";
	rapidxml::xml_document<> _xml_data;
	rapidxml::file<>* _file;

	map<string, ComponentLoader*>  _component_loaders = {
		{ "graphic", new GraphicLoader() },
		{ "location", new LocationLoader() },
		{ "collision", new CollisionLoader() },
		{ "health", new HealthLoader() },
		{ "light", new LightSourceLoader() },
		{ "sight", new SightLoader() },
		{ "damage", new DamageLoader() },
		{ "periodicDamage", new PeriodicDamageLoader() },
	};

	//void _subparse(string type, rapidxml::xml_node<char>* node, Entity& prototype);
};

//

class EntityCache
{
public:
	unique_ptr<Entity> get_entity(string entity_id);

private:
	EntityLoader _loader;
	map<string, unique_ptr<Entity>> _entities;

	void _load_entity(string entity_id);
	bool _has_entity(string entity_id);
};

class EntityManager
{
public:
	
	explicit EntityManager(const EventManager& evm) : _event_manager(evm)	{};

	shared_ptr<Entity> create_entity(string entity_type);
	shared_ptr<Entity> create_entity_at_loc(string entity_type, int x, int y);

	const Entity& get_player(void) const;
	
	void update(void);

private:
	map<int, shared_ptr<Entity>> _entities;
	const EventManager& _event_manager;
	EntityCache _cache;
	EntityFactory _factory;
	int _player_id;

	static int NEXT_ID;
};

#endif
