#include "wordnet.h"
#include <queue>

ShortestCommonAncestor::ShortestCommonAncestor(Digraph &dg) : dg(dg) {}

void ShortestCommonAncestor::init_vector_distance(int v, int ancestor, std::vector<int> &min_length_road_from_v) {
    min_length_road_from_v[v] = 0;
    std::queue<int> queue_ids_v;
    queue_ids_v.push(v);
    while(!queue_ids_v.empty()) {
        int cur_id = queue_ids_v.front(); queue_ids_v.pop();
        if (cur_id == ancestor) {
            return;
        }
        for (int next_id : dg.vector_hyponym(cur_id)) {
            if (min_length_road_from_v[next_id] > min_length_road_from_v[cur_id] + 1) {
                min_length_road_from_v[next_id] = min_length_road_from_v[cur_id] + 1;
                queue_ids_v.push(next_id);
            }
        }
    }
}

int ShortestCommonAncestor::length(int v, int w) {
    std::vector<int> min_length_road_from_v(dg.size(), std::numeric_limits<int>::max());
    std::vector<int> min_length_road_from_w(dg.size(), std::numeric_limits<int>::max());

    int ancestor = ShortestCommonAncestor::ancestor(v, w);

    init_vector_distance(v, ancestor, min_length_road_from_v);
    init_vector_distance(w, ancestor, min_length_road_from_w);

    return min_length_road_from_v[ancestor] + min_length_road_from_w[ancestor];
}

int ShortestCommonAncestor::ancestor(int v, int w) {
    std::vector<bool> hyponym_v(dg.size());
    std::queue<int> queue_ids_v;
    queue_ids_v.push(v);
    while(!queue_ids_v.empty()) {
        int cur_id = queue_ids_v.front(); queue_ids_v.pop();
        hyponym_v[cur_id] = true;
        for (int next_ids : dg.vector_hyponym(cur_id)) {
            if (!hyponym_v[next_ids]) {
                queue_ids_v.push(next_ids);
            }
        }
    }
    std::queue<int> queue_ids_w;
    queue_ids_w.push(w);
    //hyponym_v[root] always true
    while(true) {
        int cur_id = queue_ids_w.front(); queue_ids_w.pop();
        if (hyponym_v[cur_id]) {
            return cur_id;
        }
        for (int next_ids : dg.vector_hyponym(cur_id)) {
            queue_ids_w.push(next_ids);
        }
    }
}

int ShortestCommonAncestor::length_subset(const std::set<int> &subset_a, const std::set<int> &subset_b) {
    int ans = std::numeric_limits<int>::max();
    for (int i : subset_a) {
        for (int j : subset_b) {
            ans = std::min(ans, length(i, j));
        }
    }
    return ans;
}

int ShortestCommonAncestor::ancestor_subset(const std::set<int> &subset_a, const std::set<int> &subset_b) {
    int ans = dg.get_root_id();
    int length = std::numeric_limits<int>::max();
    for (int i : subset_a) {
        for (int j : subset_b) {
            int cur_length = ShortestCommonAncestor::length(i, j);
            if (length > cur_length) {
                length = cur_length;
                ans = ancestor(i, j);
            }
        }
    }
    return ans;
}
