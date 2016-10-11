#ifndef render_system_h
#define render_system_h

#include <vector>
#include <memory>
#include <algorithm>

#include "libtcod.hpp"

#include "system.h"
#include "components.h"
#include "events.h"
#include "level.h"

using namespace std;

class RenderSystem : public System, public Observer<EntityCreated> {
public:
	RenderSystem(Level& level) : _level(&level) {}

	virtual void init(EventManager& evm) override;
	virtual void update(EventManager& evm) override;
	virtual void receive(const EntityCreated& e) override;

private:
	static bool layer_compare(const weak_ptr<Entity>&, const weak_ptr<Entity>&);
	void clean(void);

	Level* _level;
};

#endif
