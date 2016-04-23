#include "Client.h"



Client::Client()
{
}


Client::~Client()
{
}

void Client::Init()
{
	/* Check for parameters */
	if (port < 999)
	{
		fprintf(stderr, "Usage: %i host port\n", port);
		exit(EXIT_FAILURE);
	}

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, ip,port))
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %i): %s\n", ip, port), SDLNet_GetError();
		exit(EXIT_FAILURE);
	}

	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(sizeof(Transform))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

int Client::Update(Transform* trans) 
{
	memcpy(p->data, trans, sizeof(Transform));
	p->len = sizeof(Transform)+1;


	p->address.host = srvadd.host;	/* Set the destination host */
	p->address.port = srvadd.port;	/* And destination port */

	SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */

								/* Quit if packet contains "quit" */
	if (!strcmp((char *)p->data, "quit"))
	{
		return 1;
	}
	return 0;
}

void Client::Exit()
{
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}
