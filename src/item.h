#ifndef ITEM_H
#define ITEM_H

class Item {
    public:
        // Constructor
        Item(int v, int w, int orig_pos) {
            // Set weight, value, original, & position
            weight = w;
            value = v;
            originalPosition = orig_pos;

            // Calculate profit per pound
            profitPerPound = float(v) / float(w);

            // At this point, we haven't taken ANY items, so the default value should be false
            taken = false;
            
            // In this problem we will need to sort twice, once by profit / pound and once by original position,
            // this variable lets us define operators to compare accordingly
            compareByPosition = false;
        }



        // Define custom operators used in quicksort, uses different modes.
        // We have to do this since we will sort the vector once by profit / pound,
        // and once by the original position in order to "undo" the previous sort.
        //      compare_by_position == true:
        //              -Compare by original position in vector
        //      compare_by_position = false:
        //              -Compare by profit / pound
        bool compareByPosition;
        bool operator>(Item comparisonItem) {
            if (compareByPosition) return originalPosition > comparisonItem.originalPosition;
            else return profitPerPound > comparisonItem.profitPerPound;
        }
        bool operator<(Item comparisonItem) {
            if (compareByPosition) return originalPosition < comparisonItem.originalPosition;
            else return profitPerPound < comparisonItem.profitPerPound;
        }
        bool operator>=(Item comparisonItem) {
            if (compareByPosition) return originalPosition >= comparisonItem.originalPosition;
            else return profitPerPound >= comparisonItem.profitPerPound;
        }
        bool operator<=(Item comparisonItem) {
            if (compareByPosition) return originalPosition <= comparisonItem.originalPosition;
            else return profitPerPound <= comparisonItem.profitPerPound;
        }

        // Weight of the item
        int weight;

        // Value of the item
        int value;
        
        // Original position of the item in the input vector
        int originalPosition;

        // Bool to determine whether we took the item or not
        bool taken;

        // Profit per pound, maybe we can use this as a parameter to sort 
        // items to get a more 'greedy' solution.
        float profitPerPound;
        
};



#endif