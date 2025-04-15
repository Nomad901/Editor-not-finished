#include "outro.h"

void outro::appendFunctional(Type type, std::function<void(void)> func)
{
	pImpl->mapOfFunctions.emplace(std::make_pair(type, func));
}

void outro::manageFunctional(int& number)
{
	Type type = static_cast<Type>(number);
	auto result = pImpl->mapOfFunctions.find(type);
	if (result != pImpl->mapOfFunctions.end()) {
		pImpl->number = static_cast<int>(result->first);
		result->second();
	}
	std::cout << "Error! This type does not exist!\n";
}
