#pragma once
#include<string>
#include<vector>
struct ModelPathParam
{
public:
	std::string basePath;
	std::string motionPath;
	std::string modelPath;

	std::vector <std::string> animationPath;
};

