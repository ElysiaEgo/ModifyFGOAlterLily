//
// Created by heqyo on 2023/2/4.
//

#include "Il2CppStringConverter.h"

#define DO_API(r, n, p) extern r (*n) p

#include "../il2cpp/il2cpp-api-functions.h"

#undef DO_API

std::string Utf16ToUtf8(const Il2CppChar *utf16String) {
    const Il2CppChar *ptr = utf16String;
    size_t length = 0;
    while (*ptr) {
        ptr++;
        length++;
    }

    std::string utf8String;
    utf8String.reserve(length);
    utf8::unchecked::utf16to8(utf16String, ptr, std::back_inserter(utf8String));

    return utf8String;
}

std::string Il2CppStringToStdString(Il2CppString *str) {
    return Utf16ToUtf8(str->chars);
}

std::basic_string<Il2CppChar> Utf8ToUtf16(const char *utf8String) {
    std::basic_string<Il2CppChar> utf16String;
    auto length = strlen(utf8String);

    if (utf8::is_valid(utf8String, utf8String + length)) {
        utf16String.reserve(length);
        utf8::unchecked::utf8to16(utf8String, utf8String + length, std::back_inserter(utf16String));
    }

    return utf16String;
}

Il2CppString *StdStringToIl2CppString(const std::string& str) {
    auto chars = Utf8ToUtf16(str.c_str());
    return il2cpp_string_new_utf16(chars.c_str(), chars.length());
}