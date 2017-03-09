#pragma once
#include <sstream>

class ISkoarLog {
public:
    const enum Level {
        debug = 0,
        info,
        warning,
        error
    };

    template<typename... Args>
    void d(const Args&... args) {
        if (logLevel == Level::debug) {
            log_d(build_msg(L"-- D", args...));
        }
    }

    template<typename... Args>
    void i(const Args&... args) {
        if (logLevel <= Level::info)
            log_i(build_msg(L"== I", args...));
    }

    template<typename... Args>
    void w(const Args&... args) {
        if (logLevel <= Level::warning)
            log_w(build_msg(L"?? W", args...));
    }

    template<typename... Args>
    void e(const Args&... args) {
        if (logLevel <= Level::error)
            log_e(build_msg(L"!! E", args...));
    }

    virtual void log_d(const std::wstring &s) = 0;
    virtual void log_i(const std::wstring &s) = 0;
    virtual void log_w(const std::wstring &s) = 0;
    virtual void log_e(const std::wstring &s) = 0;

    void setLevel(Level level) {
        logLevel = level;
    }

    Level getLevel() {
        return logLevel;
    }

private:
    Level logLevel = Level::info;

    template<typename Type, typename... Args>
    void build_msg_r(std::wostringstream& msg, Type value, const Args&... args)
    {
        msg << L" :: " << value;
        build_msg_r(msg, args...);
    }

    void build_msg_r(std::wostringstream& msg)
    {
        msg << std::endl;
    }

    template<typename... Args>
    const std::wstring build_msg(const std::wstring &prefix, const Args&... args) {
        std::wostringstream msg;
        msg << prefix;
        build_msg_r(msg, args...);
        return msg.str();
    }
};
