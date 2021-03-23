#pragma once
#include "../src/tags.hpp"
//#include <ph_system_file_path_checker/handles.hpp>
//#include "../src/handles.hpp"
#include <ph_type_list/type_list.hpp>
using namespace std;




#define PATH_EXISTS filesystem::exists (path)
#define IS_DIRECTORY filesystem::is_directory (path)
#define IS_FILE filesystem::is_regular_file (path)















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
    inline static constexpr bool path_can_exist = is_same_v <tag_error_path, tag::constraints::path::can_exist>;
    
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
    
    template <class... T, class... U, class... V>
    static auto process (filesystem::path const& path, type_list <T...> sucessHandlerMixins = type_list <> {}, type_list <U...> pathErrorHandlerMixins = type_list <> {}, type_list <V...> fileTypeErrorHandlerMixins = type_list <> {}) -> decltype (auto)
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
        } else if constexpr (path_can_exist)
        {
            
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
                return (filesystem::path) SuccessHandler<tag::file_type::file, T...> {path};
                
            } else if (IS_DIRECTORY)
            {
                return (filesystem::path) SuccessHandler<tag::file_type::folder, T...> {path};
                
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
    
    template <class... T, class... U, class... V>
    static auto process (filesystem::path const& path, type_list <T...> sucessHandlerMixins = type_list <> {}, type_list <U...> pathErrorHandlerMixins = type_list <> {}, type_list <V...> fileTypeErrorHandlerMixins = type_list <> {}) -> decltype (auto)
    {
        
        return Path_Info <SuccessHandler, tag_error_path, PathErrorHandler, tag_error_file_type, FileTypeErrorHandler>::process (path);
    }
    
    
};



#undef PATH_EXISTS
#undef IS_DIRECTORY
#undef IS_FILE
