//
// Created by heqyo on 2023/2/4.
//

#ifndef MODIFYFGO_ALTER_LILY_IL2CPPSTRINGCONVERTER_H
#define MODIFYFGO_ALTER_LILY_IL2CPPSTRINGCONVERTER_H

#include <string>
#include "utf8.h"
#include "../il2cpp/il2cpp-types.h"

std::string Il2CppStringToStdString(Il2CppString *str);

Il2CppString *StdStringToIl2CppString(const std::string& str);

#endif //MODIFYFGO_ALTER_LILY_IL2CPPSTRINGCONVERTER_H
