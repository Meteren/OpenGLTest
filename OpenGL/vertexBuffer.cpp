#include "vertexBuffer.h"
#include "renderer.h"



VertexBuffer::VertexBuffer(const void* data, unsigned int size){
	CALL(glGenBuffers(1, &m_rendererId));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
	CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	
}

VertexBuffer::~VertexBuffer()
{
	CALL(glDeleteBuffers(1, &m_rendererId));
}

void VertexBuffer::Bind() const
{
	CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
}

void VertexBuffer::UnBind() const
{
	CALL(glBindBuffer(GL_ARRAY_BUFFER,0));
}

