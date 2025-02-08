/* -------------------------------------------

	Copyright (C) 2024 Amlal El Mahrouss, all rights reserved

------------------------------------------- */

/// @file opencc.cc
/// @brief OpenNE C++ frontend compiler.

#include <LibCompiler/Defines.h>
#include <LibCompiler/Version.h>
#include <iostream>
#include <cstring>
#include <vector>

LC_IMPORT_C int CPlusPlusPreprocessorMain(int argc, char const* argv[]);
LC_IMPORT_C int CompilerCPlusPlusX8664(int argc, char const* argv[]);
LC_IMPORT_C int AssemblerMainAMD64(int argc, char const* argv[]);

int main(int argc, char const* argv[])
{
	for (size_t index_arg = 0; index_arg < argc; ++index_arg)
	{
		if (strstr(argv[index_arg], "--cl:h"))
		{
			std::printf("opencc: Frontend C/C++ Compiler.\n");
			std::printf("opencc: Version: %s, Release: %s.\n", kDistVersion, kDistRelease);
			std::printf("opencc: Written by Amlal El Mahrouss, Copyright (C) 2024-2025 Amlal El Mahrouss, all rights reserved.\n");
			std::printf("LibCompiler: Written by Amlal El Mahrouss, Copyright (C) 2024-2025 Amlal El Mahrouss, all rights reserved.\n");

			return 0;
		}
	}

	if (auto code = CPlusPlusPreprocessorMain(argc, argv); code)
	{
		std::printf("opencc: frontend exited with code %i.\n", code);
		return 1;
	}
	else
	{
		std::vector<std::string> args_list_cxx;
		std::vector<std::string> args_list_asm;

		for (size_t index_arg = 0; index_arg < argc; ++index_arg)
		{
			if (strstr(argv[index_arg], ".cxx") ||
				strstr(argv[index_arg], ".cpp") ||
				strstr(argv[index_arg], ".cc") ||
				strstr(argv[index_arg], ".c++") ||
				strstr(argv[index_arg], ".C"))
			{
				std::string arg = argv[index_arg];

				arg += ".pp.masm";
				args_list_asm.push_back(arg);

				arg = argv[index_arg];
				arg += ".pp";

				args_list_cxx.push_back(arg);
			}
			else if (strstr(argv[index_arg], ".c"))
			{
				std::printf("opencc: error: C support is not ready yet.\n");
				return EXIT_FAILURE;
			}
		}

		for (auto& cli : args_list_cxx)
		{
			const char* arr_cli[] = {argv[0], cli.data()};

			if (auto code = CompilerCPlusPlusX8664(2, arr_cli); code)
			{
				std::printf("opencc: assembler exited with code %i.", code);
			}
		}

		for (auto& cli : args_list_asm)
		{
			const char* arr_cli[] = {argv[0], cli.data()};

			if (auto code = AssemblerMainAMD64(2, arr_cli); code)
			{
				std::printf("opencc: assembler exited with code %i.", code);
			}
		}
	}

	return 0;
}
