#include "pch.h"
#include "Stats.h"

unsigned int Stats::m_DrawCalls;

void Stats::AddDrawCalls(unsigned int count)
{
	m_DrawCalls += count;
}

void Stats::ResetDrawCalls()
{
	m_DrawCalls = 0;
}

const unsigned int& Stats::GetDrawCalls()
{
	return m_DrawCalls;
}
