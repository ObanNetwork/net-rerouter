#pragma once

#include <cstdint>
#include <functional>
#include <MinHook.h>

namespace hook
{
	template <typename T> void set(std::uint32_t address, T value)
	{
		DWORD protecc;
		VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &protecc);
		*reinterpret_cast<T*>(address) = value;
		VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), protecc, &protecc);
	}
}