#include "../Common/Includes.h"

#ifndef PATH
#define PATH

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
