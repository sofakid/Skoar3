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

    void draw_tree(wostringstream &stream);
};



class SkoarpionProjection {
public:
    SkoarNoadPtr proj;
    const SkoarString name;

    SkoarpionProjection(SkoarpionPtr, SkoarString);
    ~SkoarpionProjection();

    /*list<SkoarInt> get_skip_to();
    SkoarString    get_name();
    SkoarNoadPtr   block();
    SkoarNoadPtr   in_line();
    SkoarNoadPtr   meditation();
    */
    SkoarNoadAddress map_dst(SkoarNoadPtr);

    //void draw_tree(wostringstream &stream);

private:
    SkoarNoadPtr body;
    

    SkoarNoadAddress skip_to;

    // do we need these? from SkoarIteratoar
    //list<SkoarNoadPtr> arr;
    //size_t i;
    //size_t n;


};
