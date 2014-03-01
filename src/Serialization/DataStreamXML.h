/*
 * DataStreamXML.h
 *
 *  Created on: Nov 9, 2012
 *      Author: kique
 */

#ifndef SERIALIZATION_DATASTREAMXML_H_
#define SERIALIZATION_DATASTREAMXML_H_

#include "DataStream.h"
#include "Foundation/Class.h"
#include "Foundation/TypeRegistry.h"
#include <rapidxml.hpp>

// Forward Declarations
namespace Foundation
{
	class CObject;
}

// CDataStreamXML
namespace Serialization
{

typedef rapidxml::xml_node<char> xml_node_char; 

class CDataStreamXML : public IDataStream
{
public:
           CDataStreamXML(std::istream& _istrmInput);
	virtual ~CDataStreamXML();

  template <typename TValue>
  std::unique_ptr<TValue> Read();
  
private:

  template <typename TValue>
  std::unique_ptr<TValue> ReadFromXMLNode(rapidxml::xml_node<> const* _pXMLNode);
  
  void ReadVariablesFromXMLNode(rapidxml::xml_node<> const* _pXMLNode, Foundation::CType const& oType, void* pData_);
  
  std::istream& m_istrmInput;
};

///
template <typename TValue>
std::unique_ptr<TValue> CDataStreamXML::Read()
{
  std::unique_ptr<TValue> pNewObject { nullptr };
  
  std::vector<char> vectcXML { (std::istreambuf_iterator<char>(m_istrmInput)), std::istreambuf_iterator<char>() };
  vectcXML.push_back('\0');
  rapidxml::xml_document<> doc;
  doc.parse<0>(vectcXML.data());
  
  rapidxml::xml_node<>* pNode = doc.first_node();
  if (pNode) 
  {
    pNewObject = ReadFromXMLNode<TValue>(pNode);
  } 
  
  return pNewObject;
}

///
template <typename TValue>
std::unique_ptr<TValue> CDataStreamXML::ReadFromXMLNode(rapidxml::xml_node<> const* _pXMLNode)
{
  std::unique_ptr<TValue> pData { nullptr };
  
  std::string sTypeName = _pXMLNode->name();
  Foundation::CType const* pType = Foundation::CTypeRegistry::GetInstance()->GetTypeByName(Foundation::CName(sTypeName));
  if (pType)
  {
    if (pType->IsKindOf(Foundation::StaticType<TValue>::Value()))
    {
      // @TODO[egarcia]: Safe Cast (any?)
      pData.reset(static_cast<TValue*>(pType->CreateInstance()));
      if (pData)
      {
        ReadVariablesFromXMLNode(_pXMLNode, *pType, pData.get());
      }
    }
    else
    {
      Logger::Log(Logger::ELevel::ERROR, "CDataStreamXML::ReadFromXMLNode: Found data type [%] when [%] was expected.", sTypeName, Foundation::StaticType<TValue>::Value().GetName());
    }
  }
  else
  {
    Logger::Log(Logger::ELevel::ERROR, "CDataStreamXML::ReadFromXMLNode: Type [%] not found. Skipping object.", sTypeName);
  }
  

  return pData;
}

} // namespace Serialization 


#endif /* SERIALIZATION_DATASTREAMXML_H_ */
