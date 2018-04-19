#pragma once

#include <serializer_macros.hpp>
#include <serializer.hpp>

class BinarySerializer : public ISerializer
{
public:
	BinarySerializer();
	~BinarySerializer();

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
	bool is_raw_serializable() override;
	void raw_serialize(void* data, const size_t& size) override;

	void deserialize(const char* name, int8_t& value) override;
	void deserialize(const char* name, uint8_t& value) override;
	void deserialize(const char* name, int16_t& value) override;
	void deserialize(const char* name, uint16_t& value) override;
	void deserialize(const char* name, int32_t& value) override;
	void deserialize(const char* name, uint32_t& value) override;
	void deserialize(const char* name, float& value) override;
	void deserialize(const char* name, double& value) override;
	void deserialize(const char* name, int8_t** value, bool is_static = true) override;
	void deserialize(const char* name, uint8_t** value, bool is_static = true) override;
	void deserialize(const char* name, int16_t** value, bool is_static = true) override;
	void deserialize(const char* name, uint16_t** value, bool is_static = true) override;
	void deserialize(const char* name, int32_t** value, bool is_static = true) override;
	void deserialize(const char* name, uint32_t** value, bool is_static = true) override;
	void deserialize(const char* name, float** value, bool is_static = true) override;
	void deserialize(const char* name, double** value, bool is_static = true) override;
	void deserialize(const char* name, std::string& value, bool is_static = true) override;
	void deserialize(const char* name, char** value, bool is_static = true) override;
	void begin_deserialize_complex(const char* name, int index = -1) override;
	void end_deserialize_complex(const char* name) override;
	int  begin_deserialize_complex_array(const char* name) override;
	void end_deserialize_complex_array(const char* name) override;

private:
	char* m_buffer;
	size_t m_buffer_size;
};