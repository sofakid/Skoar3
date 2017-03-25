#include "skoar_public.hpp"
#include <iostream>

#include <Windows.h>
#include "memories.hpp"
#include "operators.hpp"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {

    SkoarConsoleLogger SkoarLog;
    
    //SkoarLite(L"a ) ]]", &SkoarLog);

    //SkoarLog.i("SkoarLite done", SkoarMemories);
    //SkoarLog.i("\n");

    //auto x = make_skoarpuscle((SkoarInt)2);
    //auto y = make_skoarpuscle((SkoarInt)3);

    //auto z = SkoarOperations::add(*skoarpuscle_ptr<SkoarpuscleInt>(x), *skoarpuscle_ptr<SkoarpuscleInt>(y), nullptr);
    
    //SkoarLog.i("2 + 3", skoarpuscle_ptr<SkoarpuscleInt>(z)->val);
    
    Skoar(L"a ) ]] 0", &SkoarLog);
    
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");

    /*
    Skoar(L"a ) ]] {! derp<x> !! !x ) 0 a# !} !derp<2>  \n\n\n55 nine: 9 @food {! dorp<s:6> !! @worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");

    Skoar(L"a ) ]] {! derp<x> !! !x ) 0 a# !} !derp<2>  \n\n\n55 nine: 9 @food {! dorp<s:6> !! @worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");

    Skoar(L".alice a ))\n.bob b ))", &SkoarLog);
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");

    Skoar(L"{! derp !!\n.alice 0\n.bob 0\n.alice 1\n.bob 1!}", &SkoarLog);
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");
    */

    /*
    Skoar fun(L"a: 'hello world' ] b:2 )", &SkoarLog);
    fun.play([&](SkoarEventPtr e) {
        SkoarLog.w("yay", e->at(L"a"), e->at(L"dur"));
    });
    */
    wstring instr;
    std::wcin >> instr;
}

