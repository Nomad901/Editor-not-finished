#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "FactoryOfRect.h"
#include "App.h"
#include "ActionsOfRect.h"
#include "Menu.h"
#include "FactoryOfFront.h"
#include "SurfacesA.h"
#include "Editor.h"

class folderClass {
public:
    folderClass();
    ~folderClass();


    App& getApp() { return *m_app; }
    SurfacesA& getSurfacesA() { return *m_surfaces; }
    Editor& getEditor() { return *m_editor; }
    FactoryOfFront& getFactoryOfFront() { return *m_FactoryOfFront; }
    FactoryOfRect& getFactoryOfRect1() { return *m_FactoryOfRect1; }
    FactoryOfRect& getFactoryOfRect2() { return *m_FactoryOfRect2; }

    void setApp(App& app) { m_app = &app; }
    void setSurfacesA(SurfacesA& m_surfaces) { this->m_surfaces = &m_surfaces; }
    void setEditor(Editor& m_editor) { this->m_editor = &m_editor; }
    void setFactoryOfFront(FactoryOfFront& m_FactoryOfFront) { this->m_FactoryOfFront = &m_FactoryOfFront; }
    void setFactoryOfRect1(FactoryOfRect& m_FactoryOfRect1) { this->m_FactoryOfRect1 = &m_FactoryOfRect1; }
    void setFactoryOfRect2(FactoryOfRect& m_FactoryOfRect2) { this->m_FactoryOfRect2 = &m_FactoryOfRect2; }

private:
    App* m_app;
    SurfacesA* m_surfaces;
    Editor* m_editor;
    FactoryOfFront* m_FactoryOfFront;
    FactoryOfRect* m_FactoryOfRect1;
    FactoryOfRect* m_FactoryOfRect2;
};

