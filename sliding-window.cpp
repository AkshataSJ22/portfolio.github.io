#include <iostream>
#include <queue>
using namespace std;

class ActivityTracker {
private:
    queue<int> recentTimestamps;
    int windowSize = 300; // 5 minutes = 300 seconds

public:
    void watch(int timestamp) {
        // Remove outdated timestamps
        while (!recentTimestamps.empty() && recentTimestamps.front() <= timestamp - windowSize) {
            recentTimestamps.pop();
        }
        recentTimestamps.push(timestamp);
    }

    int getRecentViews(int currentTime) {
        // Remove outdated timestamps again to be accurate
        while (!recentTimestamps.empty() && recentTimestamps.front() <= currentTime - windowSize) {
            recentTimestamps.pop();
        }
        return recentTimestamps.size();
    }
};

int main() {
    ActivityTracker tracker;
    
    tracker.watch(100);
    tracker.watch(200);
    tracker.watch(300);
    tracker.watch(400);

    cout << "Views in last 5 minutes at t=400: " << tracker.getRecentViews(400) << endl; // Should print 3
    cout << "Views in last 5 minutes at t=600: " << tracker.getRecentViews(600) << endl; // Should print 1

    return 0;
}
