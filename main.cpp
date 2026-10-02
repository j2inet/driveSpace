#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ansi.h"


struct DirectoryInfo {
	std::string name;
	size_t size;
};

DirectoryInfo getDirectorySize(std::string sourcePath) 
{

	std::cout.imbue(std::locale("en_US.UTF-8")); 
	DirectoryInfo retVal = { sourcePath, 0 };
	std::vector<std::string> entryList { sourcePath };
	size_t fileCount = 0;
	do
	{
		auto current = entryList.front();
		entryList.erase(entryList.begin());
		try {
			++fileCount;
			if(fileCount % 1000 == 0)
			{
			std::cout << ANSI::blue() << "\rProcessing directory: " << current <<ANSI::green() << "(" << fileCount << ")" << ANSI::eraseLineAndCarriageReturn() << "   "<< std::flush;
			}
			for(const auto& entry:std::filesystem::directory_iterator(current, std::filesystem::directory_options::skip_permission_denied))
			{
				if(entry.is_directory() && !entry.is_symlink())
				{
					entryList.push_back(entry.path().string());
				}
				else if (entry.is_regular_file())
				{
					size_t entrySize = std::filesystem::file_size(entry.path().string());
					retVal.size += entrySize;
				}
			}
		}
		catch ( const std::filesystem::filesystem_error& e)
		{
			std::cerr << ANSI::red() << "Error:" << ANSI::reset() << e.what() << std::endl;
		}
	}
	while(entryList.size());
	return retVal;
}

void showDirectorySizes(const std::vector<DirectoryInfo>& directoryInfos) {
	size_t maxSize = 0;
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
    } else {
		w.ws_col = 80; // Default width
		w.ws_row = 24; // Default height
    }

	for(const auto& dirInfo : directoryInfos) {
		if(dirInfo.size > maxSize) {
			maxSize = dirInfo.size;
		}
	}
	for(const auto& dirInfo : directoryInfos) {
		size_t barWidth = static_cast<float>(dirInfo.size) / maxSize * w.ws_col;
		std::cout << ANSI::green() << dirInfo.name << ANSI::reset() << " " << dirInfo.size << std::endl;
		std::cout << ANSI::blue();
		for(size_t i = 0; i < barWidth; ++i) {
			std::cout << "=";
		}
		std::cout << ANSI::reset() << std::endl;
	}
}


int main(int argc, char** argv) 
{
	std::cout << "Getting drive space" << std::endl;
	std::string startPath = "./";
	if(argc > 1)
		startPath = argv[1];
	std::vector<DirectoryInfo> directoryInfos;
	try 
	{
		for(const auto& entry : std::filesystem::directory_iterator(startPath))
		{
			
			if(entry.is_regular_file() && !entry.is_directory()) {
				size_t size = std::filesystem::file_size(entry.path().string());
				std::cout << entry.path().string() << " " << size <<  std::endl;
			}
			else if(entry.is_directory()) {
				if(entry.path().string().ends_with("/Library"))
					continue;
				std::cout << ANSI::blue() << "Processing directory: " << entry.path().string() << ANSI::reset() << std::endl;
				DirectoryInfo dirInfo = getDirectorySize(entry.path().string());
				directoryInfos.push_back(dirInfo);	
				std::cout <<ANSI::blue() << dirInfo.name << " " << ANSI::green() <<  dirInfo.size << ANSI::reset() << std::endl;
			}
		}
		//Sort the DirectoryInfo vector by size
		std::sort(directoryInfos.begin(), directoryInfos.end(), [](const DirectoryInfo& a, const DirectoryInfo& b) {
			return a.size > b.size;
		});
		std::cout << "\r\n\r\n" << "Directory sizes:" << std::endl;
		for(const auto& dirInfo : directoryInfos) {
			std::cout << ANSI::green() << dirInfo.name << ANSI::reset() << " " << dirInfo.size << std::endl;
		}
	} 
	catch(const std::filesystem::filesystem_error& e)
	{
		std::cerr << ANSI::red() << "Error:" << ANSI::reset() << e.what() << std::endl;
	}
	showDirectorySizes(directoryInfos);
	return 0;
}
