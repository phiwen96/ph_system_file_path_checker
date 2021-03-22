#ifndef TAGS_HPP
#define TAGS_HPP

namespace tag
{
namespace file_type
    {
        struct file
        {
            
        };
        
        struct folder
        {
            
        };
    };
    
namespace constraints
    {
namespace path
        {
            struct must_exist;
            struct must_not_exist;
        struct can_exist;
        };
        
namespace file_type
        {
            struct must_be_file;
            struct must_be_folder;
            struct can_be_any;
        };
    };
};
#endif
