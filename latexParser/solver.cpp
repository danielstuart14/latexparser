#include "solver.hpp"
#include "sanitize.hpp"

std::string logicSolver(std::string expression_string) {

    std::vector<std::vector<bool>> values;
    std::vector<std::string> chars;
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

    std::string latexTable = "\t\t\\begin{table}[]\n\t\t\\begin{tabular}{";
    for (int x = 0; x <= chars.size(); x++)
        latexTable += "\|c";
    latexTable += "|}\n\t\t\\hline\n\t\t";

    for(int x=0; x<chars.size(); x++) 
        latexTable += chars[x] + " & ";

    latexTable+= "$" + latexFormula + "$ \\\\\n\t\t\\hline\n\t\t";

    std::string json = "{\n\t\"formula\": \"" + expression_string + "\",";

    for (int x = 0; x < values[0].size(); x++) {
        for (int y = 0; y < values.size() - 1; y++) {
            latexTable += std::string(values[y][x] ? "T" : "F") + " & ";
        }
        latexTable += std::string(values[values.size() - 1][x] ? "T" : "F");
        latexTable += " \\\\\n\t\t\\hline\n\t\t";
    }
    latexTable += "\\end{tabular}\n\t\t\\end{table}";


    for (int x = 0; x < values.size(); x++) {
        json += "\n\t\t\"" + (x < charsize ? chars[x] : "result") + "\": [";
        for (int y = 0; y < values[x].size(); y++) {
            json += std::string(values[x][y] ? "\"T\"" : "\"F\"") + ",";
        }
        json = json.substr(0, json.size() - 1);
        json += "],";
    }

    json = json.substr(0, json.size() - 1);
    json += "\n\t},\n\t\"latexTable\":{\n"+latexTable+"\n\t}\n";
    json += "\n}";

    return json;
}