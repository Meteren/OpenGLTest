#pragma once

class IndexBuffer 
{
private:
	unsigned int m_rendererId;
	unsigned int m_count;
public:
	IndexBuffer(unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
};
