#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cacheList; // Doubly Linked List (stores key-value pairs)
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap; // Hashmap (key -> iterator in list)

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1; // Key not found
        }

        // Move the accessed element to the front (most recently used)
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return cacheMap[key]->second;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // Key exists, update value and move to front
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key]->second = value;
            return;
        }

        // If at capacity, remove least recently used element (tail of list)
        if (cacheList.size() == capacity) {
            int lruKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(lruKey);
        }

        // Insert new element at the front
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};

// Main function for testing
int main() {
    LRUCache lru(2); // Cache capacity = 2
    lru.put(1, 1);
    lru.put(2, 2);
    cout << lru.get(1) << endl; // returns 1
    lru.put(3, 3); // removes key 2
    cout << lru.get(2) << endl; // returns -1 (not found)
    lru.put(4, 4); // removes key 1
    cout << lru.get(1) << endl; // returns -1 (not found)
    cout << lru.get(3) << endl; // returns 3
    cout << lru.get(4) << endl; // returns 4

    return 0;
}
