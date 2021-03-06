#include "UtilityFunctions.h"
#include <random>
#include <memory>

namespace UTIL
{
	std::random_device rd;
	std::mt19937 mtrand(rd());

	//範囲内でランダムな値を指定個数分取得する(lowerLimit以上upperLimit以下)
	int  GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}
}