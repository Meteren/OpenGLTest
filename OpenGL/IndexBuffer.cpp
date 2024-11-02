#include "IndexBuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int count) : m_count(count)
{
	CALL(glGenBuffers(1, &m_rendererId));
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
	CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	CALL(glDeleteBuffers(1,&m_rendererId));
}

void IndexBuffer::Bind() const
{
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
}

void IndexBuffer::UnBind() const
{
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
