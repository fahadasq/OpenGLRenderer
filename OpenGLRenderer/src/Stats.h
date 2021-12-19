#pragma once
static class Stats
{
public:
	static void AddDrawCalls(unsigned int count);
	static void ResetDrawCalls();
	static const unsigned int& GetDrawCalls();

	static void ResetAll();

private:
	Stats() { }

	static unsigned int m_DrawCalls;
};

