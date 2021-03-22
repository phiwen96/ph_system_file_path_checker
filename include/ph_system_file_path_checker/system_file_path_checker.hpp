#include "../src/tags.hpp"
#pragma once
//#include "../src/handles.hpp"
#include <ph_type_list/type_list.hpp>
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


#define PATH_EXISTS filesystem::exists (path)
#define IS_DIRECTORY filesystem::is_directory (path)
#define IS_FILE filesystem::is_regular_file (path)




template <class>
struct handle_input_path_error;

template <>
struct handle_input_path_error <tag::constraints::path::must_exist>
{
    handle_input_path_error (filesystem::path const& path)
    {
        throw runtime_error ("given path does not exist on system");
    }
};


template <class>
struct OutputPathErrorHandler;

template <>
struct OutputPathErrorHandler <tag::constraints::path::must_not_exist>
{
    OutputPathErrorHandler (filesystem::path const& path)
    {
        throw runtime_error ("given path already exist on system");
    }
};


template <class>
struct handle_input_file_type_error
{
    handle_input_file_type_error (filesystem::path const& path)
    {
        throw runtime_error ("given path already exist on system");
    }
};

template <class>
struct OutputFileTypeErrorHandler
{
    OutputFileTypeErrorHandler (filesystem::path const& path)
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












template <template <class...> class SuccessHandler, class tag_error_path, template <class...> class PathErrorHandler, class tag_error_file_type, template <class...> class FileTypeErrorHandler>
requires requires (filesystem::path const& path) {
    is_same_v <tag_error_path, tag::constraints::path::must_exist> or is_same_v <tag_error_path, tag::constraints::path::must_not_exist>;
    is_same_v <tag_error_file_type, tag::constraints::file_type::must_be_file> or is_same_v <tag_error_file_type, tag::constraints::file_type::must_be_folder> or is_same_v <tag_error_file_type, tag::constraints::file_type::can_be_any>;
    
    PathErrorHandler <tag_error_path> {path};
    SuccessHandler <tag::file_type::file> {path};
    SuccessHandler <tag::file_type::folder> {path};
}
struct Path_Info
{
    inline static constexpr bool path_must_exist = is_same_v <tag_error_path, tag::constraints::path::must_exist>;
    inline static constexpr bool path_must_not_exist = is_same_v <tag_error_path, tag::constraints::path::must_not_exist>;
    
    inline static constexpr bool must_be_file = is_same_v <tag_error_file_type, tag::constraints::file_type::must_be_file>;
    inline static constexpr bool must_be_folder = is_same_v <tag_error_file_type, tag::constraints::file_type::must_be_folder>;
    inline static constexpr bool can_be_any = is_same_v <tag_error_file_type, tag::constraints::file_type::can_be_any>;
    
//    using file_type = conditional_t <must_be_file, tag::file_type::file, conditional_t <must_be_folder, tag::file_type::folder, <#class _Then#>>>
    
    
    template <class... T, class... U, class... V>
    Path_Info (filesystem::path const& path, type_list <T...> sucessHandlerMixins = type_list <> {}, type_list <U...> pathErrorHandlerMixins = type_list <> {}, type_list <V...> fileTypeErrorHandlerMixins = type_list <> {})
    {
        
        using path_error_handler = PathErrorHandler <tag_error_path, U...>;
        using file_type_error_handler = FileTypeErrorHandler <tag_error_file_type, V...>;
    
        if constexpr (path_must_exist)
        {
            if (not PATH_EXISTS)
            {
//                type_list <T...>::
                path_error_handler {path};
            }
            
        } else if constexpr (path_must_not_exist)
        {
            if (PATH_EXISTS)
            {
                path_error_handler {path};
            }
        }
       
        if constexpr (must_be_file)
        {
            if (not IS_FILE)
            {
                file_type_error_handler {path};
            }
            
            SuccessHandler<tag::file_type::file, T...> {path};
            
        } else if constexpr (must_be_folder)
        {
            if (not IS_DIRECTORY)
            {
                file_type_error_handler {path};
            }
            
            SuccessHandler<tag::file_type::folder, T...> {path};
            
        } else if constexpr (can_be_any)
        {
            if (IS_FILE)
            {
                SuccessHandler<tag::file_type::file, T...> {path};
                
            } else if (IS_DIRECTORY)
            {
                SuccessHandler<tag::file_type::folder, T...> {path};
                
            } else
            {
                file_type_error_handler {path};
            }
        }
        
//        using success_handler = SuccessHandler <class>
    }
};





//using namespace ph_system_file_path_checker_impl;

template <template <class...> class SuccessHandler, class tag_error_path, class tag_error_file_type, template <class...> class PathErrorHandler, template <class...> class FileTypeErrorHandler>
struct system_file_path_checker
{
    
    template <class... T, class... U, class... V>
    system_file_path_checker (filesystem::path const& path, type_list <T...> sucessHandlerMixins = type_list <> {}, type_list <U...> pathErrorHandlerMixins = type_list <> {}, type_list <V...> fileTypeErrorHandlerMixins = type_list <> {})
    {
        
        Path_Info <SuccessHandler, tag_error_path, PathErrorHandler, tag_error_file_type, FileTypeErrorHandler> {path};
    }
    
};



#undef PATH_EXISTS
#undef IS_DIRECTORY
#undef IS_FILE
