
#include "stdafx.h"

#include <vector>
#include <iostream>
#include <string>

#include "geometry.h"
#include "transform.h"

struct Options
{
	Options()
	{
		nCores = 0;
		quickRender = quiet = verbose = openWindow = false;
		imageFile = "";
	}

	int nCores;
	bool quickRender;
	bool quiet, verbose;
	bool openWindow;
	std::string imageFile;
};

void pbrtInit(const Options &options)
{
}

void pbrtCleanup()
{
}

bool parseFile(const std::string &filename)
{
	std::cout << filename << std::endl;
	return true;
}

int main(int argc, char *argv[])
{
	Options options;
	std::vector<std::string> filenames;
	pbrtInit(options);

	using namespace namaste::geom;

	Vector v1(1.0f, 0.0f, 0.0f);	// x-axis
	Vector v2, v3;
	coordinateSystem(v1, &v2, &v3);

	std::cout << v2 << " " << v3 << std::endl;

	Matrix4x4 m;
	std::cout << m;

	if (filenames.size() == 0)
	{
		// Parse scene from standard input
	}
	else
	{
		// Parse scene from input file(s)
		for (auto it = filenames.cbegin(); it < filenames.cend(); ++it)
		{
			if (!parseFile(*it))
			{
				std::cerr << "Couldn't open scene file: " << *it << std::endl;
			}
		}
	}

	pbrtCleanup();

    return 0;
}

