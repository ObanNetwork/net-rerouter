#include "hook.hpp"
#include "settings/settings.hpp"

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
#ifdef DEBUG
		AllocConsole();
		SetConsoleTitleA("net-rerouter console");

		std::freopen("CONOUT$", "w", stdout);
		std::freopen("CONIN$", "r", stdin);
#endif

		if (!std::strcmp(reinterpret_cast<char*>(0x006CC054), "NFS Underground"))
		{
			settings::init(settings::game_t::NFSU);

			//*pcnfs04.ea.com reroute
			hook::set(0x005498F6 + 0x1, settings::ip);
			hook::set(0x0054D52A + 0x1, settings::ip);
			hook::set(0x006F1F60, settings::port);
		}
		else if (!std::strcmp(reinterpret_cast<char*>(0x0078E8F4), "NFS Underground 2"))
		{
			settings::init(settings::game_t::NFSU2);

			//*pcnfs05.ea.com reroute
			hook::set(0x005886B0 + 0x1, settings::ip);
			hook::set(0x007FBE00, settings::port);
		}
		else
		{
			PRINT_ERROR("%s", "Unable to determine game!");
			return;
		}

		//PRINT_DEBUG("Setting IP to \"%s:%i\"", settings::ip, settings::port);
		//PRINT_DEBUG("Setting BUDDY IP to \"%s:%i\"", settings::ip, settings::buddyPort);
	}
}