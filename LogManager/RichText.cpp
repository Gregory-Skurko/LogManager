#include "stdafx.h"
#include "RichText.h"

RichText::RichText(CMFCRibbonRichEditCtrl &richEdit)    
    :m_richEdit(richEdit)
{    
}

RichText::~RichText(void)
{
}

void RichText::ReadFile(const std::string &fileName)
{
    Clear();
    std::ifstream is (fileName, std::ifstream::binary);
    
    if (is) 
    {
        is.seekg(0, is.end);
        int length = static_cast<int>(is.tellg());
        is.seekg(0, is.beg);

        char *buffer = new char[length + 1];
        is.read(buffer,length);                    
        is.close();
        buffer[length] = '\0';        
        m_richEdit.SetWindowTextA(buffer);
                        
        delete[] buffer;
    }
    else
    {
        AfxMessageBox("Error opening file!", MB_ICONSTOP);
    }
}

void RichText::AddHighlight(const std::string &request)
{    
    TextRequest textRequest(request);
    auto it = std::find(m_requests.begin(), m_requests.end(), request);  

    if (it == m_requests.end())
    {
        auto& ranges = findMatches(request);
  
        textRequest.SetRanges(ranges);
        m_requests.push_back(textRequest);
    }
    else
    {
        textRequest = *it;
    }

    highlight(textRequest);        
}

void RichText::RemoveHighlight(const std::string &request)
{
    auto& itTextRequest = std::find(m_requests.begin(), m_requests.end(), request);
    ASSERT(itTextRequest != m_requests.end());
    
    TextRequest textRequest(*itTextRequest);
    textRequest.SetColor(RGB(255, 255, 255));

    highlight(textRequest);
}

std::vector<CHARRANGE> RichText::findMatches(const std::string & request) const
{
    FINDTEXTEXA search;
    search.chrg = { 0, -1 };
    search.lpstrText = request.c_str();

    std::vector<CHARRANGE> ranges;

    while (-1 != m_richEdit.FindTextA(FR_DOWN, &search))
    {
        ranges.push_back(search.chrgText);
        search.chrg.cpMin = search.chrgText.cpMax;
    }

    return ranges;
}

void RichText::highlight(const TextRequest &request)
{
    CHARFORMAT2A cf = { };
    cf.cbSize = sizeof(cf);
    cf.dwEffects = 0;
    cf.dwMask = CFM_BACKCOLOR;
    cf.crBackColor = request.GetColor();
    cf.crTextColor = 0;
   
    m_richEdit.HideSelection(TRUE, FALSE);
    m_richEdit.SetRedraw(FALSE);    

    for (auto range: request.GetRanges())
    {
        m_richEdit.SetSel(range);
        m_richEdit.SetSelectionCharFormat(cf);        
    }

    m_richEdit.HideSelection(FALSE, FALSE);
    m_richEdit.SetRedraw(TRUE);
    m_richEdit.Invalidate();
}

void RichText::generateLimitedText(const TextRequest& request, int amountTop, int amountDown)
{
    auto ranges = request.GetRanges();
    if (0 == ranges.size())
    {
        return;
    }

    const int sizeBuffer = 1024;
    char buffer[sizeBuffer];
    std::string lineBreak(128, '-');
    std::string newText = "\n" + lineBreak + "\n\n";

    for (auto& range : ranges)
    {
        int numberOfLine = m_richEdit.LineFromChar(range.cpMin);

        for (int i = numberOfLine - amountTop; i <= numberOfLine + amountDown; ++i)
        {
            m_richEdit.GetLine(i, reinterpret_cast<LPTSTR>(buffer), sizeBuffer);
            newText += buffer;
        }
        newText += "\n\n" + lineBreak + "\n\n";
    }

    m_richEdit.SetWindowTextA(newText.c_str());
}

void RichText::DisplayRows(const std::string &request, int amountTop, int amountDown)
{    
    auto& itTextRequest = std::find(m_requests.begin(), m_requests.end(), request);    
    ASSERT(itTextRequest != m_requests.end());           
    
    generateLimitedText(*itTextRequest, amountTop, amountDown);           
    highlight(TextRequest(request, itTextRequest->GetColor(), findMatches(request)));    
}

void RichText::SaveState()
{
    m_richStream.Save(m_richEdit);
}

void RichText::LoadState()
{   
    m_richStream.Load(m_richEdit); 
}

void RichText::Clear()
{
    m_richStream.Clear();
    m_requests.clear();
}
