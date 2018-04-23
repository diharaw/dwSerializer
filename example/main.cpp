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

enum ShadowMapping
{
	PCF = 0,
	PCSS = 1,
	PSSM = 2
};

DECLARE_ENUM_TYPE_DESC(ShadowMapping)

struct Bar
{
	int msaa;
	ShadowMapping shadows;

	REFLECT()
};

struct Foo
{
	bool hdr;
	int level;
	float bloom_intensity;
	Bar bar;

	REFLECT()
};

BEGIN_ENUM_TYPE_DESC(ShadowMapping)
	REFLECT_ENUM_CONST(PCF, "Percentage Closer Filtering", "PCF")
	REFLECT_ENUM_CONST(PCSS, "Percentage Closer Soft Shadows", "PCSS")
	REFLECT_ENUM_CONST(PSSM, "Parallel Split Shadow Maps", "PSSM")
END_ENUM_TYPE_DESC()

BEGIN_DECLARE_REFLECT(Bar)
	REFLECT_MEMBER(msaa)
	REFLECT_MEMBER(shadows)
END_DECLARE_REFLECT()

BEGIN_DECLARE_REFLECT(Foo)
	REFLECT_MEMBER(hdr)
	REFLECT_MEMBER(level)
	REFLECT_MEMBER(bloom_intensity)
	REFLECT_MEMBER(bar)
END_DECLARE_REFLECT()

int main()
{
	JsonSerializer serializer;
	Foo test;

	test.bloom_intensity = 3.4f;
	test.hdr = true;
	test.level = 5;
	test.bar.msaa = 4;
	test.bar.shadows = PCSS;

	serializer.save(test);

	serializer.print();

	Foo test2;

	serializer.load(test2);

	std::cout << test2.bloom_intensity << std::endl;

	std::cin.get();
    return 0;
}
