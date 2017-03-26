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
    
    //Skoar(L"a ) ]] 0", &SkoarLog);
    
    //SkoarLog.i("Skoar done", SkoarMemories);
    //SkoarLog.i("\n");

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

    SkoarLog.setLevel(ISkoarLog::debug);
    Skoar fun(L"a: 'hello' ] a: 'world' ) b: 7 + 2.2 ]]] b: 7.0 + 2.8 }}} b: 7.2 + 1 ]]] c: 4 + false ))) a: =^.^=  b: 2.2 1.1 }}", &SkoarLog);
    SkoarLog.i("Skoar done", SkoarMemories);
    SkoarLog.i("\n");

    fun.play([&](SkoarEventPtr e) {
        auto xs = e->at(L"a");
        auto ds = e->at(L"dur");

        SkoarString x;
        SkoarFloat d;

        if (is_skoarpuscle<SkoarpuscleString>(xs)) {
            x = skoarpuscle_ptr<SkoarpuscleString>(xs)->val;
        }
        else {
            x = L"";
        }

        if (is_skoarpuscle<SkoarpuscleFloat>(ds)) {
            d = skoarpuscle_ptr<SkoarpuscleFloat>(ds)->val;
        }
        else {
            d = 0.0;
        }

        SkoarLog.w("yay", x, d);

        wostringstream out;
        for (auto kv : e->table) {
            out << "\n" << kv.first << ": ";
            
            if (kv.second != nullptr)
                out << *(kv.second);
            else
                out << "=^.^=";

            if (check_skoarpuscle_val<SkoarpuscleString, SkoarString>(kv.second, L"hello")) {
                out << "  helloooo found!!!";
            }

            list<SkoarFloat> desires = { 1.1, 2.2, 3.3, 4.4, 5.5 };
            if (check_skoarpuscle_val_in<SkoarpuscleFloat, SkoarFloat>(kv.second, desires)) {
                out << "  desire found!!!";
            }

        }
        SkoarLog.i("Event", out.str());
    });
    
    wstring instr;
    std::wcin >> instr;
}


