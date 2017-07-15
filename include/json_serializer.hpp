#pragma once

#include <serializer_macros.hpp>

// Json Includes
#include <json.hpp>

DW_BEGIN_NAMESPACE

class JsonSerializer
{
private:
    nlohmann::json m_json;
    
public:
    JsonSerializer()
    {
        
    }
    
    void serialize_string(const char* name, std::string value)
    {
        m_json[name] = value;
    }
    
    template<typename T>
    void serialize_simple(const char* name, T& value)
    {
        m_json[name] = value;
    }
    
    template<typename T>
    void serialize_complex(const char* name, T& value)
    {
        JsonSerializer serializer;
        value.serialize(serializer);
        m_json[name] = serializer.m_json;
    }
    
    template<typename T>
    void serialize_simple_array(const char* name, T* value, size_t size)
    {
        nlohmann::json array = nlohmann::json::array();
        
        for(int i = 0; i < size; i++)
            array.push_back(value[i]);
        
        m_json[name] = array;
    }
    
    template<typename T>
    void serialize_complex_array(const char* name, T* value, size_t size)
    {
        nlohmann::json array = nlohmann::json::array();
        
        for(int i = 0; i < size; i++)
        {
            JsonSerializer serializer;
            value[i].serialize(serializer);
            
            array.push_back(serializer.m_json);
        }
    
        m_json[name] = array;
    }
    
    void deserialize_string(const char* name, char** value)
    {
        if (m_json.find(name) != m_json.end())
        {
            std::string str = m_json[name];
            *value = (char*)malloc(str.size() + 1);
            strcpy(*value, str.c_str());
        }
    }
    
    void deserialize_string(const char* name, const char** value)
    {
        if (m_json.find(name) != m_json.end())
        {
            std::string str = m_json[name];
            *value = (const char*)malloc(str.size() + 1);
            strcpy((char*)*value, str.c_str());
        }
    }
    
    void deserialize_string(const char* name, std::string& value)
    {
        if (m_json.find(name) != m_json.end())
            value = m_json[name];
    }
    
    template<typename T>
    void deserialize_simple(const char* name, T& value)
    {
        if (m_json.find(name) != m_json.end())
            value = m_json[name];
    }
    
    template<typename T>
    void deserialize_complex(const char* name, T& value)
    {
        if (m_json.find(name) != m_json.end())
        {
            nlohmann::json obj = m_json[name];
            JsonSerializer serializer;
            serializer.m_json = obj;
            value.deserialize(serializer);
        }
    }
    
    template<typename T>
    void deserialize_simple_array(const char* name, T* value, size_t size)
    {
        if (m_json.find(name) != m_json.end())
        {
            nlohmann::json array = m_json[name];
            
            for(int i = 0; i < size; i++)
            value[i] = array[i];
        }
    }
    
    template<typename T>
    void deserialize_complex_array(const char* name, T* value, size_t size)
    {
        if (m_json.find(name) != m_json.end())
        {
            nlohmann::json array = m_json[name];
            
            for(int i = 0; i < size; i++)
            {
                JsonSerializer serializer;
                serializer.m_json = array[i];
                value[i].deserialize(serializer);
            }
        }
    }
    
    const char* print()
    {
        return m_json.dump(4).c_str();
    }
};

DW_END_NAMESPACE
