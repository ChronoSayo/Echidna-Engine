#pragma once
#ifndef MEMORYCARD_H_INCLUDED
#define MEMORYCARD_H_INCLUDED

#include "Text.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/*Save feature. Saves into text into a .txt. Includes load file and a check if file exists; else it creates one.*/
class MemoryCard
{
public:
	MemoryCard(std::string filename, std::string filePath);
	~MemoryCard();
	
	/*Returns true if file exists*/
	bool FileFound();
	/*Creates a new file.*/
	void CreateFile(std::vector<std::string> lines);

	/*Reads from the file.*/
	void Load();
	/*Saves new lines into the file.*/
	void Save(std::vector<std::string> newLines);
	/*Finds the old line and replaces it with new.*/
	void Overwrite(std::string oldLine, std::string newLine);

private:
	std::string _filename;

	void LoadFromFile(std::string line);
};

#endif