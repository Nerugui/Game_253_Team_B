#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sdl\SDL_net.h>
#include <glm\glm.hpp>


class Client
{
public:
	Client();
	~Client();

	void Init();
	int Update(Transform* trans);
	void Exit();
	UDPsocket	sd;
	IPaddress	srvadd;
	UDPpacket	*p;
	int			quit;
	int port = 7777;
	const char *ip = "127.0.0.1";
};

