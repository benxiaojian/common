/*
 * ConfigurationFile.cpp
 * Author: Xiao Jian
 */
#include <ConfigurationFile.h>
#include <iostream>
#include <cstring>
using namespace std;

namespace hj
{

const static s32 BUFFER_SIZE = 1024;

ConfigurationFile::ConfigurationFile(const char *file_name)
{
    if (file_name == nullptr) {
        cout << "Failed to open file when file name is empty\n";
        return;
    }

    if ((confiuration_file = fopen(file_name, "r")) == nullptr) {
        cout << "Failed to open file\n";
    }

    buildParameterList();

    fclose(confiuration_file);
    confiuration_file = nullptr;
}


ConfigurationFile::~ConfigurationFile(void)
{
    param_map.clear();

    if (confiuration_file == nullptr) {
        return;
    }

    fclose(confiuration_file);
}


bool ConfigurationFile::isCommentLine(char *line)
{
    return ((line == nullptr) || (*line == '#') || (*line == ' ') || (*line == '\n'));
}


s32 ConfigurationFile::getParameterName(char *line_ptr, char *name, char **cont_str)
{
    if ((line_ptr == nullptr) || (name == nullptr)) {
        return -1;
    }

    while (*line_ptr == ' ') {
        line_ptr++;
    }

    if (*line_ptr == '\0') {
        return -1;
    }

    char *name_begin_ptr = line_ptr;
    while ((*line_ptr != ' ') && (*line_ptr != '=') && (*line_ptr != '\0') && (*line_ptr != '\n')) {
        line_ptr++;
    }

    u32 name_size = line_ptr - name_begin_ptr;
    if ((name_size) == 0) {
        return -1;
    }

    strncpy(name, name_begin_ptr, name_size);
    *cont_str = line_ptr;

    return 0;
}


s32 ConfigurationFile::getParameterValue(char *line_ptr, char *value)
{
    if ((line_ptr == nullptr) || (value == nullptr)) {
        return -1;
    }

    while (*line_ptr == ' ') {
        line_ptr++;
    }

    if (*line_ptr == '=') {
        line_ptr++;
    }

    while (*line_ptr == ' ') {
        line_ptr++;
    }

    char *value_begin_ptr = line_ptr;
    while ((*line_ptr != ' ') && (*line_ptr != '\0') && (*line_ptr != '\n')) {
        line_ptr++;
    }

    u32 value_size = line_ptr - value_begin_ptr;
    if ((value_size) == 0) {
        return -1;
    }

    strncpy(value, value_begin_ptr, value_size);

    return 0;
}


s32 ConfigurationFile::buildParameterList(void)
{
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char value[BUFFER_SIZE];
    char *cont_str;

    while (fgets(buffer, BUFFER_SIZE, confiuration_file) != NULL) {
        memset(name, 0, sizeof(name));
        memset(value, 0, sizeof(value));
        if (isCommentLine(buffer)) {
            continue;
        }

        if (getParameterName(buffer, name, &cont_str) != 0) {
            continue;
        }

        if (getParameterValue(cont_str, value) != 0) {
            continue;
        }

        param_map[name] = value;
    }

    return 0;
}


s32 ConfigurationFile::GetParameterValue(const char *parameter_name, string &parameter_value)
{
    auto param = param_map.find(parameter_name);
    if (param == param_map.end()) {
        return -1;
    }

    parameter_value = param->second;

    return 0;
}

}

