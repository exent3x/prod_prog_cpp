#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <filesystem>

namespace fs = std::filesystem;

class JsonWriter {
public:
    explicit JsonWriter(const std::string& fullpath)
        : filepath(fs::u8path(fullpath)) {
        createParentDir();
    }

    JsonWriter(const std::string& folder, const std::string& fname)
        : filepath(fs::u8path(folder) / fs::u8path(fname)) {
        createParentDir();
    }

    ~JsonWriter() { flush(); }

    JsonWriter(const JsonWriter&) = delete;
    JsonWriter& operator=(const JsonWriter&) = delete;

    JsonWriter(JsonWriter&& other) noexcept
        : filepath(std::move(other.filepath)), data(std::move(other.data)) {
        other.filepath.clear();
    }

    JsonWriter& operator=(JsonWriter&& other) noexcept {
        if (this != &other) {
            flush();
            filepath = std::move(other.filepath);
            data = std::move(other.data);
            other.filepath.clear();
        }
        return *this;
    }

    void Add(const std::string& key, const std::string& value) {
        data[key] = value;
    }

private:
    void createParentDir() {
        fs::path parent = filepath.parent_path();
        if (!parent.empty() && !fs::exists(parent)) {
            fs::create_directories(parent);
        }
    }

    void flush() {
        if (filepath.empty()) return;
        std::ofstream file(filepath, std::ios::binary);
        if (!file.is_open()) return;

        file << "{\n";
        bool first = true;
        for (const auto& [key, value] : data) {
            if (!first) file << ",\n";
            file << "  \"" << escape(key) << "\": \"" << escape(value) << '"';
            first = false;
        }
        file << "\n}\n";
    }

    static std::string escape(const std::string& s) {
        std::string result;
        result.reserve(s.size() * 2);
        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);
            switch (c) {
                case '"':  result += "\\\""; break;
                case '\\': result += "\\\\"; break;
                case '\b': result += "\\b";  break;
                case '\f': result += "\\f";  break;
                case '\n': result += "\\n";  break;
                case '\r': result += "\\r";  break;
                case '\t': result += "\\t";  break;
                default:
                    if (uc < 0x20) {
                        static const char hex[] = "0123456789ABCDEF";
                        result += "\\u00";
                        result += hex[uc >> 4];
                        result += hex[uc & 0xF];
                    } else {
                        result += c;
                    }
                    break;
            }
        }
        return result;
    }

    fs::path filepath;
    std::map<std::string, std::string> data;
};

class JSON {
public:
    explicit JSON(const std::string& fullpath) : writer(fullpath) {}
    JSON(const std::string& folder, const std::string& fname) : writer(folder, fname) {}

    JSON(const JSON&) = delete;
    JSON& operator=(const JSON&) = delete;

    JSON(JSON&&) = default;
    JSON& operator=(JSON&&) = default;

    void Add(const std::string& key, const std::string& value) {
        writer.Add(key, value);
    }

private:
    JsonWriter writer;
};

int main() {
    JSON j1("../", "json1.json");
    j1.Add("name", "ADOLF");
    j1.Add("age", "1488");

    JSON j2 = std::move(j1);
    j2.Add("city", "Berlin");

    return 0;
}