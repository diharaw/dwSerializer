#pragma once

#include <stdio.h>
#include <iostream>

class ISerializer;

struct TypeDescriptor
{
    const char* m_name;
    size_t m_size;
    
    TypeDescriptor(const char* name, size_t size) : m_name(name), m_size(size) {}
	virtual void serialize(void* obj, const char* name, bool trivial, ISerializer* serializer) = 0;
	virtual void deserialize(void* obj, const char* name, bool trivial, ISerializer* serializer) = 0;
};

template <typename T>
TypeDescriptor* get_primitive_descriptor();

struct TypeResolver
{
    template <typename T> static char func(decltype(&T::Reflection));
    template <typename T> static int func(...);
    template <typename T>
    struct is_reflected
    {
        enum { value = (sizeof(func<T>(nullptr)) == sizeof(char)) };
    };

    template <typename T, typename std::enable_if<is_reflected<T>::value, int>::type = 0>
    static TypeDescriptor* get()
    {
        return &T::Reflection;
    }

    template <typename T, typename std::enable_if<!is_reflected<T>::value, int>::type = 0>
    static TypeDescriptor* get()
    {
        static auto desc = get_primitive_descriptor<T>();
        return desc;
    }
};

// Specializations

struct TypeDescriptor_Struct : public TypeDescriptor
{
    struct Member
    {
        const char*     m_name;
        size_t          m_offset;
        TypeDescriptor* m_type;
        bool            m_pointer;
		bool			m_trivial = false;
        
        Member(const char* name, size_t offset, TypeDescriptor* type, bool pointer) : m_name(name), m_offset(offset), m_type(type), m_pointer(pointer) {}
    };
    
    int m_num_members;
    Member* m_members;
    
    TypeDescriptor_Struct(const char* name, size_t size, void(*initialize)());
    void init(Member* members, int num_members);
	void serialize(void* obj, const char* name, bool trivial, ISerializer* serializer) override;
	void deserialize(void* obj, const char* name, bool trivial, ISerializer* serializer) override;
};

struct TypeDescriptor_Enum : public TypeDescriptor
{
    struct Constant
    {
        const char* m_name;
        const char* m_desc;
        int         m_value;
        
        Constant(const char* name, const char* desc, int value) : m_name(name), m_desc(desc), m_value(value) {}
    };
    
    TypeDescriptor_Enum(const char* name, size_t size);
    int current_value_index(int value);
	void serialize(void* obj, const char* name, bool trivial, ISerializer* serializer) override;
	void deserialize(void* obj, const char* name, bool trivial, ISerializer* serializer) override;
    
    int       m_num_constants;
    Constant* m_constants;
};
