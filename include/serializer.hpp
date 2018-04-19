#pragma once

#include <stdint.h>
#include <string>

class ISerializer
{
public:
	ISerializer() {}
	virtual ~ISerializer() {}
	virtual void serialize(const char* name, int8_t& value)					 = 0;
	virtual void serialize(const char* name, uint8_t& value)				 = 0;
	virtual void serialize(const char* name, int16_t& value)				 = 0;
	virtual void serialize(const char* name, uint16_t& value)				 = 0;
	virtual void serialize(const char* name, int32_t& value)				 = 0;
	virtual void serialize(const char* name, uint32_t& value)				 = 0;
	virtual void serialize(const char* name, float& value)					 = 0;
	virtual void serialize(const char* name, double& value)					 = 0;
	virtual void serialize(const char* name, int8_t* value, int count)		 = 0;
	virtual void serialize(const char* name, uint8_t* value, int count)		 = 0;
	virtual void serialize(const char* name, int16_t* value, int count)		 = 0;
	virtual void serialize(const char* name, uint16_t* value, int count)	 = 0;
	virtual void serialize(const char* name, int32_t* value, int count)		 = 0;
	virtual void serialize(const char* name, uint32_t* value, int count)	 = 0;
	virtual void serialize(const char* name, float* value, int count)		 = 0;
	virtual void serialize(const char* name, double* value, int count)		 = 0;
	virtual void serialize(const char* name, std::string& value)			 = 0;
	virtual void serialize(const char* name, const char* value)				 = 0;
	virtual void begin_serialize_complex(const char* name)					 = 0;
	virtual void end_serialize_complex(const char* name)					 = 0;
	virtual void begin_serialize_complex_array(const char* name, int count)  = 0;
	virtual void end_serialize_complex_array(const char* name)				 = 0;
	virtual void print()													 = 0;
	virtual bool is_raw_serializable() = 0;
	virtual void raw_serialize(void* data, const size_t& size) = 0;

	template <typename T>
	void serialize_complex(const char* name, T& value, void (*serialize_func)(ISerializer*, T&), bool raw)
	{
		if (raw && is_raw_serializable())
			raw_serialize(&value, sizeof(T));
		else
		{
			begin_serialize_complex(name);
			(*serialize_func)(this, value);
			end_serialize_complex(name);
		}
	}

	template <typename T>
	void serialize_complex_array(const char* name, T* value, int count, void(*serialize_func)(ISerializer*, T&), bool raw)
	{
		if (raw && is_raw_serializable())
			raw_serialize(value, sizeof(T) * count);
		else
		{
			begin_serialize_complex_array(name, count)

			for (int i = 0; i < count; i++)
			{
				begin_serialize_complex(name);
				(*serialize_func)(this, value[i]);
				end_serialize_complex(name);
			}

			end_serialize_complex_array(name);
		}
	}

	virtual void deserialize(const char* name, int8_t& value) = 0;
	virtual void deserialize(const char* name, uint8_t& value) = 0;
	virtual void deserialize(const char* name, int16_t& value) = 0;
	virtual void deserialize(const char* name, uint16_t& value) = 0;
	virtual void deserialize(const char* name, int32_t& value) = 0;
	virtual void deserialize(const char* name, uint32_t& value) = 0;
	virtual void deserialize(const char* name, float& value) = 0;
	virtual void deserialize(const char* name, double& value) = 0;
	virtual void deserialize(const char* name, int8_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, uint8_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, int16_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, uint16_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, int32_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, uint32_t** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, float** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, double** value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, std::string& value, bool is_static = true) = 0;
	virtual void deserialize(const char* name, char** value, bool is_static = true) = 0;
	virtual void begin_deserialize_complex(const char* name, int index = -1) = 0;
	virtual void end_deserialize_complex(const char* name) = 0;
	virtual int  begin_deserialize_complex_array(const char* name) = 0;
	virtual void end_deserialize_complex_array(const char* name) = 0;

	template <typename T>
	void deserialize_complex(const char* name, T& value, void(*deserialize_func)(ISerializer*, T&))
	{
		begin_deserialize_complex(name);
		(*deserialize_func)(this, value);
		end_deserialize_complex(name);
	}

	template <typename T>
	void deserialize_complex_array(const char* name, T* value, void(*deserialize_func)(ISerializer*, T&))
	{
		int size = begin_deserialize_complex_array(name);

		for (int i = 0; i < size; i++)
		{
			begin_deserialize_complex(name, i);
			(*deserialize_func)(this, value[i]);
			end_deserialize_complex(name);
		}

		end_deserialize_complex_array(name);
	}

	template <typename T>
	void deserialize_complex_array(const char* name, T** value, void(*deserialize_func)(ISerializer*, T&))
	{
		int size = begin_deserialize_complex_array(name);
		*value = new T[size];

		for (int i = 0; i < size; i++)
		{
			begin_deserialize_complex(name, i);
			(*deserialize_func)(this, *value[i]);
			end_deserialize_complex(name);
		}

		end_deserialize_complex_array(name);
	}
};