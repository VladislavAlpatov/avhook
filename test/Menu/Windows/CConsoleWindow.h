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
    void Render() override;
    CConsoleWindow(LPDIRECT3DDEVICE9 pDevice);
    std::string GetAlias() override;
    private:
        std::map<std::string, int*> m_Convars;
        std::vector<std::pair<std::string, ImColor>> m_logHistory;

        bool CanBeCovertedToInt(const std::string& str);
    };
}

