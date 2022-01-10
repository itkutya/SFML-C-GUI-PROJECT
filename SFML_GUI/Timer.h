#pragma once

//TY Cherno

#include <stdlib.h>
#include <chrono>
#include <string>
#include <iostream>

class Timer
{
public:

	Timer();
	virtual ~Timer();

	const void Reset();
	auto Elapsed();

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

class ScopedTimer
{
public:
	ScopedTimer(const std::string& name);
	virtual ~ScopedTimer();

private:
	std::string m_name;
	Timer m_timer;
};