#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class LFUCache {
private:
    int capacity, minFreq;
    unordered_map<int, pair<int, int>> keyValFreq;
    unordered_map<int, set<int>> freqKeys;
    unordered_map<int, int> keyToFreq;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (keyValFreq.find(key) == keyValFreq.end()) return -1;
        int val = keyValFreq[key].first, freq = keyValFreq[key].second;
        freqKeys[freq].erase(key);
        if (freqKeys[freq].empty()) {
            freqKeys.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        freqKeys[freq + 1].insert(key);
        keyValFreq[key] = {val, freq + 1};
        keyToFreq[key] = freq + 1;
        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyValFreq.find(key) != keyValFreq.end()) {
            keyValFreq[key].first = value;
            get(key);
            return;
        }
        if (keyValFreq.size() == capacity) {
            int lfuKey = *freqKeys[minFreq].begin();
            freqKeys[minFreq].erase(lfuKey);
            if (freqKeys[minFreq].empty()) freqKeys.erase(minFreq);
            keyValFreq.erase(lfuKey);
            keyToFreq.erase(lfuKey);
        }
        keyValFreq[key] = {value, 1};
        freqKeys[1].insert(key);
        keyToFreq[key] = 1;
        minFreq = 1;
    }
};

int main() {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout << lfu.get(1) << endl;
    lfu.put(3, 3);
    cout << lfu.get(2) << endl;
    cout << lfu.get(3) << endl;
    lfu.put(4, 4);
    cout << lfu.get(1) << endl;
    cout << lfu.get(3) << endl;
    cout << lfu.get(4) << endl;
    return 0;
}
