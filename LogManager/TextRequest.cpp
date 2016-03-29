#include "stdafx.h"
#include "TextRequest.h"

const std::vector<COLORREF> TextRequest::colors = {
                                                        RGB(255, 228, 181), RGB(190, 90, 190), 
                                                        RGB(119, 136, 153), RGB(100, 149, 237), 
                                                        RGB(102, 205, 170), RGB(0, 255, 127), 
                                                        RGB(189, 183, 107), RGB(255, 255, 0), 
                                                        RGB(188, 143, 143), RGB(255, 165, 0)
                                                     };
int TextRequest::idColor = 0;

TextRequest::TextRequest(std::string request, COLORREF color, const std::vector<CHARRANGE> &rangesMathes)
    : m_request(request), m_rangesMathes(rangesMathes)
{
    if (color == RGB(0, 0, 0))
    {
        ++TextRequest::idColor;
        TextRequest::idColor %= colors.size(); 

        m_color = TextRequest::colors[idColor];
    }
    else
    {
        m_color = color;
    }
}

TextRequest::~TextRequest(void)
{    
    (TextRequest::idColor == 0) ? TextRequest::idColor = (colors.size() - 1) : --TextRequest::idColor;
}

const std::string & TextRequest::GetRequest() const
{
    return m_request;
}

void TextRequest::AddRange(const CHARRANGE &range)
{
    m_rangesMathes.push_back(range);
}

COLORREF TextRequest::GetColor() const
{
    return m_color;
}

void TextRequest::SetColor(COLORREF color)
{
    m_color = color;
}

const std::vector<CHARRANGE> & TextRequest::GetRanges() const
{
    return m_rangesMathes;
}

void TextRequest::SetRanges(const std::vector<CHARRANGE>& ranges)
{
    m_rangesMathes = ranges;
}

bool TextRequest::operator==(const TextRequest &textRequest) const
{
    return m_request == textRequest.m_request;
}



