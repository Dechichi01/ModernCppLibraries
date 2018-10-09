#include "../Precompiled.h"
#include <utility>

namespace KennyKerr
{
	template <typename T>
	class unique_handle
	{
		typedef typename T::pointer pointer;

		pointer m_value;

		void close() noexcept
		{
			if (*this) {
				T::close(m_value);
			}
		}

	public:
		~unique_handle() noexcept
		{
			close();
		}

		explicit unique_handle(pointer value = T::invalid()) noexcept :
			m_value(value)
		{}

		unique_handle(const unique_handle& other) = delete;
		unique_handle& operator=(const unique_handle& other) = delete;

		unique_handle(unique_handle&& other) noexcept
			: m_value(other.m_value)
		{}

		unique_handle& operator=(const unique_handle&& other) noexcept
		{
			if (&other != this) {
				reset(other.release());
			}

			return *this;
		}

		explicit operator bool() const noexcept
		{
			return m_value != T::invalid();
		}

		pointer get() const noexcept
		{
			return m_value;
		}

		pointer release() noexcept
		{
			auto temp = m_value;
			m_value = T::invalid();
			return temp;
		}

		bool reset(pointer value = T::invalid()) noexcept
		{
			if (m_value != value) 
			{
				close();
				m_value = value;
			}

			return static_cast<bool>(*this);
		}
	};

	struct null_handle_traits
	{
		typedef HANDLE pointer;

		constexpr static pointer invalid() noexcept
		{
			return nullptr;
		}
		
		static void close(pointer value) noexcept
		{
			LOG("Closing handle");
			CloseHandle(value);
		}
	};

	struct invalid_handle_traits
	{
		typedef HANDLE pointer;

		constexpr static pointer invalid() noexcept
		{
			return INVALID_HANDLE_VALUE;
		}

		static void close(pointer value) noexcept
		{
			LOG("Closing file handle");
			CloseHandle(value);
		}
	};

	typedef unique_handle<null_handle_traits> null_handle;
	typedef unique_handle<invalid_handle_traits> invalid_handle;
}

//int main()
//{
//	HANDLE ptr = nullptr;
//	auto h = KennyKerr::null_handle{ ptr};
//
//	if (h) 
//	{
//		LOG("This should not happen");
//	}
//
//	auto event = KennyKerr::null_handle
//	{
//		CreateEvent(nullptr, true, false, nullptr)
//	};
//
//	if (event) {
//		LOG("Event is valid");
//		SetEvent(event.get());
//	}
//
//	if (event.reset(CreateEvent(nullptr, true, false, nullptr))) 
//	{
//		LOG("Reset to new event");
//	}
//
//	auto copy = std::move(event);
//}

//int main()
//{
//	auto filename = LR"(C:\Dev\Cpp\ModernCppLibraries\ModernCppLibraries\src\3_SmartClasses\unique_handle.cpp)";
//
//	auto file = KennyKerr::invalid_handle
//	{
//		CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)
//	};
//
//	if (!file)
//	{
//		LOG("FAILED to open file!");
//		return 0;
//	}
//
//	auto size = LARGE_INTEGER();
//
//	if (!GetFileSizeEx(file.get(), &size))
//	{
//		LOG("Failed to get file size");
//		return 0;
//	}
//
//	//check not empty
//	if (size.QuadPart == 0)
//	{
//		LOG("File is empty");
//		return 0;
//	}
//
//	KennyKerr::null_handle map(CreateFileMapping(file.get(), nullptr, PAGE_READONLY, 0, 0, nullptr));
//
//	if (!map)
//	{
//		LOG("Create file mapping failed");
//		return 0;
//	}
//
//	file.reset();
//}