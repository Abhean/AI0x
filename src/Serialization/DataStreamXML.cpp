/*
 * DataStreamXML.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: kique
 */

#include "DataStreamXML.h"
#include "Foundation/Pointer.h"
#include "Foundation/Object.h"
#include "Foundation/Name.h"
#include "Logger/Logger.h"
#include <string>

namespace Serialization
{

///
CDataStreamXML::CDataStreamXML(std::istream& _istrmInput) :
  m_istrmInput(_istrmInput)
{
	// ...
}

///
CDataStreamXML::~CDataStreamXML()
{
	// TODO Auto-generated destructor stub
}

///
void CDataStreamXML::ReadVariablesFromXMLNode(rapidxml::xml_node<> const* _pXMLNode, Foundation::CType const& _oType, void* pData_)
{
  assert(_pXMLNode != nullptr);
  assert(pData_ != nullptr);
  
  Foundation::CClass const* pClass = Foundation::CType::DynamicCast<Foundation::CClass const>(&_oType); 
  if (pClass == nullptr)
  {
    Logger::Log(Logger::ELevel::INFO, "CDataStreamXML::ReadVariablesFromXMLNode: Type '%' is not a class.", _oType.GetName());
    return;
  }
  
  // Read attributes
  for (auto pAttr = _pXMLNode->first_attribute(); pAttr != nullptr; pAttr = pAttr->next_attribute())
  {
    Foundation::CVariable const* pVariable = pClass->GetVariable(Foundation::CName { pAttr->name() });
    if (pVariable)
    {
      pVariable->SetValue<std::string>(pData_, pAttr->value());
    }
  }
  
  // Read child nodes
  for (auto pVariableNode = _pXMLNode->first_node(); pVariableNode != nullptr; pVariableNode = pVariableNode->next_sibling())
  {
    auto pAttr = pVariableNode->first_attribute();
    Foundation::CName nAttrName { pAttr->name() };
    if (nAttrName == Foundation::CName("ID"))
    {
      Foundation::CVariable const* pVariable = pClass->GetVariable(Foundation::CName { pAttr->value() });
      if (pVariable)
      {
        Foundation::CType const* pValueType = nullptr;
        void* pValuePtr = nullptr;

        void* pVarData = pVariable->GetValuePtr(pData_);
        Foundation::CPointer const* pPointerType = Foundation::CType::DynamicCast<Foundation::CPointer const>(&pVariable->GetType());
        if (pPointerType)
        {
          if  (pPointerType->GetValue(pVarData, &pValuePtr))
          {
            if (!pValuePtr)
            {
              pValuePtr = pPointerType->GetPointedType().CreateInstance();
              if (!pPointerType->SetValue(pVarData, pValuePtr))
              {
                delete pValuePtr;
                pValuePtr = nullptr;
              }
            }
            
            pValueType = &pPointerType->GetPointedType();
          }
        }
        else
        {
          pValueType = &pVariable->GetType();
          pValuePtr = pVarData;
        }

        assert(pValueType != nullptr && pValuePtr);
        ReadVariablesFromXMLNode(pVariableNode, *pValueType, pValuePtr);
      }
      else
      {
        Logger::Log(Logger::ELevel::ERROR, "CDataStreamXML::ReadVariablesFromXMLNode: Variable '%' does not exist in type '%'", nAttrName, pClass->GetName());
      }
    }
    else
    {
      Logger::Log(Logger::ELevel::ERROR, "CDataStreamXML::ReadVariablesFromXMLNode: Malformed XML. Child node has not ID attribute.");
    }
  }
}


} // namespace Serialization

