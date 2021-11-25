#pragma once

#include <pch.h>

struct VertexBufferElement
{
public:

	unsigned int type;
	unsigned int componentSize;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(float);

		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);

		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
		}

		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	
	VertexBufferLayout() : m_Stride(0)
	{ }

	void Clear()
	{
		if (!m_Elements.empty())
		{
			m_Elements.clear();
		}
		m_Stride = 0;
	}

	template<typename t>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false });
		m_Stride += sizeof(float) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += sizeof(unsigned int) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_Stride += sizeof(unsigned char) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};