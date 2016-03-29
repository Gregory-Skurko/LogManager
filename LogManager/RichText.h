#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "TextRequest.h"
#include "RichStream.h"

class RichText
{
    CMFCRibbonRichEditCtrl &m_richEdit;
    RichStream m_richStream;

    std::vector<TextRequest> m_requests;    
public:
    RichText(CMFCRibbonRichEditCtrl &richEdit);
    ~RichText(void);

    void ReadFile(const std::string &fileName);
    void AddHighlight(const std::string &searchText);
    void RemoveHighlight(const std::string &searchText);
    void DisplayRows(const std::string &request, int amountTop, int amountDown);

    void SaveState();
    void LoadState();
   
    void Clear();

private:
    std::vector<CHARRANGE> findMatches(const std::string &request) const;
    void highlight(const TextRequest &textRequest);
    void generateLimitedText(const TextRequest &textRequest, int amountTop, int amountDown);
};













