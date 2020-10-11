Build & Launch
```
mkdir -p build && cd build
cmake ..
make -j8
ctest -j8   # run test
./cgol      # launch app
```
or
```
chmod +x build.sh
./build.sh
```

Implementation considerations & Possible improvements
- Drawing is big bottle-neck for performance with large size of the board.
- Potential improvement could be - hand over rendering to separate thread.
- First time working with Qt. In the beginning i've selected to draw rectangles manually with painter, which I guess is not an optimal solution for rendering. QPixmap seems like appropriate thing to use here. 
- Computing next generation of cells could be computed in parallel. E.g splitting game field into grid of 4 and launching a thread for each grid part.
