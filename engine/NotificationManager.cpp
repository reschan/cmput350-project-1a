#include "NotificationManager.h"
#include <unordered_map>

namespace CMPUT350 {

void NotificationManager::Register(std::weak_ptr<GameObject> object, const std::string& key) {
    if (mListeners.contains(key)) { // add to existing map
        mListeners.at(key).push_back(object);
    } else { // add new map
        std::vector<std::weak_ptr<GameObject>> list;
        list.push_back(object);
        mListeners.insert(
            std::pair<std::string, std::vector<std::weak_ptr<GameObject>>>(key, list));
    }
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object, const std::string& key) {
    auto i = std::find_if(mListeners.at(key).begin(), mListeners.at(key).end(),
                          [object](std::weak_ptr<GameObject> const& n) {
                              return !n.owner_before(object) && !object.owner_before(n);
                          });
    if (i != mListeners.at(key).end()) {
        // found weak ptr index
        mListeners.at(key).erase(i);      
    }   
}

void NotificationManager::Notify(const std::string& message) {
    for (const std::weak_ptr<GameObject> obj : mListeners.at(message)) {
        if (auto p = obj.lock()) {
            p->ReceiveNotification(message);
        }
    }
}

}