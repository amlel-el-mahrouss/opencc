/* -------------------------------------------

	Copyright (C) 2024 Amlal El Mahrouss, all rights reserved

	@file DynamicLinker64PEF.cc
	@brief: C++ 64-Bit PEF Linker.

------------------------------------------- */

/// @author EL Mahrouss Amlal (amlel)
/// @brief TQ 64-bit PEF Linker.
/// Last Rev: Sat Feb 24 CET 2024
/// @note Do not look up for anything with .code64/.data64/.zero64!
/// It will be loaded when the program loader will start the image.

//! Toolchain Kit.
#include <LibCompiler/Defines.h>

#include <LibCompiler/NFC/ErrorID.h>

//! Assembler Kit
#include <LibCompiler/AAL/AssemblyInterface.h>

//! Preferred Executable Format
#include <LibCompiler/NFC/XCOFF.h>
#include <LibCompiler/UUID.h>

//! Release macros.
#include <LibCompiler/Version.h>

//! Advanced Executable Object Format.
#include <LibCompiler/NFC/AE.h>
#include <cstdint>

#define kLinkerVersionStr "TQ 64-Bit Linker (ELF) %s, (c) Amlal El Mahrouss. 2024, all rights reserved.\n"

#define MemoryCopy(DST, SRC, SZ) memcpy(DST, SRC, SZ)
#define StringCompare(DST, SRC)	 strcmp(DST, SRC)

#define kPefNoCpu	 0U
#define kPefNoSubCpu 0U

#define kWhite "\e[0;97m"

#define kStdOut (std::cout << kWhite << "ld64: ")

#define kLinkerDefaultOrigin kPefBaseOrigin
#define kLinkerId			 (0x5046FF)
#define kLinkerAbiContainer	 "Container:ABI:"

/// @brief PEF stack size symbol.
#define kLinkerStackSizeSymbol "SizeOfReserveStack"

namespace Detail
{
	struct DynamicLinkerBlob final
	{
		std::vector<CharType> mBlob{};		   // PEF code/bss/data blob.
		UIntPtr				  mObjOffset{0UL}; // the offset of the PEF container header..
	};
} // namespace Detail

static Bool kFatBinaryEnable  = false;
static Bool kStartFound		  = false;
static Bool kDuplicateSymbols = false;
static Bool kVerbose		  = false;

/* object code and list. */
static std::vector<LibCompiler::String>		  kObjectList;
static std::vector<Detail::DynamicLinkerBlob> kObjectBytes;

static uintptr_t kMIBCount	= 8;
static uintptr_t kByteCount = 1024;

#define kPrintF			printf
#define kLinkerSplash() kPrintF(kWhite kLinkerVersionStr, kDistVersion)

///	@brief OpenNE 64-bit Linker.
/// @note This linker is made for XCOFF executable, thus OpenNE based OSes.
LIBCOMPILER_MODULE(DynamicLinker64XCOFF)
{
	return EXIT_SUCCESS;
}

// Last rev 13-1-24
