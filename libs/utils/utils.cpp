#include <vector>
#include <string>
#include <glob.h>
#include "utils.hpp"

namespace Utils {
    void globVector (const std::string& pattern, std::vector<std::string>& outFiles) {
        glob_t glob_result;
        glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
        for(unsigned int i=0;i<glob_result.gl_pathc;++i){
            outFiles.push_back(std::string(glob_result.gl_pathv[i]));
        }
        globfree(&glob_result);   
    }
}
