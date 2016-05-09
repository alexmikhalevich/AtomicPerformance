# AtomicPerformance
This little investigation aimed to determine the performance of std::atomic_\* functions in different cases.  
_First case:_ aligned and not alighed atomic variables.  
_Second case:_ atomic variable that lies entirely in the cache line and atomic variable which crosses this border.  
_Third case:_ two atomic variables which lie in the same or in different cache lines.  
