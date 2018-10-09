/*
	Used in destructors
*/

#include <Windows.h>
#include "../Precompiled.h"

#ifdef _DEBUG
#define VERIFY ASSERT
#else
#define VERIFY(ex) (ex)
#endif

struct ManualResetEvent
{
	HANDLE m_Handle;

	ManualResetEvent() {
		m_Handle = CreateEvent(nullptr, true, false, nullptr);

		if (!m_Handle) {
			//TODO: throw
		}
	}

	~ManualResetEvent() {
		VERIFY(CloseHandle(m_Handle));
	}
};

//int main() {
//	ManualResetEvent e;
//	auto e1 = e;
//}