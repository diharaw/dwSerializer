#include <iostream>
#include <json_serializer.hpp>
#include <binary_serializer.hpp>

class TestB
{
public:
	float a;
	std::string b;
	int c;

	void serialize(ISerializer* serializer)
	{
		serializer->serialize("a", a);
		serializer->serialize("b", b);
		serializer->serialize("c", c);
	}

	void deserialize(ISerializer* serializer)
	{
		serializer->deserialize("a", a);
		serializer->deserialize("b", b);
		serializer->deserialize("c", c);
	}
};

struct TestA
{
	float a;
	std::string b;
	int c;
	TestB d;
	TestB e[10];

	void serialize(ISerializer* serializer)
	{
		serializer->serialize("a", a);
		serializer->serialize("b", b);
		serializer->serialize("c", c);
		serializer->serialize_complex("d", d, false);
		serializer->serialize_complex_array("e", &e[0], 10, false);
	}

	void deserialize(ISerializer* serializer)
	{
		serializer->deserialize("a", a);
		serializer->deserialize("b", b);
		serializer->deserialize("c", c);
		serializer->deserialize_complex("d", d, false);
		serializer->deserialize_complex_array("e", &e[0], false);
	}
};

int main()
{
	JsonSerializer serializer;
	TestA obj;

	TestB obj_b;

	obj_b.a = 75.4f;
	obj_b.b = "Hello Complex Object";
	obj_b.c = 54;

	obj.a = 43.43f;
	obj.b = "Hello JSON";
	obj.c = 42;
	obj.d = obj_b;

	for (int i = 0; i < 10; i++)
	{
		obj.e[i].a = rand();
		std::string str = "This is a random string ";
		str += std::to_string(rand());
		obj.e[i].b = str;
		obj.e[i].c = rand();
	}

	obj.serialize(&serializer);

	serializer.print();

	TestA deserialize_test;

	deserialize_test.deserialize(&serializer);

	std::cin.get();
    return 0;
}
