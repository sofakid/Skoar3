#include "skoar_public.hpp"
#include <iostream>

#include <Windows.h>
#include "memories.hpp"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {

    SkoarConsoleLogger SkoarLog;
    
    SkoarLite(L"a ) ]]", &SkoarLog);

    wstring instr;
    SkoarLog.i("Done", SkoarMemories);
    std::wcin >> instr;

}


