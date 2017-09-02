# MemoryAllocator

固定長スタック管理式MemoryAllocator  
std::allocatorは実装していません  

Debug実行時で約2倍、Release実行時で約5倍の速度がでます。  


# Benchmark

## DebugBuild
DefaultAllocatorAverage  
newTime:154774us  
deleteTime:142670us  
new/deleteTime:258480us  
  
CustomAllocatorAverage  
newTime:79235.9us  
deleteTime:47216.7us  
new/deleteTime:112332us  
  
CustomAllocatorRate  
newTimeRate:0.511945%  
deleteTimeRate:0.330951%  
new/deleteTimeRate:0.434589%  
  
## ReleaseBuild
DefaultAllocatorAverage  
newTime:48955.5us  
deleteTime:29395.4us  
new/deleteTime:59800.4us  

CustomAllocatorAverage  
newTime:9398.2us  
deleteTime:2241.4us  
new/deleteTime:4782.7us  

CustomAllocatorRate  
newTimeRate:0.191974%  
deleteTimeRate:0.07625%  
new/deleteTimeRate:0.0799777%