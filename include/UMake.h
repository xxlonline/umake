#pragma once

#include <list>

namespace UM
{
	class UMake
	{
	public:
		// 生成器类型
		enum class GeneratorType
		{
			Visual_Studio_12,
			GNU_Make,
		};
		// 工具链类型
		enum class ToolchainType
		{
			Visual_Studio_12,
			GCC_4_9,
			CLANG_3_3,
			MONO,
			Android_SDK
		};
		// 平台类型
		enum class PlatformType
		{
			Windows_XP,
			Windows_Vista,
			Windows_7,
			Windows_8,
			Windows_8_1,
			Windows_Phone_8_1,
			GNU_Linux,
			Android,
			IPhone,
		};
		// 架构类型
		enum class ArchitectureType
		{
			X86_32,
			X86_32_Intel,
			X86_32_Intel_Atom,
			X86_32_Intel_Core2,
			X86_32_Intel_Corei,
			X86_32_Intel_Corei_Nehalem,
			X86_32_Intel_Corei_Westmere,
			X86_32_Intel_Corei_SandyBridge,
			X86_32_Intel_Corei_IvyBridge,
			X86_32_Intel_Corei_Haswell,
			X86_32_AMD,
			X86_32_AMD_K8,
			X86_32_AMD_K10,
			X86_32_AMD_Bobcat,
			X86_32_AMD_Bulldozer,
			X86_32_AMD_Piledriver,
			X86_32_AMD_Steamroller,
			X86_32_AMD_Excavator,
			X86_64,
			X86_64_Intel,
			X86_64_Intel_Core2,
			X86_64_Intel_Corei,
			X86_64_Intel_Corei_Nehalem,
			X86_64_Intel_Corei_Westmere,
			X86_64_Intel_Corei_SandyBridge,
			X86_64_Intel_Corei_IvyBridge,
			X86_64_Intel_Corei_Haswell,
			X86_64_AMD,
			X86_64_AMD_K8,
			X86_64_AMD_K10,
			X86_64_AMD_Bobcat,
			X86_64_AMD_Bulldozer,
			X86_64_AMD_Piledriver,
			X86_64_AMD_Steamroller,
			X86_64_AMD_Excavator,
			ARM,
			ARM_2,
			ARM_2a,
			ARM_3,
			ARM_3m,
			ARM_4,
			ARM_4t,
			ARM_5,
			ARM_5t,
			ARM_5e,
			ARM_5te,
			ARM_6,
			ARM_6j,
			ARM_6t2,
			ARM_6z,
			ARM_6zk,
			ARM_6m,
			ARM_7,
			ARM_7a,
			ARM_7r,
			ARM_7m,
			ARM_8a,
			ARM_iwmmxt,
			ARM_iwmmxt2,
			ARM_ep9312
		};
	public:
		// 生成器
		static const std::list<std::string>& Generators();

		// 工具链
		static const std::list<std::string>& Toolchains();

		// 平台
		static const std::list<std::string>& Platforms();

		// 架构
		static const std::list<std::string>& Architectures();

	public:
		// 创建项目
		void CreateProject();

		// 查找项目
		void FindProject();

		// 生成项目
		void BuildProject();
	};
}