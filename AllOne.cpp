#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class AllOne {
private:
    struct Bucket {
        int count;
        unordered_map<string, list<Bucket>::iterator>::iterator pos;
        list<string> keys;
    };

    list<Bucket> buckets;
    unordered_map<string, list<string>::iterator> keyToPos;
    unordered_map<string, list<Bucket>::iterator> keyToBucket;

public:
    AllOne() {}

    void inc(string key) {
        if (keyToBucket.find(key) == keyToBucket.end()) {
            if (buckets.empty() || buckets.front().count > 1) {
                buckets.push_front({1});
            }
            buckets.front().keys.push_back(key);
            keyToPos[key] = --buckets.front().keys.end();
            keyToBucket[key] = buckets.begin();
        } else {
            auto it = keyToBucket[key];
            auto nextIt = next(it);
            if (nextIt == buckets.end() || nextIt->count > it->count + 1) {
                nextIt = buckets.insert(nextIt, {it->count + 1});
            }
            nextIt->keys.push_back(key);
            keyToPos[key] = --nextIt->keys.end();
            keyToBucket[key] = nextIt;
            it->keys.erase(keyToPos[key]);
            if (it->keys.empty()) {
                buckets.erase(it);
            }
        }
    }

    void dec(string key) {
        auto it = keyToBucket[key];
        if (it->count == 1) {
            it->keys.erase(keyToPos[key]);
            keyToBucket.erase(key);
            keyToPos.erase(key);
        } else {
            auto prevIt = it;
            if (it == buckets.begin() || prev(it)->count < it->count - 1) {
                prevIt = buckets.insert(it, {it->count - 1});
            } else {
                --prevIt;
            }
            prevIt->keys.push_back(key);
            keyToPos[key] = --prevIt->keys.end();
            keyToBucket[key] = prevIt;
            it->keys.erase(keyToPos[key]);
        }
        if (it->keys.empty()) {
            buckets.erase(it);
        }
    }

    string getMaxKey() {
        return buckets.empty() ? "" : buckets.back().keys.front();
    }

    string getMinKey() {
        return buckets.empty() ? "" : buckets.front().keys.front();
    }
};

int main() {
    AllOne allOne;
    allOne.inc("Amit");
    allOne.inc("Amit");
    cout << allOne.getMaxKey() << endl;
    cout << allOne.getMinKey() << endl;
    allOne.inc("leet");
    cout << allOne.getMaxKey() << endl;
    cout << allOne.getMinKey() << endl;
    return 0;
}
