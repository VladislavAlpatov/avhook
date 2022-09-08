#pragma once
#include "CBaseWindow.h"
#include <map>
#include <string>
#include <vector>
namespace UI 
{
    class CConsoleWindow final : public CBaseWindow
    {

public:
    CConsoleWindow(LPDIRECT3DDEVICE9 pDevice);
    void Render() override;
    std::string GetAlias() const override;
private:
    std::map<std::string, bool*> m_Convars;
    std::vector<std::pair<std::string, ImColor>> m_logHistory;

    bool CanBeConvertedToInt(const std::string& str);
    bool ConsoleExecute(const std::string& text);
    void AddConsoleLog(const std::string& text, const ImColor& col = ImColor(255, 255, 255));
    };
}

