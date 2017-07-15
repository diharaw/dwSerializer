#include <iostream>

#include <serializer.hpp>

#define NUM_INNER_ARRAY 10

struct MyInnerData
{
    float  x;
    int    y;
    double z;
    
    template<typename SerializerType>
    void serialize(SerializerType& serializer)
    {
        DW_SERIALIZE_SIMPLE(serializer, x);
        DW_SERIALIZE_SIMPLE(serializer, y);
        DW_SERIALIZE_SIMPLE(serializer, z);
    }
    
    template<typename SerializerType>
    void deserialize(SerializerType& serializer)
    {
        DW_DESERIALIZE_SIMPLE(serializer, x);
        DW_DESERIALIZE_SIMPLE(serializer, y);
        DW_DESERIALIZE_SIMPLE(serializer, z);
    }
};

struct MyData
{
    float a;
    int b;
    double c;
    const char* str;
    std::string str2;
    MyInnerData dt;
    MyInnerData what_the_fuck[NUM_INNER_ARRAY];
    float simple_array[10];
    
    template<typename SerializerType>
    void serialize(SerializerType& serializer)
    {
        DW_SERIALIZE_SIMPLE(serializer, a);
        DW_SERIALIZE_SIMPLE(serializer, b);
        DW_SERIALIZE_SIMPLE(serializer, c);
        DW_SERIALIZE_CSTRING(serializer, str);
        DW_SERIALIZE_STRING(serializer, str2);
        DW_SERIALIZE_COMPLEX(serializer, dt);
        DW_SERIALIZE_SIMPLE_ARRAY(serializer, simple_array, 10);
        DW_SERIALIZE_COMPLEX_ARRAY(serializer, what_the_fuck, NUM_INNER_ARRAY);
    }
    
    template<typename SerializerType>
    void deserialize(SerializerType& serializer)
    {
        DW_DESERIALIZE_SIMPLE(serializer, a);
        DW_DESERIALIZE_SIMPLE(serializer, b);
        DW_DESERIALIZE_SIMPLE(serializer, c);
        DW_DESERIALIZE_CSTRING(serializer, str);
        DW_DESERIALIZE_STRING(serializer, str2);
        DW_DESERIALIZE_COMPLEX(serializer, dt);
        DW_DESERIALIZE_SIMPLE_ARRAY(serializer, simple_array, 10);
        DW_DESERIALIZE_COMPLEX_ARRAY(serializer, what_the_fuck, NUM_INNER_ARRAY);
    }
};

struct BinTest
{
    float a;
    int b;
    float d[10];
    
    template<typename SerializerType>
    void serialize(SerializerType& serializer)
    {
        serializer.serialize_simple("a", a, offsetof(BinTest, a));
        serializer.serialize_simple("b", b, offsetof(BinTest, b));
        serializer.serialize_simple_array("d", &d[0], 10, offsetof(BinTest, d));
    }
    
    template<typename SerializerType>
    void deserialize(SerializerType& serializer)
    {
        serializer.deserialize_simple("a", a, offsetof(BinTest, a));
        serializer.deserialize_simple("b", b, offsetof(BinTest, b));
        serializer.deserialize_simple_array("d", &d[0], 10, offsetof(BinTest, d));
    }
};

void test_binary()
{
    dw::BinarySerializer serializer;
    
    void* buf = malloc(sizeof(BinTest));
    serializer.set_buffer((char*)buf, sizeof(BinTest));
    
    BinTest obj1;
    BinTest obj2;
    
    obj1.a = 323.1f;
    obj1.b = 4;
    
    obj1.d[0] = 235.224f;
    obj1.d[1] = 625.334f;
    obj1.d[2] = 135.924f;
    obj1.d[3] = 45.44f;
    obj1.d[4] = 3135.524f;
    obj1.d[5] = 2665.824f;
    obj1.d[6] = 1225.124f;
    obj1.d[7] = 264.524f;
    obj1.d[8] = 85.224f;
    obj1.d[9] = 12835.34f;
    
    obj1.serialize(serializer);
    
    obj2.deserialize(serializer);
    
    std::cout << obj2.a << std::endl;
    std::cout << obj2.b << std::endl;
    
    for(int i = 0; i < 10; i++)
        std::cout << obj2.d[i] << std::endl;
    
    free(buf);
}

int main()
{
    MyData data;
    data.str = "Hello";
    data.str = "lol";
    data.str2 = "LMFAO";
    data.a = 0.5f;
    data.b = 3;
    data.c = 0.0032;
    
    data.dt.x = rand();
    data.dt.y = rand();
    data.dt.z = rand();
    
    for(int i = 0; i < NUM_INNER_ARRAY; i++)
    {
        data.what_the_fuck[i].x = rand();
        data.what_the_fuck[i].y = rand();
        data.what_the_fuck[i].z = rand();
    }
    
    for(int i = 0; i < 10; i++)
    {
        data.simple_array[i] = rand();
    }
    
    dw::JsonSerializer test;
    dw::XmlSerializer xml_test;
    
    data.serialize(test);
    data.serialize(xml_test);
    
    std::cout << test.print() << std::endl;
    std::cout << xml_test.print() << std::endl;
    
    MyData test_data;
    test_data.deserialize(xml_test);
    
    std::cout << test_data.str << std::endl;
    
    test_binary();
    
    return 0;
}
