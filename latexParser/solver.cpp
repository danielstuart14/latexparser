#include "solver.hpp"
#include "sanitize.hpp"

std::string logicSolver(std::string expression_string, std::string variables) {

    std::vector<std::vector<bool>> values;
    std::vector<std::string> chars;
    TokenMap vars;

    for (int i = 0; i < variables.size(); i++) {
        chars.push_back(std::string(1, variables[i]));
        values.push_back({});
    }

    values.push_back({});

    std::size_t charsize = chars.size();

    for (int i = 0; i < 0b01 << charsize; ++i) {
        for (std::size_t j = 0; j < charsize; j++) {
            if(chars[j]=="T") vars[chars[j]] = 1;
            else if(chars[j]=="F") vars[chars[j]] = 0;
            else vars[chars[j]] = int(i & (0x01 << (charsize - 1 - j)) ? 1 : 0);
            values[j].push_back(vars[chars[j]].asBool());
        }

        try {
            vars["RESULT"] = calculator::calculate(expression_string.data(), vars);
            values[values.size() - 1].push_back(vars["RESULT"].asBool());
        } 
        catch (...) {
            return "{}";
        }
    }
    
    std::string latexFormula = expression_string;
    latex(&latexFormula);

    std::string latexTable = "\\\\begin{table}[]\\n \\\\begin{tabular}{";
    for (int x = 0; x <= chars.size(); x++)
        latexTable += "|c";
    latexTable += "|}\\n\\\\hline\\n";

    for(int x=0; x<chars.size(); x++) 
        latexTable += chars[x] + " & ";

    latexTable+= "$" + latexFormula + "$ \\\\\\\\\\\\n\\\\hline\\n";

    std::string json = "{\n\t\"formula\": \"" + expression_string + "\",";
    json += "\n\t\"truthTable\": {";

    for (int x = 0; x < values[0].size(); x++) {
        for (int y = 0; y < values.size() - 1; y++) {
            latexTable += std::string(values[y][x] ? "T" : "F") + " & ";
        }
        latexTable += std::string(values[values.size() - 1][x] ? "T" : "F");
        latexTable += " \\\\\\\\\\\\n\\\\hline\\n";
    }
    latexTable += "\\\\end{tabular}\\n\\\\end{table}";


    for (int x = 0; x < values.size(); x++) {
        json += "\n\t\t\"" + (x < charsize ? chars[x] : "result") + "\": [";
        for (int y = 0; y < values[x].size(); y++) {
            json += std::string(values[x][y] ? "\"T\"" : "\"F\"") + ",";
        }
        json = json.substr(0, json.size() - 1);
        json += "],";
    }

    json = json.substr(0, json.size() - 1);
    json += "\n\t},\n\t\"latexTable\": \""+latexTable+"\"\n";
    json += "}";

    return json;
}