#include "Server.h"



Server::Server()
{
	
}


Server::~Server()
{
}

void Server::Init()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Open a socket */
	if (!(sd = SDLNet_UDP_Open(7777)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Make space for the packet */
	if (!(p = SDLNet_AllocPacket(sizeof(Transform))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Wait for a connection, send data and term */
	quit = 0;

	
}

Transform* Server::update()
{
	/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
	if (SDLNet_UDP_Recv(sd, p))
	{

		/* Quit if packet contains "quit" */
		if (strcmp((char *)p->data, "quit") == 0)
			quit = 1;
	}
	
	return static_cast<Transform*>((void*)p->data);
}

void Server::Quit()
{
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}
