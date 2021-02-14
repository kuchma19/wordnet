#include <fstream>
#include "wordnet.h"

Digraph::Digraph(const std::string &hypernyms_fn) {
    std::ifstream in(hypernyms_fn);
    std::string line;
    while(getline(in, line)) {
        std::size_t i = 0;
        std::string s_id;
        std::vector<unsigned> ids;
        while(i < line.size()) {
            if (line[i] == ',') {
                ids.emplace_back(atoi(s_id.c_str()));
                s_id.clear();
            } else {
                s_id.push_back(line[i]);
            }
            i++;
        }
        ids.emplace_back(atoi(s_id.c_str()));
        if (ids.size() == 1) {
            root = ids[0];
        }
        G.emplace_back();
        //ids[0] == G.size() - 1
        for (std::size_t j = 1; j < ids.size(); j++) {
            G.back().push_back(ids[j]);
        }
    }
    in.close();
}

