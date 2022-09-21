#ifndef memo_h
#define memo_h

#include <vector>

template <typename T>
class Memo {
    public:
        // A should be a smaller value, b should be larger.
        bool Find(int a, int b, T& result) {
            if (Exists_In_Index(a, lookup_indices.size() - 1, 0)) {
                int possible_result = T();
                if (Get_In_Memo(a, b, possible_result)) {
                    result = possible_result;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        void Insert(int a, int b, T value);
    private:

        // Recursively insert elements
        bool Insert_Helper() {

        }

        bool Exists_In_Index(const int a, int max, int min) {
            int i = min + ((max - min) / 2);

            if (lookup_indices[i] == a) return true;
            if (i == max && i == min) return false;
            else {
                int max_offset = max - i;
                int min_offset = i - min;
                if (lookup_indices[i] > a) {
                    return Exists_In_Index(a, max, max_offset);
                }
                if (lookup_indices[i] < a) {
                    return Exists_In_Index(a, min_offset, min);
                }
            }
        }

        bool Find_Item(const int a, const int b, int max, int min, T& result) {
            int i = min + ((max - min) / 2);
            if (index_table[a][i] == b) {
                result = values[a][i];
                return true;
            } else if (max == i && min == i) {
                return false;
            } else {
                int max_offset = max - i;
                int min_offset = i - min;

                if (index_table[a][i] > b) {
                    return Find_Item(a, b, max, max_offset, result);
                }
                if (index_table[a][i] < b) {
                    return Find_Item(a, b, min_offset, min, result);
                }
            }
        }

        bool Get_In_Memo(int a, int b, T& result) {
            T possible_result;
            if (Find_Item(a, b, values[a].size() - 1, 0, possible_result)) {
                result = possible_result;
                return true;
            }else {
                return false;
            }
        }

        std::vector<int> lookup_indices;
        std::vector< std::vector<int> > index_table;
        std::vector< std::vector<T> > values;
}


#endif