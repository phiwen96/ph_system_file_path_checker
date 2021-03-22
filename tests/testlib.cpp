#include "headers.hpp"

template <class>
struct InputPathErrorHandler;

template <>
struct InputPathErrorHandler <tag::error::path::must_exist>
{
    static void error (filesystem::path const& path)
    {
        throw runtime_error ("given path does not exist on system");
    }
};


template <class>
struct OutputPathErrorHandler;

template <>
struct OutputPathErrorHandler <tag::error::path::must_not_exist>
{
    static void error (filesystem::path const& path)
    {
        throw runtime_error ("given path already exist on system");
    }
};


template <class>
struct InputFileTypeErrorHandler
{
    static void error (filesystem::path const& path)
    {
        throw runtime_error ("given path already exist on system");
    }
};

template <class>
struct OutputFileTypeErrorHandler
{
    static void error (filesystem::path const& path)
    {
        throw runtime_error ("given path already exist on system");
    }
};








template <class...>
struct InputPathHandler;

template <class... Mixins>
struct InputPathHandler <tag::file_type::file, Mixins...> : Mixins...
{
    string text;
    
    InputPathHandler (filesystem::path const& path) : text (readFileIntoString(path)), Mixins {path}...
    {
        cout << "FILE" << endl;
        cout << text << endl;
    }
};





template <class... Mixins>
struct InputPathHandler <tag::file_type::folder, Mixins...> : Mixins...
{
    
    
    InputPathHandler (filesystem::path const& path) : Mixins {path}...
    {
        cout << "FOLDER" << endl;
    }
};




int main( int argc, char* argv[] ) {
    
    using input_reader = system_file_path_checker <InputPathHandler, tag::error::path::must_exist, InputPathErrorHandler, tag::error::file_type::can_be_any, InputFileTypeErrorHandler>;
    input_reader reader (argv[0], type_list <int, char> {}, type_list <string, int> {});

    int result = Catch::Session().run( argc, argv );


    return result;
}



