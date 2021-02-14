#include "wordnet.h"
#include <fstream>
#include <cctype>
#include <cstdlib>

WordNet::WordNet(const std::string &synsets_fn, const std::string &hypernyms_fn) : digraph(hypernyms_fn), shortestCommonAncestor(digraph){
    std::ifstream in(synsets_fn);
    std::string s;
    while(std::getline(in, s)) {
        std::size_t i = 0;
        std::string s_id;
        while(i < s.size() && isdigit(s[i])) {
            s_id.push_back(s[i++]);
        }
        unsigned id = atoi(s_id.c_str());
        i++; //,
        std::string word;
        while(i < s.size()) {
            if (s[i] == ' ' || s[i] == ',') {
                set_nouns.insert(word);
                string_set_ids[word].insert(id);
                word.clear();
                if (s[i] == ',') {
                    i++;
                    std::string gloss;
                    while(i < s.size()) {
                        gloss.push_back(s[i++]);
                    }
                    id_to_gloss[id] = gloss;
                }
            } else {
                word.push_back(s[i]);
            }
            i++;
        }
    }
    in.close();

}

WordNet::Iterator WordNet::nouns() {
    return set_nouns.begin();
}

WordNet::Iterator WordNet::end() {
    return set_nouns.end();
}

bool WordNet::is_noun(const std::string &word) const {
    return set_nouns.count(word) == 1;
}

std::string WordNet::sca(const std::string &noun1, const std::string &noun2) {
    return id_to_gloss.at(shortestCommonAncestor.ancestor_subset(string_set_ids.at(noun1), string_set_ids.at(noun2)));
}

int WordNet::distance(const std::string &noun1, const std::string &noun2) {
    return shortestCommonAncestor.length_subset(string_set_ids.at(noun1), string_set_ids.at(noun2));
}

