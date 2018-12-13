#pragma once
#include "skoarpuscle.hpp"

class SkoarpuscleMeditation : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleMeditation" << " :: " ; }
    SkoarpuscleMeditation (Skoar*, SkoarNoadPtr);
    SkoarpuscleMeditation (SkoarpionPtr);
    ~SkoarpuscleMeditation () override;
    void clear ();

    SkoarpusclePtr duplicate () override;
    void on_enter (SkoarMinstrelPtr) override;

    void run (SkoarMinstrelPtr m);
    SkoarpusclePtr skoar_msg (SkoarString, SkoarpusclePtr, SkoarMinstrelPtr) override;


private:
    SkoarpionPtr skoarpion;
};

class SkoarpuscleMeditationMsg : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleMeditationMsg" << " :: " ; }
    SkoarpuscleMeditationMsg(Skoar*, SkoarNoadPtr);
};
