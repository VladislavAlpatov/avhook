#pragma once
#include "CBaseWindow.h"
#include <map>
#include <string>
#include <vector>
namespace UI 
{
    class CConsoleWindow : public CBaseWindow
    {

public:
    CConsoleWindow(LPDIRECT3DDEVICE9 pDevice);
    void Render() override;
    std::string GetAlias() override;
private:
    std::map<std::string, bool*> m_Convars;
    std::vector<std::pair<std::string, ImColor>> m_logHistory;

    bool CanBeCovertedToInt(const std::string& str);
    };
}

