#include <bits/stdc++.h>
# define long long long
using namespace std;

template <typename Key, typename Value, typename Compare = std::less<Value>>
class IndexedHeap {
public:
    using Entry = std::pair<Key, Value>;

    void push(const Key& key, const Value& value) {
        if (key_to_index.count(key)) throw std::invalid_argument("Key already exists");
        data.emplace_back(key, value);
        key_to_index[key] = data.size() - 1;
        sift_up(data.size() - 1);
    }

    void update(const Key& key, const Value& new_value) {
        auto it = key_to_index.find(key);
        if (it == key_to_index.end()) throw std::invalid_argument("Key not found");

        size_t idx = it->second;
        data[idx].second = new_value;
        sift_up(idx);
        sift_down(idx);
    }

    void erase(const Key& key) {
        auto it = key_to_index.find(key);
        if (it == key_to_index.end()) throw std::invalid_argument("Key not found");

        size_t idx = it->second;
        size_t last = data.size() - 1;
        swap_entries(idx, last);
        data.pop_back();
        key_to_index.erase(key);

        if (idx < data.size()) {
            sift_up(idx);
            sift_down(idx);
        }
    }

    const Entry& top() const {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        return data.front();
    }

    void pop() {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        erase(data.front().first);
    }

    bool contains(const Key& key) const {
        return key_to_index.count(key);
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

private:
    std::vector<Entry> data;
    std::unordered_map<Key, size_t> key_to_index;
    Compare comp;

    void sift_up(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (!comp(data[idx].second, data[parent].second)) break;
            swap_entries(idx, parent);
            idx = parent;
        }
    }

    void sift_down(size_t idx) {
        size_t n = data.size();
        while (true) {
            size_t smallest = idx;
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;

            if (left < n && comp(data[left].second, data[smallest].second)) smallest = left;
            if (right < n && comp(data[right].second, data[smallest].second)) smallest = right;

            if (smallest == idx) break;
            swap_entries(idx, smallest);
            idx = smallest;
        }
    }

    void swap_entries(size_t i, size_t j) {
        std::swap(data[i], data[j]);
        key_to_index[data[i].first] = i;
        key_to_index[data[j].first] = j;
    }
};