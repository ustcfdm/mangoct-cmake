#include "stdafx.h"
#include "FpjClass.h"

int main(int argc, char* argv[])
{
	namespace mg = mango;
	namespace fs = std::filesystem;

	if (argc == 1)
	{
		printf( "This is mangoct forward projection tool, please input config file name as arguments.\n");
		return 0;
	}

	for (int idx = 1; idx < argc; idx++)
	{
		mg::FpjClass fpj;

		printf("Loading config %s...\n", argv[idx]);

		fpj.ReadConfigFile(argv[idx]);

		fpj.InitParam();

		fs::path inDir(mg::FpjClass::config.inputDir);
		fs::path outDir(mg::FpjClass::config.outputDir);

		for (size_t i = 0; i < mg::FpjClass::config.inputFiles.size(); i++)
		{
			printf("    \nForward projection %s ...", mg::FpjClass::config.inputFiles[i].c_str());

			fpj.ReadImageFile((inDir / mg::FpjClass::config.inputFiles[i]).string().c_str());

			fpj.ForwardProjectionBilinearAndSave((outDir / mg::FpjClass::config.outputFiles[i]).string().c_str());

			printf("\n->\tSaved to file %s\n", mg::FpjClass::config.outputFiles[i].c_str());
		}
	}
	return 0;
}