#pragma once
#include <vector>

struct VecUtils final {
    template<typename T>
    static inline void findAndDelete(std::vector<T>& arr, T entryToDelete) {
        int pos = -1;

        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] == entryToDelete) {
                pos = i;
            }
        }

        if (pos == -1) {
            return;
        }

        arr.erase(arr.begin() + pos);
    }
};
