#include <iostream>
#include "cparse.hpp"
#include "sanitize.hpp"

std::string logic(std::string);

#ifdef EMSCRIPTEN
    #include <emscripten/bind.h>
    using namespace emscripten;

    EMSCRIPTEN_BINDINGS(my_module) {
        function("logic", &logic);
    }

#else

int main()
{
    cparseStartup();

    std::string s;
    std::getline(std::cin, s);
    sanitize(&s);

    std::cout << logic(s);

    return 0;
}

#endif

std::string logic(std::string expression_string) {

    std::vector<std::vector<bool>> values;
    std::vector<std::string> chars;
    std::string json = "{";
    TokenMap vars;

    for (std::size_t i = 0; i < expression_string.size(); i++) {
        if (expression_string[i] >= 'A' && expression_string[i] <= 'Z') {
            bool exists = false;
            for (std::size_t j = 0; j < chars.size(); j++)
                if (expression_string[i] == chars[j][0]) exists = true;
            if (!exists) {
                chars.push_back(std::string(1, expression_string[i]));
                values.push_back({});
            }
        }
    }
    values.push_back({});

    std::size_t charsize = chars.size();

    for (int i = 0; i < 0b01 << charsize; ++i) {
        for (std::size_t j = 0; j < charsize; j++) {
            vars[chars[j]] = int(i & (0x01 << (charsize - 1 - j)) ? 1 : 0);
            values[j].push_back(vars[chars[j]].asBool());
        }

        vars["RESULT"] = calculator::calculate(expression_string.data(), vars);
        values[values.size() - 1].push_back(vars["RESULT"].asBool());
    }

    for (int x = 0; x < values.size(); x++) {
        json += "\n\t\"" + (x < charsize ? chars[x] : "result") + "\": [";
        for (int y = 0; y < values[x].size(); y++) {
            json += std::string(values[x][y] ? "\"T\"" : "\"F\"") + ",";
        }
        json = json.substr(0, json.size() - 1);
        json += "],";
    }
    json = json.substr(0, json.size() - 1);
    json += "\n}";

    return json;
}