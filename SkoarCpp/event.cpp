#include "event.hpp"

#include "skoarpuscle.hpp"
#include "exception.hpp"

SkoarDic::SkoarDic() {
	//not_found = nullptr;
}

SkoarpusclePtr &SkoarDic::operator[](wstring *key) {
	if (key == nullptr)
		throw SkoarError(L"Tried to use a null key on a SkoarDic.");

	return table[*key];
}

SkoarpusclePtr &SkoarDic::operator[](wstring key) {
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

