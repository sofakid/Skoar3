#include "skoarcery.hpp"

#include "lex_fwd.hpp"

#include <vector>

class SkoarLine {
public:
	wstring line;
	vector<SkoarToke *> tokes;
};

class SkoarBufCursor {
public:
	int line_no;
	int char_pos;
};

class SkoarBuf {
	vector<SkoarLine *> lines;
	
public:

	SkoarBuf(wstring&);

	void load_string(wstring&);

	void update_line(int line_no, int start, int end, wstring &new_text);
	void update_lines(int line_start, int line_end, int start, int end, wstring &new_text);


};