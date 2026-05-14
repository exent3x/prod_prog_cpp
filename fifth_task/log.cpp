#include "log.h"

class Log::Impl {
public:
    struct Event {
        LogLevel level;
        std::string msg;
        std::time_t time;
    };
    std::deque<Event> events;

    static const char* levelName(LogLevel lv);
};

const char* Log::Impl::levelName(LogLevel lv) {
    switch (lv) {
        case LOG_NORMAL: return "NORMAL";
        case LOG_REMARK: return "REMARK";
        case LOG_ERROR:  return "ERROR";
        default:         return "UNKNOWN";
    }
}

Log::Log() : pImpl(std::make_unique<Impl>()) {}

Log::~Log() = default;

Log* Log::Instance() {
    static Log instance;
    return &instance;
}

void Log::message(LogLevel level, const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    pImpl->events.push_back({level, msg, t});
    if (pImpl->events.size() > 10)
        pImpl->events.pop_front();
}

void Log::print() const {
    for (const auto& e : pImpl->events) {
        std::tm tm = *std::localtime(&e.time);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
        std::cout << buf << " [" << Impl::levelName(e.level) << "] "
                  << e.msg << '\n';
    }
}