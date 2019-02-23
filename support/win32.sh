cd ../build
if [ ! -d WIN32 ] ; then
    mkdir WIN32
fi
cd WIN32
cmake -G "Visual Studio 14 2015"  -DCMAKE_PREFIX_PATH="D:/Sys"  -DCMAKE_MODULE_PATH="D:/Sys" --build -DPACKAGE_TESTS=OFF -Dgtest_force_shared_crt=TRUE ..\\..
