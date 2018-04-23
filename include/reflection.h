#pragma once

#include "type_descriptor.h"

template <typename TYPE>
const char* type_name()
{
    assert(false);
    return nullptr;
}

template <typename TYPE>
struct IsPointer
{
    static bool val;
};

template <typename TYPE>
struct IsPointer<TYPE*>
{
    static bool val;
};

template <typename TYPE>
struct StripPointer
{
    typedef TYPE Type;
};

template <typename TYPE>
struct StripPointer<TYPE*>
{
    typedef TYPE Type;
};

template <typename TYPE>
bool IsPointer<TYPE>::val = false;

template <typename TYPE>
bool IsPointer<TYPE*>::val = true;

#define DECLARE_PRIMITIVE_TYPENAME(TYPE) template <> \
inline const char* type_name<TYPE>() { return #TYPE; }

DECLARE_PRIMITIVE_TYPENAME(float)
DECLARE_PRIMITIVE_TYPENAME(char)
DECLARE_PRIMITIVE_TYPENAME(bool)
DECLARE_PRIMITIVE_TYPENAME(double)
DECLARE_PRIMITIVE_TYPENAME(int32_t)
DECLARE_PRIMITIVE_TYPENAME(uint32_t)
DECLARE_PRIMITIVE_TYPENAME(int16_t)
DECLARE_PRIMITIVE_TYPENAME(uint16_t)
DECLARE_PRIMITIVE_TYPENAME(int64_t)
DECLARE_PRIMITIVE_TYPENAME(uint64_t)


#define REFLECT() static TypeDescriptor_Struct Reflection; \
static void init_reflection();

#define BEGIN_DECLARE_REFLECT(TYPE) TypeDescriptor_Struct TYPE::Reflection{ #TYPE, sizeof(TYPE), TYPE::init_reflection }; \
void TYPE::init_reflection()                                                          \
{                                                                                     \
using T = TYPE;                                                                   \
static TypeDescriptor_Struct::Member members[] = {

#define END_DECLARE_REFLECT()   };                                                                               \
Reflection.init(members, sizeof(members)/sizeof(TypeDescriptor_Struct::Member)); \
}

#define REFLECT_MEMBER(MEMBER) { #MEMBER, offsetof(T, MEMBER), TypeResolver::get<StripPointer<decltype(MEMBER)>::Type>(), IsPointer<decltype(MEMBER)>::val },

#define DECLARE_ENUM_TYPE_DESC(TYPE) struct TypeDescriptor_##TYPE : TypeDescriptor_Enum   \
{                                                    \
TypeDescriptor_##TYPE();                         \
};                                                   \
template <>                                          \
TypeDescriptor* get_primitive_descriptor<TYPE>()     \
{                                                    \
static TypeDescriptor_##TYPE typeDesc;           \
return &typeDesc;                                \
}

#define BEGIN_ENUM_TYPE_DESC(TYPE) TypeDescriptor_##TYPE::TypeDescriptor_##TYPE() : TypeDescriptor_Enum(#TYPE, sizeof(TYPE)) { \
static Constant constants[] = {                                                         \

#define REFLECT_ENUM_CONST(VALUE, DISPLAY_NAME, DESC) { DISPLAY_NAME, DESC, VALUE },
#define END_ENUM_TYPE_DESC()    };                                                    \
m_constants = &constants[0];                          \
m_num_constants = sizeof(constants)/sizeof(Constant); \
}
