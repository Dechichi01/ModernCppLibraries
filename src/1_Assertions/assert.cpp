#include "../Precompiled.h"

//----- Used for runtime debug assumptions
//#include <assert.h>//c assert
//#include <cassert>//cpp assert
#include <crtdbg.h>//windows, much better

//--- for compile time assumptinos: static_assert

#define ASSERT _ASSERTE //Good to change the implementation if needed

//int main() {
//	//static_assert(sizeof(int) == 16, "wtf??"); --> will fail
//	ASSERT(4 == 5);
//}