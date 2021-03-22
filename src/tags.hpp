#ifndef HANDLES_HPP
#define HANDLES_HPP

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
