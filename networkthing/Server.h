#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sdl\SDL_net.h>

union EventUnion
{
	SDL_Event SDLEvent;
	char buffer[sizeof(SDL_Event)];
};

class Server
{
public:
	Server();
	~Server();
	void Init();
	Transform* update();
	void Quit();

	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	int quit;
	EventUnion EU;
};

