#include "MemoryCard.h"

MemoryCard::MemoryCard(std::string filename, std::string filePath)
{
	_filename = filePath + "/" + filename + ".txt";
}

MemoryCard::~MemoryCard()
{
}

void MemoryCard::Load()
{
	std::string line;
	std::ifstream file;

	file.open (_filename);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			LoadFromFile(line);
		}
		file.close();
	}
}

void MemoryCard::Save(std::vector<std::string> newLines)
{
	std::string line;
	std::vector<std::string> lines;
	std::fstream file;

	file.open(_filename);
	for (unsigned int i = 0; i < newLines.size(); i++)
	{
		file << newLines[i] + "\n";
	}
	file.close();
}

void MemoryCard::Overwrite(std::string oldLine, std::string newLine)
{
	//TODO: Change to find keyword and replace, instead of line.

	std::string line;
	std::fstream file;

	file.open(_filename);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (oldLine == line)
			{
				file << newLine;
				break;
			}
		}
		file.close();
	}
}

void MemoryCard::LoadFromFile(std::string line)
{
	Text* text = Text::GetInstance();

	//TODO: Implement functionality where loaded lines would apply (e.g. scores, player stats).
	
	//Testing purposes.
	printf(line.c_str());
}

bool MemoryCard::FileFound()
{
	std::ifstream file(_filename);
	return !file.fail();
}

void MemoryCard::CreateFile(std::vector<std::string> lines)
{
	std::string line;
	std::ofstream file;

	file.open(_filename);

	for (unsigned int i = 0; i < lines.size(); i++)
		file << lines[i] + "\n";

	file.close();
}