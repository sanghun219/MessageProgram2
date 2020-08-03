#pragma once
#include "../ServLibrary.h"
class Stream {
private:
	size_t m_offset;
	size_t m_readPt;
	std::array<UCHAR, SOCKET_BUF_SIZE> m_stream;
public:
	Stream();
	Stream(UCHAR* stream, size_t size);
	void Initialize();

	UCHAR* data();
	size_t size();

	void operator = (Stream& stream);
	void set(UCHAR* stream, size_t size);

	// write
	bool checkWriteBound(size_t len);

	template<class T>
	void operator << (const T& value);
	void operator << (const bool& value);
	void operator << (const INT8& value);
	void operator << (const UINT8& value);
	void operator << (const INT16& value);
	void operator << (const UINT16& value);
	void operator << (const INT32& value);
	void operator << (const UINT32& value);
	void operator << (const INT64& value);
	void operator << (const UINT64& value);

	template<class T>
	void operator << (const std::vector<T>& value);
	void operator << (const std::string value);
	void operator << (const std::wstring value);

	// read
	bool checkReadBound(size_t len);
	void read(void* retval, size_t len);

	template<class T>
	void operator >> (T* retval);

	void operator >> (bool* retval);
	void operator >> (INT8* retval);
	void operator >> (UINT8* retval);
	void operator >> (INT16* retval);
	void operator >> (UINT16* retval);
	void operator >> (INT32* retval);
	void operator >> (UINT32* retval);
	void operator >> (INT64* retval);
	void operator >> (UINT64* retval);

	template <typename T>
	void operator >> (std::vector<T>* retval);

	void operator >> (std::string* retval);
	void operator >> (std::wstring* retval);
};

template<class T>
inline void Stream::operator<<(const T& value)
{
	STREAM_WRITE(value);
}

template<class T>
inline void Stream::operator<<(const std::vector<T>& value)
{
	*this << value.size();
	for (auto i : value) {
		*this << i;
	}
}

template<class T>
inline void Stream::operator>>(T* retval)
{
	STREAM_READ(T, retval);
}

template<typename T>
inline void Stream::operator>>(std::vector<T>* retval)
{
	size_t size;
	*this >> &size;

	for (size_t i = 0; i < size; i++) {
		T tmp;
		*this >> &tmp;
		retval->push_back(tmp);
	}
}
