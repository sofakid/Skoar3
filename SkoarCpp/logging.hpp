#pragma once

class ISkoarLog {
public:
	virtual void d(const std::wstring &s) = 0;
	virtual void i(const std::wstring &s) = 0;
	virtual void w(const std::wstring &s) = 0;
	virtual void e(const std::wstring &s) = 0;
};
