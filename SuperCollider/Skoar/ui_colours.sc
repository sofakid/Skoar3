SkoarUiColours {

    *style_noad {
        | noad |
        var toke = noad.toke;

        if (toke.notNil) {
            noad.style = SkoarUiColourTemplate.defaults[toke.name];
        } {
            noad.style = SkoarUiColourTemplate.defaults[noad.name];
        };
    }

}