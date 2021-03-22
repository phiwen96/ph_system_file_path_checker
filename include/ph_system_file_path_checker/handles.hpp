#ifndef HANDLES_HPP
#define HANDLES_HPP
using namespace std;
string readFileIntoString(filesystem::path const& path) {
    ifstream input_file (path);
    
      if (!input_file.is_open()) {
            cerr << "Could not open the file - '"
            << path << "'" << endl;
            exit(EXIT_FAILURE);
      }
      return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

template <class>
struct handle_path_error;

template <>
struct handle_path_error <tag::constraints::path::must_exist>
{
    handle_path_error (filesystem::path const& path)
    {
        throw runtime_error ("given path does not exist on system");
    }
};


template <class Tag>
struct handle_file_type_error
{
    handle_file_type_error (filesystem::path const& path)
    {
        if constexpr (is_same_v <Tag, tag::constraints::file_type::must_be_folder>)
        {
            throw runtime_error ("given path refers to a folder");
            
        } else if constexpr (is_same_v <Tag, tag::constraints::file_type::must_be_file>)
        {
            throw runtime_error ("given path refers to a file");
        }
    }
};





template <class...>
struct handle_path;

template <class... Mixins>
struct handle_path <tag::file_type::file, Mixins...> : Mixins...
{
    string text;
    
    handle_path (filesystem::path const& path) : text (readFileIntoString(path)), Mixins {path}...
    {
        cout << "FILE" << endl;
        cout << text << endl;
    }
};





template <class... Mixins>
struct handle_path <tag::file_type::folder, Mixins...> : Mixins...
{
    
    
    handle_path (filesystem::path const& path) : Mixins {path}...
    {
        cout << "FOLDER" << endl;
    }
};


#endif
