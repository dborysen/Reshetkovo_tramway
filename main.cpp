/*
** Трамваи города Решетково
** Борисенко Дмитрий
*/

#include "Reshetkovo.hpp"

int main()
{
	Reshetkovo newFile;

	newFile.enterFileName();
	std::cout << newFile.getLightsNum() << std::endl;
	return (0);
}
