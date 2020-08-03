#include "Stream.h"
#include <assert.h>
Stream::Stream()
{
	this->Initialize();
}

Stream::Stream(UCHAR* stream, size_t size)
{
	this->Initialize();
	this->set(stream, size);
}

void Stream::Initialize()
{
	m_readPt = 0;
	m_offset = 0;
	ZeroMemory(&m_stream, sizeof(m_stream));
}

UCHAR* Stream::data()
{
	return m_stream.data();
}

size_t Stream::size()
{
	return m_offset;
}

void Stream::operator=(Stream& stream)
{
	this->set(stream.data(), stream.size());
}

void Stream::set(UCHAR* data, size_t size)
{
	this->m_offset = size;
	memcpy_s(this->m_stream.data(), this->m_stream.size(), (void*)data, size);
}

bool Stream::checkWriteBound(size_t len)
{
	if (m_offset + len > sizeof(m_stream)) {
		Log(L"Socket Stream Over!");
		assert(false);
		return false;
	}
	return true;
}
#define STREAM_WRITE(value)\
INT32 size = sizeof(value);\
if(this->checkWriteBound(size) == false){\
    return;\
}\
memcpy_s((void*)(m_stream.data() + m_offset),m_stream.size()-m_offset,\
(const void*)&value,size);\
m_offset += size;

void Stream::operator<<(const bool& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const INT8& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const UINT8& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const INT16& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const UINT16& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const INT32& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const UINT32& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const INT64& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const UINT64& value)
{
	STREAM_WRITE(value);
}

void Stream::operator<<(const std::string value)
{
	*this << (INT32)value.length();
	for (auto i : value)
		*this << i;
}

void Stream::operator<<(const std::wstring value)
{
	*this << (INT32)value.length();
	for (auto i : value)
		*this << i;
}

bool Stream::checkReadBound(size_t len)
{
	if (m_readPt + len > m_offset) {
		LogA(L"! readOffset : %d, size : %d, totalOffset : %d", m_readPt, len, m_offset);
		Log(L"! socket stream has not more memory!");
		assert(false);
		return false;
	}
	return true;
}

void Stream::read(void* retval, size_t len)
{
	memcpy_s(retval, len, (void*)(m_stream.data() + m_readPt), len);
	m_readPt += len;
}
#define STREAM_READ(type,retVal)\
size_t size = sizeof(type); \
if(this->checkReadBound(size) == false){\
 return;\
}\
this->read((void*)(retVal), size);
void Stream::operator>>(bool* retval)
{
	STREAM_READ(bool, retval);
}

void Stream::operator>>(INT8* retval)
{
	STREAM_READ(INT8, retval);
}

void Stream::operator>>(UINT8* retval)
{
	STREAM_READ(UINT8, retval);
}

void Stream::operator>>(INT16* retval)
{
	STREAM_READ(INT16, retval);
}

void Stream::operator>>(UINT16* retval)
{
	STREAM_READ(UINT16, retval);
}

void Stream::operator>>(INT32* retval)
{
	STREAM_READ(INT32, retval);
}

void Stream::operator>>(UINT32* retval)
{
	STREAM_READ(UINT32, retval);
}

void Stream::operator>>(INT64* retval)
{
	STREAM_READ(INT64, retval);
}

void Stream::operator>>(UINT64* retval)
{
	STREAM_READ(UINT64, retval);
}

void Stream::operator>>(std::string* retval)
{
	INT32 size;
	*this >> &size;
	if (this->checkReadBound(size) == false)
		return;

	char* buf = new char[size + 1];
	this->read((void*)(buf), size * sizeof(char));
	buf[size] = '\0';

	retval->clear();
	*retval = buf;

	delete buf;
}

void Stream::operator>>(std::wstring* retval)
{
	INT32 size;
	*this >> &size;
	if (this->checkReadBound(size) == false)
		return;

	WCHAR* buf = new WCHAR[size + 1];
	this->read((void*)buf, size * sizeof(WCHAR));
	buf[size] = '\0';

	retval->clear();
	*retval = buf;
	delete buf;
}