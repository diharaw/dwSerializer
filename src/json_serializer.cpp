#include <json_serializer.hpp>
#include <iostream>

JsonSerializer::JsonSerializer()
{
	m_object_stack.push(nlohmann::json());
}

JsonSerializer::~JsonSerializer()
{

}

void JsonSerializer::serialize(const char* name, bool& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, int8_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, uint8_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, int16_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, uint16_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, int32_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, uint32_t& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, float& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, double& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, int8_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();
	
	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, uint8_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, int16_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, uint16_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, int32_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, uint32_t* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, float* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, double* value, int count)
{
	nlohmann::json array = nlohmann::json::array();

	for (int i = 0; i < count; i++)
		array.push_back(value[i]);

	nlohmann::json array_container;
	array_container["size"] = count;
	array_container["data"] = array;
	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::serialize(const char* name, std::string& value)
{
	m_object_stack.top()[name] = value;
}

void JsonSerializer::serialize(const char* name, const char* value)
{
	m_object_stack.top()[name] = value;
}

bool JsonSerializer::is_raw_serializable()
{
	return false;
}

void JsonSerializer::raw_serialize(void* data, const size_t& size)
{
	// NOT ALLOWED.
	assert(false);
}

void JsonSerializer::begin_serialize_complex(const char* name)
{
	m_object_stack.push(nlohmann::json());
}

void JsonSerializer::end_serialize_complex(const char* name)
{
	nlohmann::json top = m_object_stack.top();
	m_object_stack.pop();

	if (m_object_stack.top().is_array())
		m_object_stack.top().push_back(top);
	else
		m_object_stack.top()[name] = top;
}

void JsonSerializer::begin_serialize_complex_array(const char* name, int count)
{
	nlohmann::json array_container;
	array_container["size"] = count;
	m_object_stack.push(array_container);
	m_object_stack.push(nlohmann::json::array());
}

void JsonSerializer::end_serialize_complex_array(const char* name)
{
	nlohmann::json array = m_object_stack.top();
	m_object_stack.pop();
	nlohmann::json array_container = m_object_stack.top();
	m_object_stack.pop();

	array_container["data"] = array;

	m_object_stack.top()[name] = array_container;
}

void JsonSerializer::print()
{
	std::cout << m_object_stack.top().dump(4) << std::endl;
}

void JsonSerializer::deserialize(const char* name, bool& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, int8_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, uint8_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, int16_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, uint16_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, int32_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, uint32_t& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, float& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, double& value)
{
	value = m_object_stack.top()[name];
}

void JsonSerializer::deserialize(const char* name, int8_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new int8_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, uint8_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new uint8_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, int16_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new int16_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, uint16_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new uint16_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, int32_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new int32_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, uint32_t** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new uint32_t[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, float** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new float[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::JsonSerializer::deserialize(const char* name, double** value, bool is_static)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];

	if (!is_static)
		*value = new double[size];

	for (int i = 0; i < size; i++)
		*value[i] = data[i];
}

void JsonSerializer::deserialize(const char* name, std::string& value, bool is_static)
{
	std::string str = m_object_stack.top()[name];
	value = str;
}

void JsonSerializer::deserialize(const char* name, char** value, bool is_static)
{
	std::string str = m_object_stack.top()[name];

	if (!is_static)
		*value = new char[str.length()];
	
	strcpy(*value, str.c_str());
}

void JsonSerializer::begin_deserialize_complex(const char* name, int index)
{
	if (m_object_stack.top().is_array())
	{
		nlohmann::json obj = m_object_stack.top()[index];
		m_object_stack.push(obj);
	}
	else
	{
		nlohmann::json obj = m_object_stack.top()[name];
		m_object_stack.push(obj);
	}
}

void JsonSerializer::end_deserialize_complex(const char* name)
{
	m_object_stack.pop();
}

int JsonSerializer::begin_deserialize_complex_array(const char* name)
{
	nlohmann::json array_container = m_object_stack.top()[name];
	nlohmann::json data = array_container["data"];
	int size = array_container["size"];
	m_object_stack.push(data);
	return size;
}

void JsonSerializer::end_deserialize_complex_array(const char* name)
{
	m_object_stack.pop();
}

void JsonSerializer::raw_deserialize(void* data, const size_t& size)
{

}