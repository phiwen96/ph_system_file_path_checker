#include "headers.hpp"

template <class>
struct handle_input_path_error;

template <>
struct handle_input_path_error <tag::error::path::must_exist>
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
struct handle_input_file_type_error
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
struct handle_input_path;

template <class... Mixins>
struct handle_input_path <tag::file_type::file, Mixins...> : Mixins...
{
    string text;
    
    handle_input_path (filesystem::path const& path) : text (readFileIntoString(path)), Mixins {path}...
    {
        cout << "FILE" << endl;
        cout << text << endl;
    }
};





template <class... Mixins>
struct handle_input_path <tag::file_type::folder, Mixins...> : Mixins...
{
    
    
    handle_input_path (filesystem::path const& path) : Mixins {path}...
    {
        cout << "FOLDER" << endl;
    }
};


string my_file_name (string name = __builtin_FILE ())
{
    return name;
};



int main( int argc, char* argv[] ) {
    
    using input_reader = system_file_path_checker <handle_input_path, tag::error::path::must_exist, handle_input_path_error, tag::error::file_type::can_be_any, handle_input_file_type_error>;
    input_reader reader (my_file_name (), type_list <int, char> {}, type_list <string, int> {});

    int result = Catch::Session().run( argc, argv );


    return result;
}



