#pragma once

#include <Windows.h>
#include <memory>

#include "../Precompiled.h"

struct work_deleter
{
	typedef PTP_WORK pointer;

	void operator()(pointer value) const
	{
		CloseThreadpoolWork(value);
	}
};

//int main() {
//	typedef std::unique_ptr<PTP_WORK, work_deleter> work;
//
//	auto w = work
//	{
//		CreateThreadpoolWork([](PTP_CALLBACK_INSTANCE, void*, PTP_WORK)
//		{
//			
//		},
//		nullptr, nullptr)
//	};
//
//	if (w)
//	{
//		SubmitThreadpoolWork(w.get());
//		WaitForThreadpoolWorkCallbacks(w.get(), false);
//	}
//}
