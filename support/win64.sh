cd ../build
if [ ! -d WIN64 ] ; then
    mkdir WIN64
fi
cd WIN64
cmake -G "Visual Studio 14 2015 Win64"  -DCMAKE_PREFIX_PATH="C:/Sys/bin" --build -DPACKAGE_TESTS=OFF -Dgtest_force_shared_crt=TRUE ..\\..
