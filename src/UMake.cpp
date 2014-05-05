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
	// ������
	const std::list<std::string>& UMake::Generators()
	{
	}

	// ������
	const std::list<std::string>& UMake::Toolchains()
	{
	}

	// ƽ̨
	const std::list<std::string>& UMake::Platforms()
	{
	}

	// �ܹ�
	const std::list<std::string>& UMake::Architectures()
	{
	}
}

#else

#include <boost/program_options.hpp>

void printhelp(boost::program_options::options_description desc)
{
	std::cout << "ʹ��:" << std::endl;
	std::cout << "  UMake [ѡ��] Դ·��" << std::endl;

	desc.print(std::cout);

	std::cout << std::endl;
	std::cout << "������:" << std::endl;
	std::cout << std::endl;
	std::cout << "������:" << std::endl;
	std::cout << std::endl;
	std::cout << "ƽ̨:" << std::endl;
	std::cout << std::endl;
	std::cout << "�ܹ�:" << std::endl;
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

	boost::program_options::options_description builddesc("����ѡ��");
	builddesc.add_options()
		("generator,g", boost::program_options::value(&generator), "������")
		("toolchain,t", boost::program_options::value(&toolchain), "������")
		("platform,p", boost::program_options::value(&platform), "ƽ̨")
		("architecture,a", boost::program_options::value(&architecture), "�ܹ�")
		("sources_prefix,s", boost::program_options::value(&sources_prefix), "Դ·��")
		("install_prefix,i", boost::program_options::value(&install_prefix), "��װ·��")
		;

	boost::program_options::options_description helpdesc("����ѡ��");
	helpdesc.add_options()
		("help,h", "��ʾ����Ϣ")
		("version,v", "�汾��Ϣ")
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
		// �ռ���Ŀ�ļ�

	}
}

#endif