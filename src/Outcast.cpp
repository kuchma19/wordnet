#include "wordnet.h"

Outcast::Outcast(WordNet &wordnet) : wordnet(wordnet){
}

std::string Outcast::outcast(const std::vector<std::string> &nouns) {
    if (nouns.size() <= 2) {
        return "";
    }
    std::string answer;
    int distance = std::numeric_limits<int>::min();
    std::vector<std::string> filter_nouns;
    for (std::size_t i = 0; i < nouns.size(); i++) {
        if (wordnet.is_noun(nouns[i])) {
            filter_nouns.push_back(nouns[i]);
        }
    }
    for (std::size_t i = 0; i < filter_nouns.size(); i++) {
        int cur_distance = 0;
        for (std::size_t j = 0; j < filter_nouns.size(); j++) {
            cur_distance += wordnet.distance(nouns[i], nouns[j]);
        }
        if (cur_distance > distance) {
            answer = filter_nouns[i];
            distance = cur_distance;
        }
    }

    return answer;
}

