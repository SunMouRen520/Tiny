# What is a plugin:
  Generally specking, there are two different kinds of api that need to think about:
  1. APIs that will be implemented by plugin and called by engine.
      - In this way, we can modify some specify behivour of engine, such as ImageLoader.
  2. APIs provide by engine and called by plugin.
      - This type is wildly used in editor development, as Atom, Eclipse etc.
      - Maybe Dependency injection is the right way.



Reference:
  1. https://stackoverflow.com/questions/2768104/how-to-create-a-flexible-plug-in-architecture
  2. http://bitsquid.blogspot.com/2014/04/building-engine-plugin-system.html
  3. http://blog.nuclex-games.com/tutorials/cxx/plugin-architecture/
  4. http://www.drdobbs.com/cpp/building-your-own-plugin-framework-part/204202899?pgno=2
  5. https://sourcey.com/articles/building-a-simple-cpp-cross-platform-plugin-system
