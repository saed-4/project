#include <iostream>
using namespace std;

int main() {
    double temp[] = {37.5, 32.6, 30, 26, 25, 31, 34};
    double minTemp = temp[0];
    double maxTemp = temp[0];
    double sum = 0.0;
    
    int arraylength = sizeof(temp) / sizeof(temp[0]);
    
    // FIX: Changed "arraylength - 1" to "arraylength" to include the last element
    for (int i = 0; i < arraylength; i++) {
        if (temp[i] < minTemp) { minTemp = temp[i]; }
        if (temp[i] > maxTemp) { maxTemp = temp[i]; }
        sum += temp[i];
    }
    
    // Calculate average after the loop finishes summing everything
    double avg = sum / arraylength;
    
    // Display the statistics
    cout << "Minimum Temperature: " << minTemp << endl;
    cout << "Maximum Temperature: " << maxTemp << endl;
    cout << "Average Temperature: " << avg << endl;
    
    return 0;
}
