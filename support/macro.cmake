if(WIN32)
    add_definitions(-DTINY_PLATFORM_WINDOWS )
endif(WIN32)

if(PACKAGE_TESTS)
    add_definitions(-DTINY_TEST)
endif(PACKAGE_TESTS)
