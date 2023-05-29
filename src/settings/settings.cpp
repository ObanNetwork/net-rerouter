#include "settings.hpp"

ini_t* settings::ini = 0;
const char* settings::ini_file = "net-rerouter.ini";

const char* settings::ip = "127.0.0.1";
std::uint16_t settings::port = USHRT_MAX;
settings::game_t settings::game = settings::game_t::Unknown;

void settings::init(settings::game_t game)
{
	settings::game = game;

#ifndef DISABLE_INI
	const char* port = "65565";

	switch (game)
	{
		case settings::game_t::NFSU: port = "10900"; break;
		case settings::game_t::NFSU2: port = "20920"; break;
		case settings::game_t::NFSMW: port = "30920"; break;
	}

	if (!std::filesystem::exists(settings::ini_file))
	{
		std::string ini_default = settings::va(
			"[network]\n"
			"ip = 127.0.0.1\n"
			"port = %s\n",
			port
		);

		settings::ini = ini_create(ini_default.data(), ini_default.length() + 1);
		ini_save(settings::ini, settings::ini_file);
	}

	settings::ini = ini_load(settings::ini_file);

	if (settings::ini == 0)
	{
		PRINT_ERROR("Unable to load %s!", settings::ini_file);
		return;
	}

	settings::ip = ini_get(settings::ini, "network", "ip");

	if (const char* port = ini_get(settings::ini, "network", "port"))
	{
		if (settings::is_num(port))
		{
			settings::port = std::stoi(port);
		}
	}
#else
	settings::ip = "127.0.0.1";

	switch (game)
	{
		case settings::game_t::NFSU: settings::port = 10900; break;
		case settings::game_t::NFSU2: settings::port = 20920; break;
		case settings::game_t::NFSMW: settings::port = 30920; break;
	}
#endif
}

bool settings::is_num(const char* input)
{
	char* p;
	std::strtol(input, &p, 10);
	return *p == 0;
}
