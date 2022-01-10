#include "pch.h"

#include "Timer.h"

Timer::Timer()
{
	this->Reset();
}

Timer::~Timer()
{

}

const void Timer::Reset()
{
	this->m_start = std::chrono::high_resolution_clock::now();
}

auto Timer::Elapsed()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->m_start).count();
}

ScopedTimer::ScopedTimer(const std::string& name) : m_name(name)
{

}

ScopedTimer::~ScopedTimer()
{
	auto time = this->m_timer.Elapsed();

	std::cout << this->m_name << ": " << time << " us." << std::endl;
}