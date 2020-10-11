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