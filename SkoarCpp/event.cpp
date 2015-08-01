#include "event.hpp"

#include "skoarpuscle.hpp"
#include "exception.hpp"

SkoarDic::SkoarDic() {
	//not_found = nullptr;
}

Skoarpuscle* &SkoarDic::operator[](string *key) {
	if (key == nullptr)
		throw SkoarError("Tried to use a null key on a SkoarDic.");

	return table[*key];
}

Skoarpuscle* &SkoarDic::operator[](string key) {
	return table[key];
}

void SkoarEvent::from(SkoarDic *dic) {
	auto src = dic->table;
	if (src.empty())
		return;

	for (auto pair : src) {
		auto key = pair.first;
		auto skoarpuscle = pair.second;
		table[key] = skoarpuscle;
	}
}

