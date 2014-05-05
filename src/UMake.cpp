#include <iostream>
#include <string>
#include <filesystem>

namespace std
{
	namespace sys = tr2::sys;
}

#ifdef UMakeCore_EXPORTS

namespace UM
{
	// 生成器
	const std::list<std::string>& UMake::Generators()
	{
	}

	// 工具链
	const std::list<std::string>& UMake::Toolchains()
	{
	}

	// 平台
	const std::list<std::string>& UMake::Platforms()
	{
	}

	// 架构
	const std::list<std::string>& UMake::Architectures()
	{
	}
}

#else

#include <boost/program_options.hpp>

void printhelp(boost::program_options::options_description desc)
{
	std::cout << "使用:" << std::endl;
	std::cout << "  UMake [选项] 源路径" << std::endl;

	desc.print(std::cout);

	std::cout << std::endl;
	std::cout << "生成器:" << std::endl;
	std::cout << std::endl;
	std::cout << "工具链:" << std::endl;
	std::cout << std::endl;
	std::cout << "平台:" << std::endl;
	std::cout << std::endl;
	std::cout << "架构:" << std::endl;
}
void printversion()
{

}

int main(int argc, char** argv)
{
	std::string generator;
	std::string toolchain;
	std::string platform;
	std::string architecture;
	std::sys::path sources_prefix;
	std::sys::path install_prefix;

	boost::program_options::options_description builddesc("生成选项");
	builddesc.add_options()
		("generator,g", boost::program_options::value(&generator), "生成器")
		("toolchain,t", boost::program_options::value(&toolchain), "工具链")
		("platform,p", boost::program_options::value(&platform), "平台")
		("architecture,a", boost::program_options::value(&architecture), "架构")
		("sources_prefix,s", boost::program_options::value(&sources_prefix), "源路径")
		("install_prefix,i", boost::program_options::value(&install_prefix), "安装路径")
		;

	boost::program_options::options_description helpdesc("帮助选项");
	helpdesc.add_options()
		("help,h", "显示此信息")
		("version,v", "版本信息")
		;

	boost::program_options::options_description alldesc;
	alldesc.add(builddesc).add(helpdesc);

	boost::program_options::positional_options_description positionaldesc;
	positionaldesc.add("sources_prefix", -1);

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, alldesc), vm);
	boost::program_options::notify(vm);

	if (vm.count("help"))
	{
		printhelp(alldesc);
	}
	if (vm.count("version"))
	{
		printversion();
	}
	else if (sources_prefix.empty())
	{
		printhelp(alldesc);
	}
	else
	{
		// 收集项目文件

	}
}

#endif