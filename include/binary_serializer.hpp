#pragma once

#include <serializer_macros.hpp>

#define VALID_SERIALIZER            \
if(!m_buffer || m_buffer_size == 0) \
    return;

DW_BEGIN_NAMESPACE

class BinarySerializer
{
private:
    char* m_buffer;
    size_t m_buffer_size;
    
public:
    BinarySerializer()
    {
        m_buffer = nullptr;
        m_buffer_size = 0;
    }
    
    void set_buffer(char* buf, size_t size)
    {
        m_buffer = buf;
        m_buffer_size = size;
    }
    
    void serialize_string(const char* name, char* value, size_t offset)
    {
        VALID_SERIALIZER
        strcpy(m_buffer + offset, value);
    }
    
    template<typename T>
    void serialize_simple(const char* name, T& value, size_t offset)
    {
        VALID_SERIALIZER
        memcpy(m_buffer + offset, &value, sizeof(T));
    }
    
    template<typename T>
    void serialize_complex(const char* name, T& value, size_t offset)
    {
        
    }
    
    template<typename T>
    void serialize_simple_array(const char* name, T* value, size_t size, size_t offset)
    {
        VALID_SERIALIZER
        memcpy(m_buffer + offset, value, sizeof(T) * size);
    }
    
    template<typename T>
    void serialize_complex_array(const char* name, T* value, size_t size, size_t offset)
    {
        
    }
    
    void deserialize_string(const char* name, char* value, size_t offset)
    {
        VALID_SERIALIZER
        strcpy(value, m_buffer + offset);
    }
    
    template<typename T>
    void deserialize_simple(const char* name, T& value, size_t offset)
    {
        VALID_SERIALIZER
        memcpy(&value, m_buffer + offset, sizeof(T));
    }
    
    template<typename T>
    void deserialize_complex(const char* name, T& value, size_t offset)
    {
        
    }
    
    template<typename T>
    void deserialize_simple_array(const char* name, T* value, size_t size, size_t offset)
    {
        VALID_SERIALIZER
        memcpy(value, m_buffer + offset, sizeof(T) * size);
    }
    
    template<typename T>
    void deserialize_complex_array(const char* name, T* value, size_t size, size_t offset)
    {
        
    }
};

DW_END_NAMESPACE
