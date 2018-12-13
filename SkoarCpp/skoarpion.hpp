#pragma once
#include "skoarcery.hpp"
#include "skoar_fwd.hpp"
#include "noad_fwd.hpp"		
#include "skoarpuscle_fwd.hpp"

#include "skoarpion_fwd.hpp"

#include "spells.hpp"

#include "noad.hpp"

class Skoarpion {
public:

    static SkoarpionPtr NewFromSkoar(Skoar *skoar);
    static SkoarpionPtr NewFromSkoarNoad(Skoar *skoar, SkoarNoadPtr noad);
    static SkoarpionPtr NewFromSubtree(Skoar*, SkoarNoadPtr);

    Skoar *skoar;
    SkoarNoadPtr body;
    SkoarString name;
    SkoarpusclePtr arg_list;
    ListOfSkoarStrings capture_list;
    ListOfSkoarStrings expoart_list;
    SkoarInt n;

    const SkoarString made_from;

    Skoarpion(const SkoarString);
    Skoarpion(const Skoarpion *);
    ~Skoarpion();

    void clear();

    void init_from_skoar(Skoar*);                 // the entire skoar gets put in a skoarpion
    void init_from_noad(Skoar*, SkoarNoadPtr);    // a literal skoarpion, like {! derp !! ... !}
    void init_from_subtree(Skoar*, SkoarNoadPtr); // chunks of the tree sucked into skoarpions
                                                  // i.e. conditions, if bodies, else bodies
    static SkoarpionProjectionPtr projection(SkoarpionPtr skoarpion, SkoarString);

    static ListOfSkoarpionProjectionsPtr get_projections(SkoarpionPtr skoarpion, const ListOfSkoarStrings&);

    void draw_tree(std::wostringstream &stream);
};



class SkoarpionProjection {
public:
    const SkoarString name;
    const SkoarString voice_name;
    std::vector<SkoarNoadite> noadites;

    SkoarpionProjection(SkoarpionPtr, SkoarString);
    ~SkoarpionProjection();

    //SkoarNoadAddress map_dst(SkoarNoadPtr);

    void draw(std::wostringstream &stream);

private:
    //SkoarNoadAddress skip_to;

};
