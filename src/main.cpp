#include "hook.hpp"
#include "settings/settings.hpp"

static int(__cdecl* RunHTTP_)(const char*, int, int, int, int);
int __cdecl RunHTTP(const char* URL, int a2, int Title, int InnerText, int ButtonText)
{
	PRINT_INFO("0x%0x", _ReturnAddress());
	
	if (_ReturnAddress() == (void*)0x0049cefc)
	{
		std::string tos = settings::domain;

		if (!tos.ends_with("/")) tos += "/";
		tos += "tos";

		URL = tos.data();
	}
	else if (_ReturnAddress() == (void*)0x004bc671)
	{
		std::string news = settings::domain;

		if (!news.ends_with("/")) news += "/";
		news += "news";

		URL = news.data();
	}

	return RunHTTP_(URL, a2, Title, InnerText, ButtonText);
}

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

		if (MH_Initialize() == MH_OK);
		{
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

				//Buddy Server force until the proper method is figured out
				hook::set(0x00590BB6 + 0x1, settings::ip);
				hook::set(0x00590B98 + 0x1, settings::buddyPort);

				MH_CreateHook((void*)0x0049CDB0, RunHTTP, (void**)&RunHTTP_);
			}
			else
			{
				PRINT_ERROR("%s", "Unable to determine game!");
				return;
			}

			MH_EnableHook(MH_ALL_HOOKS);
		}


		PRINT_INFO("Setting IP to \"%s:%i\"", settings::ip, settings::port);
		PRINT_INFO("Setting BUDDY IP to \"%s:%i\"", settings::ip, settings::buddyPort);
	}
}