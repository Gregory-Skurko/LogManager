#pragma once

#include <array>
#include <vector>

class TextRequest
{
    std::string m_request;    
    std::vector<CHARRANGE> m_rangesMathes;        
    COLORREF m_color;

    static const std::vector<COLORREF> colors;
    static int idColor;
    
public:
    TextRequest(std::string request, COLORREF color = RGB(0,0,0), const std::vector<CHARRANGE> &rangesMathes = std::vector<CHARRANGE>());
    ~TextRequest(void);

    const std::string & GetRequest() const;    

    COLORREF GetColor() const;
    void SetColor(COLORREF color);

    void AddRange(const CHARRANGE &range);
    const std::vector<CHARRANGE> & GetRanges() const;
    void SetRanges(const std::vector<CHARRANGE> &ranges);

    bool operator==(const TextRequest &textRequest) const;    

};

