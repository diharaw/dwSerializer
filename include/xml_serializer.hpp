#pragma once

#include <serializer_macros.hpp>

// Xml Includes
#include <tinyxml2.h>

DW_BEGIN_NAMESPACE

class XmlSerializer
{
private:
    // TinyXML version
    tinyxml2::XMLDocument  xml_doc;
    tinyxml2::XMLDocument* xml_doc_ref;
    tinyxml2::XMLPrinter   xml_printer;
    tinyxml2::XMLNode*     xml_root;
    
public:
    XmlSerializer(tinyxml2::XMLNode* root = nullptr, tinyxml2::XMLDocument* doc = nullptr)
    {
        if(root)
        {
            xml_root = root;
            xml_doc_ref = doc;
        }
        else
        {
            xml_root = xml_doc.NewElement("root");
            xml_doc.InsertEndChild(xml_root);
            xml_doc_ref = &xml_doc;
        }
    }
    
    void serialize_string(const char* name, std::string value)
    {
        tinyxml2::XMLElement* element = xml_doc_ref->NewElement(name);
        element->SetText(value.c_str());
        xml_root->InsertEndChild(element);
    }
    
    template<typename T>
    void serialize_simple(const char* name, T& value)
    {
        tinyxml2::XMLElement* element = xml_doc_ref->NewElement(name);
        element->SetText(value);
        xml_root->InsertEndChild(element);
    }
    
    template<typename T>
    void serialize_complex(const char* name, T& value)
    {
        tinyxml2::XMLElement* element = xml_doc_ref->NewElement(name);
        XmlSerializer serializer(element, xml_doc_ref);
        value.serialize(serializer);
        xml_root->InsertEndChild(element);
    }
    
    template<typename T>
    void serialize_simple_array(const char* name, T* value, size_t size)
    {
        tinyxml2::XMLElement* element = xml_doc_ref->NewElement(name);
        
        for(uint32_t i = 0; i < size; i++)
        {
            tinyxml2::XMLElement* array_element = xml_doc_ref->NewElement("element");
            array_element->SetText(value[i]);
            element->InsertEndChild(array_element);
        }
        
        xml_root->InsertEndChild(element);
    }
    
    template<typename T>
    void serialize_complex_array(const char* name, T* value, size_t size)
    {
        tinyxml2::XMLElement* element = xml_doc_ref->NewElement(name);
        
        for(uint32_t i = 0; i < size; i++)
        {
            tinyxml2::XMLElement* array_element = xml_doc_ref->NewElement("element");
            
            XmlSerializer serializer(array_element, xml_doc_ref);
            value[i].serialize(serializer);
            
            element->InsertEndChild(array_element);
        }
        
        xml_root->InsertEndChild(element);
    }
    
    void deserialize_string(const char* name, char** value)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
        {
            std::string str = element->GetText();
            *value = (char*)malloc(str.size() + 1);
            strcpy(*value, str.c_str());
        }
    }
    
    void deserialize_string(const char* name, const char** value)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
        {
            std::string str = element->GetText();
            *value = (const char*)malloc(str.size() + 1);
            strcpy((char*)*value, str.c_str());
        }
    }
    
    void deserialize_string(const char* name, std::string& value)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
            value = element->GetText();
    }
    
    template<typename T>
    void deserialize_simple(const char* name, T& value)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
            from_string(element->GetText(), value);
    }
    
    template<typename T>
    void deserialize_complex(const char* name, T& value)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
        {
            XmlSerializer serializer(element, xml_doc_ref);
            value.deserialize(serializer);
        }
    }
    
    template<typename T>
    void deserialize_simple_array(const char* name, T* value, size_t size)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
        {
            uint32_t i = 0;
            for(tinyxml2::XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
            {
                from_string(child->GetText(), value[i]);
                i++;
            }
        }
    }
    
    template<typename T>
    void deserialize_complex_array(const char* name, T* value, size_t size)
    {
        tinyxml2::XMLElement* element = xml_root->FirstChildElement(name);
        
        if(element)
        {
            uint32_t i = 0;
            for(tinyxml2::XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
            {
                XmlSerializer serializer(child, xml_doc_ref);
                value[i].deserialize(serializer);
                i++;
            }
        }
    }
    
    const char* print()
    {
        xml_doc_ref->Print(&xml_printer);
        return xml_printer.CStr();
    }
    
    template<typename T>
    std::string to_str(T value)
    {
        return std::to_string(value);
    }

    inline void from_string(const char* str, int& value)
    {
        value = atoi(str);
    }
    
    inline void from_string(const char* str, float& value)
    {
        value = strtof(str, NULL);
    }
    
    inline void from_string(const char* str, double& value)
    {
        value = atof(str);
    }
};

DW_END_NAMESPACE
