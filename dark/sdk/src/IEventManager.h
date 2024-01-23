#pragma once

#include <string>
#include <cstdint>
#include <functional>

#define HASH(str) uintptr_t(std::hash<std::string>{}(str))

template<typename T, typename R, typename... args>
inline void* void_cast(R(T::* f)(args...))
{
	union
	{
		R(T::* pf)(args...);
		void* p;
	};
	pf = f;
	return p;
}

class IEventManager
{
public:
	virtual ~IEventManager() = default;

public:
	virtual void subscribe(uintptr_t event, void* callback) = 0;
	virtual void unsubscribe(uintptr_t event, void* callback) = 0;
	
	virtual void emit(uintptr_t event, void* data) = 0;
};