#pragma once

#include <xhash>

class UniversallyUniqueID
{
private:
	uint64_t m_UUID;

public:
	UniversallyUniqueID();
	UniversallyUniqueID(uint64_t uuid);

	operator uint64_t() const { return m_UUID; }
};

