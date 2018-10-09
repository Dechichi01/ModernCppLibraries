#include <algorithm>
#include <memory>

//int main()
//{
//	auto first = std::make_unique<int>(5);
//	auto second = std::make_unique<int>(6);
//
//	//if the compiler can't find function in the current namespace, it searches int the namespace of the values
//	// This is called ADL (Argument dependent lookup)
//	std::swap(first, second);
//
//	//Providing a custom swap function can greately improve performance  
//
//}