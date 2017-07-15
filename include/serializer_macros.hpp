#pragma once

#define DW_SERIALIZE_SIMPLE(serializer, value) serializer.serialize_simple(#value, value)
#define DW_SERIALIZE_STRING(serializer, value) serializer.serialize_string(#value, value)
#define DW_SERIALIZE_CSTRING(serializer, value) serializer.serialize_string(#value, value)
#define DW_SERIALIZE_COMPLEX(serializer, value) serializer.serialize_complex(#value, value)
#define DW_SERIALIZE_SIMPLE_ARRAY(serializer, value, size) serializer.serialize_simple_array(#value, &value[0], size)
#define DW_SERIALIZE_COMPLEX_ARRAY(serializer, value, size) serializer.serialize_complex_array(#value, &value[0], size)

#define DW_DESERIALIZE_SIMPLE(serializer, value) serializer.deserialize_simple(#value, value)
#define DW_DESERIALIZE_STRING(serializer, value) serializer.deserialize_string(#value, value)
#define DW_DESERIALIZE_CSTRING(serializer, value) serializer.deserialize_string(#value, &value)
#define DW_DESERIALIZE_COMPLEX(serializer, value) serializer.deserialize_complex(#value, value)
#define DW_DESERIALIZE_SIMPLE_ARRAY(serializer, value, size) serializer.deserialize_simple_array(#value, &value[0], size)
#define DW_DESERIALIZE_COMPLEX_ARRAY(serializer, value, size) serializer.deserialize_complex_array(#value, &value[0], size)

#define DW_BEGIN_NAMESPACE namespace dw {
#define DW_END_NAMESPACE }



