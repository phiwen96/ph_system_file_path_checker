#ifndef HANDLES_HPP
#define HANDLES_HPP
using namespace std;
string my_file_name (string name = __builtin_FILE ())
{
    return name;
};


template <class...>
struct handle_input_path_error {};

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


template <class...>
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
struct handle_input_path {};

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

#endif
