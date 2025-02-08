/* -------------------------------------------

	Copyright (C) 2024-2025 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

/// @brief CRT exit, with exit code (!!! exits all threads. !!!)
/// @param code the exit code.
/// @return the return > 0 for non successful.
extern "C" int exit(int code);

/// @brief Standard C++ namespace
namespace std::process
{
	inline int exit(int code)
	{
		exit(code);
		return 0;
	}
} // namespace std::process
