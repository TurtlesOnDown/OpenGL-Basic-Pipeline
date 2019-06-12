#include "Includes.h"

#ifndef PATH
#define PATH

/* Defines a class to store files paths, and quickly access information from the path.
Path delimiter on Windows: '\\'
Path delimiter on Linx: '/'

Constructor Use:
CWD = Current Working Directory of main()
Path("examplePath/exampleFile.txt") -> CWD/examplePath/exampleFile.txt
Path("CWD/examplePath/exampleFile.txt") -> CWD/examplePath/exampleFile.txt
*/

class Path {
public:
	Path();
	Path(std::string);
	Path(const Path&);
	Path operator=(const Path&);

	bool operator==(const Path&);
	bool operator!=(const Path&);

	std::string getFile();
	std::string getFileType();
	std::string getPath();
	std::string getDirectory();

	static std::string CWD();
private:
	std::vector<std::string> path;
	std::string file;
};
#endif // !PATH
