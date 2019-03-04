/*
 * ConfigurationFile.h
 * Author: Xiao Jian
 *
 * read file with format "key = value".
 * and get the value
 */
#include <GobalType.h>
#include <string>
#include <map>


namespace hj
{

class ConfigurationFile
{
public:
    ConfigurationFile(const char *file_name = nullptr);
    ~ConfigurationFile(void);

    s32 GetParameterValue(const char *parameter_name, std::string &parameter_value);

private:
    s32 buildParameterList(void);
    bool isCommentLine(char *line);
    s32 getParameterName(char *line_ptr, char *name, char **cont_str);
    s32 getParameterValue(char *line_ptr, char *value);

    FILE *confiuration_file;
    std::map<std::string, std::string> param_map;
};

}
