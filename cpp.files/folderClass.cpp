#include "folderClass.h"

folderClass::folderClass()
    :m_app(nullptr), 
     m_editor(nullptr),
     m_surfaces(nullptr)
{}

folderClass::~folderClass()
{
    delete m_app;
    delete m_editor;
    delete m_surfaces;
}


