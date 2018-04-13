#include <iostream>
#include <json_serializer.hpp>

class TestB
{
public:
	float a;
	std::string b;
	int c;

	static void serialize_test_b(ISerializer* serializer, TestB& obj)
	{
		serializer->serialize("a", obj.a);
		serializer->serialize("b", obj.b);
		serializer->serialize("c", obj.c);
	}

	static void deserialize_test_b(ISerializer* serializer, TestB& obj)
	{
		serializer->deserialize("a", obj.a);
		serializer->deserialize("b", obj.b);
		serializer->deserialize("c", obj.c);
	}
};

struct TestA
{
	float a;
	std::string b;
	int c;
	TestB d;
	TestB e[10];
};

void serialize(ISerializer* serializer, TestA& obj)
{
	serializer->serialize("a", obj.a);
	serializer->serialize("b", obj.b);
	serializer->serialize("c", obj.c);
	serializer->serialize_complex("d", obj.d, &TestB::serialize_test_b);
	serializer->serialize_complex_array("e", &obj.e[0], 10, &TestB::serialize_test_b);
}

void deserialize(ISerializer* serializer, TestA& obj)
{
	serializer->deserialize("a", obj.a);
	serializer->deserialize("b", obj.b);
	serializer->deserialize("c", obj.c);
	serializer->deserialize_complex("d", obj.d, &TestB::deserialize_test_b);
	serializer->deserialize_complex_array("e", &obj.e[0], &TestB::deserialize_test_b);
}

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

	serialize(&serializer, obj);

	serializer.print();

	TestA deserialize_test;

	deserialize(&serializer, deserialize_test);

	std::cin.get();
    return 0;
}
