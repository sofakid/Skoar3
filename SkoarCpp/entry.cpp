#include "skoar_public.hpp"
#include <iostream>

#include <Windows.h>
#include "memories.hpp"
#include "operators.hpp"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {

    SkoarConsoleLogger SkoarLog;
    
    SkoarLite(L"a ) ]]", &SkoarLog);

    SkoarLog.i("Done", SkoarMemories);
    

    auto x = make_skoarpuscle((SkoarInt)2);
    auto y = make_skoarpuscle((SkoarInt)3);

    //auto z = SkoarOperations::add(*skoarpuscle_ptr<SkoarpuscleInt>(x), *skoarpuscle_ptr<SkoarpuscleInt>(y), nullptr);
    
    //SkoarLog.i("2 + 3", skoarpuscle_ptr<SkoarpuscleInt>(z)->val);

    wstring instr;
    std::wcin >> instr;
}


