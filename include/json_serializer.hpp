#pragma once

#include <serializer_macros.hpp>
#include <serializer.hpp>
#include <stack>

// Json Includes
#include <json.hpp>

class JsonSerializer : public ISerializer
{
public:
	JsonSerializer();
	~JsonSerializer();
	void serialize(const char* name, int8_t& value) override;
	void serialize(const char* name, uint8_t& value) override;
	void serialize(const char* name, int16_t& value) override;
	void serialize(const char* name, uint16_t& value) override;
	void serialize(const char* name, int32_t& value) override;
	void serialize(const char* name, uint32_t& value) override;
	void serialize(const char* name, float& value) override;
	void serialize(const char* name, double& value) override;
	void serialize(const char* name, int8_t* value, int count) override;
	void serialize(const char* name, uint8_t* value, int count) override;
	void serialize(const char* name, int16_t* value, int count) override;
	void serialize(const char* name, uint16_t* value, int count) override;
	void serialize(const char* name, int32_t* value, int count) override;
	void serialize(const char* name, uint32_t* value, int count) override;
	void serialize(const char* name, float* value, int count) override;
	void serialize(const char* name, double* value, int count) override;
	void serialize(const char* name, std::string& value) override;
	void serialize(const char* name, const char* value) override;
	void begin_serialize_complex(const char* name) override;
	void end_serialize_complex(const char* name) override;
	void begin_serialize_complex_array(const char* name, int count) override;
	void end_serialize_complex_array(const char* name) override;
	void print() override;

private:
	std::stack<nlohmann::json> m_object_stack;
};
