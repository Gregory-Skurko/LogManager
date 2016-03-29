#pragma once
#include <sstream>

class RichStream
{
    CMemFile m_memFile;

public:
    RichStream(void);
    ~RichStream(void);
    void Load(CMFCRibbonRichEditCtrl &richEdit);
    void Save(CMFCRibbonRichEditCtrl &richEdit);
    void Clear();
private:
    static DWORD CALLBACK editStreamOutCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
    static DWORD CALLBACK editStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
};

