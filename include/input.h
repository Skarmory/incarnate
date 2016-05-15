#ifndef input_h
#define input_h

#include <ncurses.h>
#include <memory>
#include "command.h"

class InputManager {
public:
	InputManager(std::shared_ptr<Entity>&, bool&);
	std::unique_ptr<Command::ICommand> handle_input(void);
private:
	std::shared_ptr<Entity>& _player;
	bool& _is_running;
};

#endif
