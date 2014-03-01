#include "NPuzzle/Model/World.h"
#include "NPuzzle/Model/State.h"
#include "AI/Model/Action.h"
#include "Logic/Component.h"
#include "Logic/ComponentDef.h"
#include "Foundation/TypeRegistry.h"
#include "Foundation/Type.h"
#include "Foundation/NameManager.h"
#include "Foundation/PoolManager.h"
#include "Foundation/Pool.h"
#include "Foundation/CRC32.h"
#include "Render/Service.h"
#include "Logger/Logger.h"
#include "Serialization/DataStreamXML.h"
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <GL/glfw.h>


int main(int _iNumArgs, char** _apszArgs)
{
    using Foundation::operator "" _n;
/*
    // create and open a character archive for output
    std::ofstream ofs("NPuzzle.xml");

    // create class instance
    NPuzzle::Model::CWorld World { NPuzzle::Model::V2i(3, 3) };
    //NPuzzle::Model::CState State { &World };

    // save data to archive
    {
        boost::archive::xml_oarchive oa(ofs);
        // write class instance to archive
        oa << boost::serialization::make_nvp("World", World);
        //oa << boost::serialization::make_nvp("InitState", State);
    	// archive and stream closed when destructors are called
    }
*/

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    Foundation::CNameManager::Init();

    Foundation::CTypeRegistry::Init();
    Foundation::CPoolManager::Init();
    Render::CService::Init();

    Foundation::CPoolManager::GetInstance()->CreatePool<Logic::CComponent>(10);
    Foundation::IObjectPool::THandle hPoolInstance = Foundation::CPoolManager::GetInstance()->CreateInstance<Logic::CComponent>();
    assert(hPoolInstance != Foundation::IObjectPool::INVALID_HANDLE);

    //
    Foundation::CType const* pType = Foundation::CTypeRegistry::GetInstance()->GetTypeByName("Logic::CComponentDef"_n);
    Logic::CComponentDef* pInstance = pType->CreateInstance<Logic::CComponentDef>();
    
    Logger::Log(Logger::ELevel::ERROR, "Type %", pType->GetName());

    const char* pszFilePath = "Objects.xml";
    std::ifstream istrmText(pszFilePath);
    if (istrmText.is_open())
    {
        Serialization::CDataStreamXML oDataStreamXML(istrmText);
        std::unique_ptr<Foundation::CObject> ptrObject = oDataStreamXML.Read<Foundation::CObject>();
        istrmText.close();
    }
    else
    {
      Logger::Log(Logger::ELevel::ERROR, "File Not Found [%]", pszFilePath);
    }


    int iTest = 0;
    
    pInstance->SetValue("m_iTest"_n, 3.1f);
    pInstance->GetValue("m_iTest"_n, &iTest);

    pInstance->SetValue("m_Name"_n, "NameTest"_n);
    
    Foundation::CName ComponentName;
    pInstance->GetValue("m_Name"_n, &ComponentName);

    Foundation::CName const* pComponentNamePtr { nullptr };
    pInstance->GetValuePtr("m_Name"_n, &pComponentNamePtr);

    Foundation::CName* pComponentNameRWPtr { nullptr };
    pInstance->GetValuePtr("m_Name"_n, &pComponentNameRWPtr);

    Logger::Log(Logger::ELevel::INFO, "Instance [%]", pInstance->GetName());
    Logger::Log(Logger::ELevel::INFO, "Instance [%]", ComponentName);
    Logger::Log(Logger::ELevel::INFO, "Instance [%]", *pComponentNamePtr);
    Logger::Log(Logger::ELevel::INFO, "Instance [%]", *pComponentNameRWPtr);

    //std::iofstream strmLevel("");
    //Serialization::IArchive xmlData = new Serialization::ArchiveXML(strmLevel);
    //Foundation::CObject* pEntity = xmlData.Read();

    // Init Render Service
    Render::CService::GetInstance()->OpenWindow();

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    float fX = 1.0f;
    float fY = 0.0f;

    do
    {
      Render::CService::GetInstance()->BeginScene();
      Render::CService::GetInstance()->DrawLine(V3f(0.0f, 0.0f, 0.0f), V3f(fX, fY, 0.0f));
      fY += 0.01f;
      Render::CService::GetInstance()->EndScene();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS && glfwGetWindowParam( GLFW_OPENED ) );

    // Free Resources
    delete pInstance;

    Render::CService::Done();
    Foundation::CPoolManager::Done();
    Foundation::CTypeRegistry::Done();

    Foundation::CNameManager::Done();

    return 0;
}
