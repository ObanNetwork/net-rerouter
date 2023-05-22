#pragma once

class settings
{
public:
	static enum game_t
	{
		Unknown,
		NFSU,
		NFSU2,
	};

	static void init(game_t game);
	static bool is_num(const char* input);

	static const char* ip;
	static std::uint16_t port;
	static std::uint16_t buddyPort;
	static const char* domain;
	static game_t game;

	static std::string va(const char* fmt, ...)
	{
		auto va = ::va_list();

		va_start(va, fmt);

		char result[512]{};

		std::vsprintf(result, fmt, va);

		return std::string(result);
	}


private:
	static ini_t* ini;
	static const char* ini_file;
};