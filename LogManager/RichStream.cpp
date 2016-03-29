#include "stdafx.h"
#include "RichStream.h"
#include <fstream>

RichStream::RichStream(void)
    : m_memFile( 83886008/*8mb in bytes*/ )
{
}


RichStream::~RichStream(void)
{
}

void RichStream::Save(CMFCRibbonRichEditCtrl &richEdit)
{    
    m_memFile.SeekToBegin();
    
    EDITSTREAM es = { 0, 0, editStreamOutCallback };    
    es.dwCookie = reinterpret_cast<DWORD_PTR>(&m_memFile);
    
    richEdit.StreamOut(SF_RTF, es);      
}

void RichStream::Load(CMFCRibbonRichEditCtrl &richEdit)
{   
    m_memFile.SeekToBegin();
    
    EDITSTREAM es = { 0, 0, editStreamInCallback };
    es.dwCookie = reinterpret_cast<DWORD_PTR>(&m_memFile);    
    
    richEdit.StreamIn(SF_RTF, es);
}

DWORD CALLBACK RichStream::editStreamOutCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    CMemFile *pFile = reinterpret_cast<CMemFile *>(dwCookie);

    pFile->Write(pbBuff, cb);

    *pcb = cb;
    
    return 0;   
}

DWORD CALLBACK RichStream::editStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    CMemFile *pFile = reinterpret_cast<CMemFile *>(dwCookie);

    *pcb = pFile->Read(pbBuff, cb);

    return 0;
}

void RichStream::Clear()
{
    m_memFile.SetLength(0);
}