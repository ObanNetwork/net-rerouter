#pragma once

#include <Windows.h>
#include <intrin.h>
#include <string>
#include <filesystem>

//deps
#include "ini_rw.h"

#define PRINT(__FMT__, ...) std::printf(__FMT__, __VA_ARGS__)

#ifdef DEBUG
#define PRINT_DEBUG(__FMT__, ...) PRINT("[ DEBUG ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#define PRINT_INFO(__FMT__, ...) PRINT("[ INFO ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#define PRINT_WARNING(__FMT__, ...) PRINT("[ WARNING ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#define PRINT_ERROR(__FMT__, ...) PRINT("[ ERROR ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#else
#define PRINT_DEBUG(__FMT__, ...)
#define PRINT_INFO(__FMT__, ...) PRINT("[ INFO ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#define PRINT_WARNING(__FMT__, ...) PRINT("[ WARNING ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#define PRINT_ERROR(__FMT__, ...) PRINT("[ ERROR ][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__)
#endif