#pragma once

#include <set>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
class Digraph
{
    using digraph_type = std::vector<std::vector<int>>;
    digraph_type G;
    int root;
public:
    Digraph(const std::string & hypernyms_fn);

    const std::vector<int> & vector_hyponym(int v) const {
        return G[v];
    }

    std::size_t size() {
        return G.size();
    }

    int get_root_id() {
        return root;
    }
};

class ShortestCommonAncestor
{
    Digraph & dg;

    void init_vector_distance(int v, std::vector<int> &min_length_road_from_v);

    void init_vector_distance(int v, int ancestor, std::vector<int> &min_length_road_from_v);

public:

    ShortestCommonAncestor(Digraph & dg);
    // calculates length of shortest common ancestor path from node with id 'v' to node with id 'w'
   int length(int v, int w);

   // returns node id of shortest common ancestor of nodes v and w
   int ancestor(int v, int w);

   // calculates length of shortest common ancestor path from node subset 'subset_a' to node subset 'subset_b'
   int length_subset(const std::set<int> & subset_a, const std::set<int> & subset_b);

   // returns node id of shortest common ancestor of node subset 'subset_a' and node subset 'subset_b'
   int ancestor_subset(const std::set<int> & subset_a, const std::set<int> & subset_b);

};

class WordNet
{
    std::set<std::string> set_nouns;
    std::map<std::string, std::set<int>> string_set_ids;
    std::unordered_map<int, std::string> id_to_gloss;
    Digraph digraph;
    ShortestCommonAncestor shortestCommonAncestor;
public:

    WordNet(const std::string & synsets_fn, const std::string & hypernyms_fn);

    // Please implement...
    using Iterator = std::set<std::string>::const_iterator;

    // get iterator to list all nouns stored in WordNet
    Iterator nouns();
    Iterator end();

    // returns 'true' iff 'word' is stored in WordNet
    bool is_noun(const std::string & word) const;

    // returns gloss of "shortest common ancestor" of noun1 and noun2
    std::string sca(const std::string & noun1, const std::string & noun2);

    // calculates distance between noun1 and noun2
    int distance(const std::string & noun1, const std::string & noun2);

};

class Outcast
{
    WordNet wordnet;
public:
   Outcast(WordNet & wordnet);

   // returns outcast word
   std::string outcast(const std::vector<std::string> & nouns);
};
